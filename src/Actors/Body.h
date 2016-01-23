//
// Created by mk on 19.01.16.
//

#ifndef ORBIT2_BODY_H
#define ORBIT2_BODY_H

#include <oxygine-framework.h>

using namespace oxygine;
using namespace std;

typedef tuple<Vector2, Vector2, Vector2> BodyInfo;
class Body : public Actor {
public:
    Vector2 velocity;
    Vector2 acceleration;

    const Vector2 & getVelocity() const;
    void setVelocity(const Vector2 &velocity);
    const Vector2 & getAcceleration() const;
    void setAcceleration(const Vector2 &acceleration);
};
typedef intrusive_ptr<Body> spBody;

#endif //ORBIT2_BODY_H
