
#ifndef LEXER_CONFIG
#define LEXER_CONFIG

/* ���������� */
extern bool isLetter (char ch);
extern bool isDigit (char ch);
extern bool isOperator (char ch);
extern bool isWhitespace (char ch);
extern bool isDelimiter (char ch);

enum CONDITION {IS_LETTER, IS_DIGIT, IS_OPERATOR, IS_WHITESPACE, IS_DELIMITER, UNKNOWN};

// ����token������
enum mTOKEN_TYPE {
// ��������������״̬
NUM, ID, INC, IN, VO, DO, RET, QUO, LP, RP, LB, RB, AS, SE, QU, COM, PO,
EPSILON, ENDL, UN,

// ���Ĳ��޸ģ����ڼ���
mTOKEN_NUM};

// ����state������
enum mSTATE_TYPE {
READY, IGNORE, FINISH, ERROR,

// ��������������״̬
INTEGER, IDENTIFIER,
M_AIN, MA_IN, MAI_N, MAIN,
I_NCLUDE, IN_CLUDE, INC_LUDE, INCL_UDE, INCLU_DE, INCLUD_E, INCLUDE,
I_NT, IN_T, INT, V_OID, VO_ID, VOI_D, VOID,
D_OUBLE, DO_UBLE, DOU_BLE, DOUB_LE, DOUBL_E, DOUBLE,
R_ETURN ,RE_TURN, RET_URN, RETU_RN, RETUR_N, RETURN,
COMMA, SEMICOLON, LEFT_BRACE, RIGHT_BRACE, ASSIGN, QUOTATION, POUND,
LEFT_PAREM, RIGHT_PAREN,

/* ����״̬READY, IGNORE, FINISH, ERROR */
/* ���Ĳ��޸ģ����ڼ��� */
mSTATE_NUM};

#endif

#include "mToken.h"
#include "mState.h"
