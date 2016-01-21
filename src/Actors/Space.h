//
// Created by mk on 17.01.16.
//

#ifndef ORBIT2_MAINACTOR_H
#define ORBIT2_MAINACTOR_H


#include <oxygine-framework.h>
#include "Planet.h"
#include "Player.h"
#include "GlobalState.h"
#include "Anchor.h"
#include "Way.h"

using namespace oxygine;


class Space : public Actor
{

private:

    spPlayer player;
    spPlanet planet;
    spWay orbitWay;
    spWay playerWay;

    GlobalState *globalState;
    bool touchDown;

    Vector2 addAcceleration;
    Vector2 pointerPosition;
    Vector2 spacePosition;
public:
    Space(Resources &gameResources, GlobalState *state);
    void zoom(float k);

protected:
    virtual void doUpdate(const UpdateState &us) override;
    void showOrbit();
    spAnchor anchor;

};
//declare spMainActor as intrusive_ptr holder of Space
typedef oxygine::intrusive_ptr<Space> spSpace;


#endif //ORBIT2_MAINACTOR_H