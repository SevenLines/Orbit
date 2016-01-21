//
// Created by mk on 18.01.16.
//

#ifndef ORBIT2_ROCKET_H
#define ORBIT2_ROCKET_H

#include <oxygine-framework.h>
#include "Anchor.h"
#include "Body.h"

using namespace oxygine;
using namespace std;

class Rocket : public Body {
protected:
    float fuel;
    float fuelUsage;
    bool engineActive;
    bool landed;

    spAnchor anchorAcceleration;
    spAnchor anchorVelocity;

    virtual void doUpdate(const UpdateState &us) override;

public:
    Rocket(Resources &resources);
    bool getLanded();


    float accelerationEffeciency;
    virtual void toggleLanded(bool is_landed);

};

typedef oxygine::intrusive_ptr<Rocket> spRocket;


#endif //ORBIT2_ROCKET_H
