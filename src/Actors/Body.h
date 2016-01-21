//
// Created by mk on 19.01.16.
//

#ifndef ORBIT2_BODY_H
#define ORBIT2_BODY_H

#include <oxygine-framework.h>

using namespace oxygine;

class Body : public Actor {
public:
    Vector2 velocity;
    Vector2 acceleration;
    Vector2 getNextPosition(float delta_time);

};
typedef intrusive_ptr<Body> spBody;

#endif //ORBIT2_BODY_H
