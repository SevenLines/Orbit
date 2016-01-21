//
// Created by mk on 19.01.16.
//

#include "Body.h"

Vector2 Body::getNextPosition(float delta_time) {
    return getPosition() + velocity * delta_time;
}
