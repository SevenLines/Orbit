//
// Created by mk on 18.01.16.
//

#ifndef ORBIT2_GLOBALSTATE_H
#define ORBIT2_GLOBALSTATE_H

#include <oxygine-framework.h>

class GlobalState {
public:
    bool keys_pressed[256] = {false};
};
typedef oxygine::intrusive_ptr<GlobalState> spGlobalState;


#endif //ORBIT2_GLOBALSTATE_H
