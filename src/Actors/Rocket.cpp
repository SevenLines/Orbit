//
// Created by mk on 18.01.16.
//

#include "Rocket.h"

Rocket::Rocket(Resources &resources) :
        fuel(100),
        accelerationEffeciency(1),
        fuelUsage(0.1) {
    spSprite sprite = new Sprite();
    sprite->setResAnim(resources.getResAnim("rocket"));
    sprite->setAnchor(0.5, 0.5);

    anchorAcceleration = new Anchor(resources);
    anchorAcceleration->setColor(Color::YellowGreen);

    anchorVelocity = new Anchor(resources);
    anchorVelocity->setColor(Color::IndianRed);

    addChild(anchorAcceleration);
    addChild(anchorVelocity);
    addChild(sprite);
}

void
Rocket::doUpdate(const UpdateState &us) {
    Actor::doUpdate(us);
//    float delta = (float) us.dt / 1000;
//    if (fuel == 0) {
//        acceleration = {0, 0};
//    } else {
//        float accel = max(acceleration.x, acceleration.y);
//        fuel -= fuelUsage * (accel * delta);
//    }


    anchorAcceleration->setVector(acceleration);
    anchorVelocity->setVector(velocity);
}

void Rocket::toggleLanded(bool is_landed) {
    landed = is_landed;
}

bool Rocket::getLanded() {
    return landed;
}
