#include <string>
#include <map>
using namespace std;

#ifndef M_STATE
#define M_STATE

struct mState {
    int stateID;
    bool isEnd;
    string currntText;
    multimap<CONDITION, mState*> generalTransfer;
    multimap<char, mState*> specifiedTransfer;
    mState& push(CONDITION condition, mState* state) { generalTransfer.insert(make_pair(condition, state)); return *this; }
    mState& push(char ch, mState* state) { specifiedTransfer.insert(make_pair(ch, state)); return *this; }

    mState (int id = -1, string text = "", bool end = false): stateID(id), currntText(text), isEnd(end) {};
};

#endif