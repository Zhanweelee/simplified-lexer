# 简易编译器
本编译器由词法分析(**mLexer**)、语法分析(**mParser**)和语义解析三部分组成。其中库中提供lexer和parser部分的功能实现，可以直接通过包含头文件，进行实例化构造不同需求的lexer和parser，而语义解析部分没有具体的代码提供，但是有相应的例子(**Simplified-SQL**)提供参考。
项目地址(simplified-compiler)：https://github.com/Zhanweelee/simplified-compiler

# 简易词法分析器

## 词法分析
@[mLexer|词法分析器|有穷自动机|编译器]

本项目是simplified-compiler的子项目，是编译器的第一部分词法分析过程，所使用的类名为mLexer。

**mLexer**是词法分析器的类名，使用者可以自行进行继承和封装，采用FSM进行状态转移，因此我们在使用前需要定义状态、状态终止时对应的token类型。

**注意** 本项目暂时无法用GCC编译，项目测试在Visual Studio 2012项目下可以正常编译和运行。

### 使用步骤
可以概括为三个步骤：
1. 包含头文件`#include "mLexer.h"`
2. 在`lexerConfig.h`中定义`enum mTOKEN_TYPE`
3. 在`lexerConfig.h`中定义`enum mSTATE_TYPE`
4. 在`mLexerInit.cpp`中定义状态转移图
5. 实例化mLexer，调用process方法对字符串进行处理

### 例子
使用**mLexer**构造一个C程序代码的词法分析，可以解析一下代码并且得到相应的token。
```
#include "file"
int main(void) {
    int a = 123;
	printf("Hello world");
	return 0;
}
```

#### 1. 在`lexerConfig.h`中定义token类型
使用之前我们应该清楚词法分析器的输出是token流，我们对自己希望得到的token的类型和文本内容应该要很清楚。在这里我们可以简单的设定token的类型一共有四大类：Identifier, keyword, integer, delimiter。
具体细分如下
- Identifier: a main
- keyword: # include int void return
- integer: 123 0
- delimiter: " ( ) { = ; }

这里我们需要在lexerConfig.h中定义枚举类型mTOKEN_TYPE，这个例子中定义为
```
enum mTOKEN_TYPE {
NUM, ID, INC, IN, VO, DO, RET, QUO, LP, RP, LB, RB, AS, SE, PO,
EPSILON, ENDL, UN,
mTOKEN_NUM};
```

#### 2. 在`lexerConfig.h`中定义状态转移类型
> ** 有限状态机 **（英语：finite-state machine，缩写：FSM）又称有限状态自动机，简称状态机，是表示有限个状态以及在这些状态之间的转移和动作等行为的数学模型。 --[维基百科](http://en.wikipedia.org/wiki/Finite-state_machine)

构建有限状态自动机我们需要状态节点和状态转移条件。这一步骤中我们先简单讨论状态节点的定义。词法分析部分中采用的有限状态机每次读取一个字符，然后根据状态图中转移条件进行转移，因此我们需要把所有可能出现的下一字符都定义相应的状态。实际上，我们只需要考虑符合我们要求的条件赋予特定的状态，其他都定义为ERROR状态即可。

这里我们需要在lexerConfig.h中定义枚举类型mSTATE_TYPE，这个例子中定义为
```
enum mSTATE_TYPE {
READY, END, FINISH, ERROR,

// 这里继续填入你的状态
INTEGER, IDENTIFIER,
I_NCLUDE, IN_CLUDE, INC_LUDE, INCL_UDE, INCLU_DE, INCLUD_E, INCLUDE,
I_NT, IN_T, INT, V_OID, VO_ID, VOI_D, VOID,
D_OUBLE, DO_UBLE, DOU_BLE, DOUB_LE, DOUBL_E, DOUBLE,
R_ETURN ,RE_TURN, RET_URN, RETU_RN, RETUR_N, RETURN,
COMMA, SEMICOLON, LEFT_BRACE, RIGHT_BRACE, ASSIGN, QUOTATION, POUND
LEFT_PAREM, RIGHT_PAREN,

/* 保留状态READY, END, FINISH, ERROR */
/* 最后的不要修改，用于计数 */
mSTATE_NUM};
```

#### 4. 在`mLexerInit.cpp`中定义状态转移图
状态转移图由两部分组成：**状态节点**和**转移条件**。**状态节点**在上一步骤已经完成，这一步骤需要根据**转移条件**构建这个图。

```
	/* 构造状态转移图 */
	// 状态READY
    states[READY].push(IS_DIGIT, &states[INTEGER])
        .push(IS_LETTER, &states[IDENTIFIER])
        .push('i', &states[I_NCLUDE])
		.push('i', &states[I_NT])
		.push('d', &states[D_OUBLE])
		.push('r', &states[R_ETURN])
        .push('=', &states[ASSIGN])
		.push(',', &states[COMMA])
		.push(';', &states[SEMICOLON])
        .push('{', &states[LEFT_BRACE])
		.push('}', &states[RIGHT_BRACE])
        .push('(', &states[LEFT_PAREM])
		.push(')', &states[RIGHT_PAREN])
		.push('\n', &states[IGNORE])
		.push(IS_WHITESPACE, &states[IGNORE]);
	
    states[INTEGER].push(IS_LETTER, &states[ERROR])
		.push(IS_DIGIT, &states[INTEGER])
		.push(IS_OPERATOR, &states[FINISH])
		.push(IS_WHITESPACE, &states[FINISH])
		.push(IS_DELIMITER, &states[FINISH]);

    states[IDENTIFIER].push(IS_LETTER, &states[IDENTIFIER])
		.push(IS_DIGIT, &states[IDENTIFIER])
		.push(IS_OPERATOR, &states[FINISH])
		.push(IS_WHITESPACE, &states[FINISH])
		.push(IS_DELIMITER, &states[FINISH]);

    states[I_NCLUDE].push('n', &states[IN_CLUDE]);
    states[IN_CLUDE].push('c', &states[INC_LUDE]);
    states[INC_LUDE].push('l', &states[INCL_UDE]);
    states[INCL_UDE].push('u', &states[INCLU_DE]);
    states[INCLU_DE].push('d', &states[INCLUD_E]);
    states[INCLUD_E].push('e', &states[INCLUDE]);
	states[INCLUDE].push(IS_OPERATOR, &states[FINISH])
		.push(IS_WHITESPACE, &states[FINISH])
		.push(IS_DELIMITER, &states[FINISH]);
    
    .... (略)
```

转移图构造好之后，我们还需要定义状态节点和token对应的关系，一般只需要可以通过epsilon转移到终止状态的节点进行定义。

```
	map<int, int> stateIDToTokenType;
	stateIDToTokenType[INTEGER] = NUM;
	stateIDToTokenType[IDENTIFIER] = ID;

	stateIDToTokenType[INCLUDE] = INC;
	stateIDToTokenType[INT] = IN;
	stateIDToTokenType[VOID] = VO;
	stateIDToTokenType[RETURN] = RET;
	
    stateIDToTokenType[LEFT_BRACE] = LB;
    stateIDToTokenType[RIGHT_BRACE] = RB;
    stateIDToTokenType[LEFT_PAREM] = LP;
    stateIDToTokenType[RIGHT_PAREN] = RP;
	stateIDToTokenType[QUOTATION] = QU;
	stateIDToTokenType[ASSIGN] = AS;
	stateIDToTokenType[COMMA] = COM;
	stateIDToTokenType[SEMICOLON] = SE;
	stateIDToTokenType[POUND] = PO;
```

额外的，如果我们有特殊的**转移条件**，可以进行设置。
代码如下
```
	/* 通配转移条件 */
	map<int, charTypeCheck> transferCondition;
	transferCondition[IS_LETTER]= isLetter;
	transferCondition[IS_DIGIT]= isDigit;
	transferCondition[IS_OPERATOR]= isOperator;
	transferCondition[IS_WHITESPACE]= isWhitespace;
	transferCondition[IS_DELIMITER]= isDelimiter;
```

最后用状态图根节点、状态节点和token的关系、通配转移条件三个参数构造lexer的实例。
`mLexer* lexer = new mLexer(states, stateIDToTokenType, transferCondition);`

新建一个文件`lexerTest.cpp`，测试代码为
```
#include <iostream>
#include <string>

using namespace std;

#include "mLexer.h"

extern mLexer* mLexerInit();

int main() {
	mLexer* lexer = mLexerInit();
	string str = "#include \"file\" int main(void) { int a = 123, b = 456; a = b; return 0; }";
    lexer->process(str);
    cout <<str <<endl;
    lexer->printTokenStream();

    return 0;
}
```

测试**输出**为
```
#include "file" int main(void) { int a = 123, b = 456; a = b; return 0; }
Token: 0
type: 16
text: #
value: 0.000000

Token: 1
type: 2
text: include
value: 0.000000

Token: 2
type: 14
text: "
value: 0.000000

Token: 3
type: 1
text: file
value: 0.000000

Token: 4
type: 14
text: "
value: 0.000000

Token: 5
type: 3
text: int
value: 0.000000

Token: 6
type: 1
text: main
value: 0.000000

Token: 7
type: 8
text: (
value: 0.000000

Token: 8
type: 1
text: void
value: 0.000000

Token: 9
type: 9
text: )
value: 0.000000

Token: 10
type: 10
text: {
value: 0.000000

Token: 11
type: 3
text: int
value: 0.000000

Token: 12
type: 1
text: a
value: 0.000000

Token: 13
type: 12
text: =
value: 0.000000

Token: 14
type: 0
text: 123
value: 123.000000

Token: 15
type: 15
text: ,
value: 0.000000

Token: 16
type: 1
text: b
value: 0.000000

Token: 17
type: 12
text: =
value: 0.000000

Token: 18
type: 0
text: 456
value: 456.000000

Token: 19
type: 13
text: ;
value: 0.000000

Token: 20
type: 1
text: a
value: 0.000000

Token: 21
type: 12
text: =
value: 0.000000

Token: 22
type: 1
text: b
value: 0.000000

Token: 23
type: 13
text: ;
value: 0.000000

Token: 24
type: 6
text: return
value: 0.000000

Token: 25
type: 0
text: 0
value: 0.000000

Token: 26
type: 13
text: ;
value: 0.000000

Token: 27
type: 11
text: }
value: 0.000000
```

