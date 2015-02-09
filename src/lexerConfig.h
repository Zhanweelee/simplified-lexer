
#ifndef LEXER_CONFIG
#define LEXER_CONFIG

/* 其他处理函数 */
extern bool isLetter (char ch);
extern bool isDigit (char ch);
extern bool isOperator (char ch);
extern bool isWhitespace (char ch);
extern bool isDelimiter (char ch);

enum CONDITION {IS_LETTER, IS_DIGIT, IS_OPERATOR, IS_WHITESPACE, IS_DELIMITER, UNKNOWN};

// 定义token的类型
enum mTOKEN_TYPE {
// 这里继续填入你的状态
NUM, ID, INC, IN, VO, DO, RET, QUO, LP, RP, LB, RB, AS, SE, QU, COM, PO,
EPSILON, ENDL, UN,

// 最后的不修改，用于计数
mTOKEN_NUM};

// 定义state的类型
enum mSTATE_TYPE {
READY, IGNORE, FINISH, ERROR,

// 这里继续填入你的状态
INTEGER, IDENTIFIER,
M_AIN, MA_IN, MAI_N, MAIN,
I_NCLUDE, IN_CLUDE, INC_LUDE, INCL_UDE, INCLU_DE, INCLUD_E, INCLUDE,
I_NT, IN_T, INT, V_OID, VO_ID, VOI_D, VOID,
D_OUBLE, DO_UBLE, DOU_BLE, DOUB_LE, DOUBL_E, DOUBLE,
R_ETURN ,RE_TURN, RET_URN, RETU_RN, RETUR_N, RETURN,
COMMA, SEMICOLON, LEFT_BRACE, RIGHT_BRACE, ASSIGN, QUOTATION, POUND,
LEFT_PAREM, RIGHT_PAREN,

/* 保留状态READY, IGNORE, FINISH, ERROR */
/* 最后的不修改，用于计数 */
mSTATE_NUM};

#endif

#include "mToken.h"
#include "mState.h"
