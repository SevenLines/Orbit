//
// Created by mk on 19.01.16.
//

#include "Body.h"

const Vector2 &Body::getVelocity() const {
    return velocity;
}

void Body::setVelocity(const Vector2 &velocity) {
    Body::velocity = velocity;
}

const Vector2 &Body::getAcceleration() const {
    return acceleration;
}

void Body::setAcceleration(const Vector2 &acceleration) {
    Body::acceleration = acceleration;
}