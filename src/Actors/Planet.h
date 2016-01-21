//
// Created by mk on 18.01.16.
//

#ifndef ORBIT2_PLANET_H
#define ORBIT2_PLANET_H

#include <oxygine-framework.h>
#include "Rocket.h"

using namespace oxygine;

class Planet : public Body {
private:
    float angle;

    spSprite planet;
    spSprite mark;
public:
    Planet(Resources &resources, float radius=100);

    float radius;
    float gravity;

    bool isCollide(spRocket rocket);

    float angle_velocity;
protected:
    virtual void doUpdate(const UpdateState &us) override;

};
typedef oxygine::intrusive_ptr<Planet> spPlanet;

#endif //ORBIT2_PLANET_H
