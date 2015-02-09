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