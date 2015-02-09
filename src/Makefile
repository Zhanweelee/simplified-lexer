all: run

run: lexer-c
	./lexerTest

lexer-c: mToken.h mState.h mLexer.h mLexer.cpp lexerConfig.h lexerFuncions.cpp mLexerInit.cpp lexerTest.cpp
	g++ lexerConfig.h mToken.h mState.h mLexer.h mLexer.cpp lexerFuncions.cpp mLexerInit.cpp lexerTest.cpp -o lexerTest