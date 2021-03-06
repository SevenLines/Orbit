//
// Created by mk on 18.01.16.
//

#include "Planet.h"
using  namespace std;

Planet::Planet(Resources &resources, float radius) {
    angle_velocity = 2;
    angle = 0;
    this->radius = radius;
    auto diameter = 2 * this->radius;
    setGravity(9.8);

    planet = new Sprite();
    planet->setResAnim(resources.getResAnim("earth"));
    planet->setAnchor(0.5, 0.5);

    auto size = planet->getSize();
    planet->setScale(diameter / size.x, diameter / size.y);
    this->addChild(planet);
}



void Planet::doUpdate(const UpdateState &us) {
    Actor::doUpdate(us);
    angle += angle_velocity * us.dt / 1000;
    planet->setRotation(angle);
}

bool Planet::isCollide(Vector2 position) {
    auto length = (getPosition() - position).length();
    return length < radius;
}

float Planet::getGravity() const {
    return gravity;
}

void Planet::setGravity(float gravity) {
    Planet::gravity = gravity;
}