#include <string>

using std::string;

#ifndef M_TOKEN
#define M_TOKEN

// 定义token结构体
struct mToken {
    int type;
    string text;
    double value;
    mToken (int tp = -1, const string& t = "", double v = 0): type(tp), text(t), value(v) {};
};

#endif