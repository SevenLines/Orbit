//
// Created by mk on 17.01.16.
//

#include "Space.h"
#include <boost/format.hpp>
#include <iostream>

using namespace oxygine;
using namespace std;
using namespace boost;


void Space::doUpdate(const UpdateState &us) {
    Actor::doUpdate(us);

    auto playerPos = player->getPosition();
    auto delta = (float) us.dt / 1000;
//    auto planetPos = planet->getPosition();
//
//
//    auto distance = (planetPos - playerPos).length();
//    auto direct = (planetPos - playerPos).normalized();
//    auto gravityVector = direct * planet->gravity / pow(distance / planet->radius, 2);
//
//    player->acceleration = gravityVector;
    player->acceleration = {0, 0};
    auto velocityVector = player->velocity.normalized();

    if (this->globalState->keys_pressed[SDL_SCANCODE_A]) {
        player->acceleration += Vector2(velocityVector.y, -velocityVector.x) * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_D]) {
        player->acceleration -= Vector2(velocityVector.y, -velocityVector.x) * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_W]) {
        player->acceleration += velocityVector * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_S]) {
        player->acceleration -= velocityVector * 15;
    }

    if (addAcceleration.length()) {
        player->acceleration = addAcceleration;
    }

    auto acceleration = player->acceleration;
    auto velocity = player->velocity;
    spPlanet collidedPlanet;
    Vector2 nextPosition;
    map<int, BodyInfo> bodyInfos;

    tie(nextPosition, collidedPlanet, bodyInfos) = getNextPosition(delta, playerPos, acceleration, velocity);

    player->setPosition(nextPosition);
    player->velocity = velocity;
    player->acceleration = acceleration;

    player->toggleLanded(bool(collidedPlanet));
//
    auto info = format("скорость: %1$.1f\nвысота: %2%;");
    info % player->velocity.length() % 0;
    player->edtInfo->setText(info.str());
//
//    player->velocity += player->acceleration * delta * player->accelerationEffeciency;
//    player->setPosition(player->getNextPosition(delta));
//    planet->setPosition(planet->getPosition() + planet->velocity * delta);

    showOrbit();
}

Space::Space(Resources &gameResources, GlobalState *state) {
    globalState = state;

    spPlanet basePlanet = new Planet(gameResources, 150);
    basePlanet->setGravity(10);
//    basePlanet->setVelocity({1, 1});
    addPlanet(basePlanet, getStage()->getSize() / 2);

    spPlanet planet = new Planet(gameResources, 100);
    planet->setGravity(100);
    addPlanet(planet, getStage()->getSize() / 2 + Vector2{800, 0});

//    planet = new Planet(gameResources, 300);
//    planet->setGravity(10.0f);
//    addPlanet(planet, getStage()->getSize() / 2 + Vector2{800, 500});

    player = new Player(gameResources);
    orbitWayNVG = new WayNVG(&gameResources);

    addChild(player);
    getStage()->addChild(orbitWayNVG);

    player->setPosition(basePlanet->getPosition() + basePlanet->getSize() + Vector2(-basePlanet->radius, 0));

    getStage()->addEventListener(TouchEvent::MOVE, (const EventCallback &) [=](Event *event) {
        auto touchEvent = dynamic_cast<TouchEvent *>(event);
        auto lastPointerPosition = pointerPosition;

        pointerPosition = touchEvent->getPointer()->getPosition();
        spacePosition = global2local(pointerPosition);

        if (touchEvent->getPointer()->isPressed(MouseButton_Left)) {
            auto offset = lastPointerPosition - pointerPosition;
            setPosition(getPosition() - offset);
        }
    });

    getStage()->addEventListener(TouchEvent::WHEEL_DOWN, (const EventCallback &) [=](Event *event) {
        zoom(7.0f / 8);
    });
    getStage()->addEventListener(TouchEvent::WHEEL_UP, (const EventCallback &) [=](Event *event) {
        zoom(8.0f / 7);
    });

    getStage()->addEventListener(TouchEvent::TOUCH_UP, (const EventCallback &) [=](Event *event) {
        touchDown = false;
        addAcceleration = {0, 0};
    });
}

void Space::zoom(float k) {
    auto local = global2local(pointerPosition);
    touchDown = false;
    addAcceleration = {0, 0};

    Vector2 scale = getScale();
    setScale(scale * k);

    auto newPointerPosition = local2global(local);
    setPosition(getPosition() + pointerPosition - newPointerPosition);
}

void Space::showOrbit() {
    orbitWayNVG->clear();

    if (player->getLanded()) {
        return;
    }

    auto delta = 0.01;
    int i = 0;

    Vector2 playerPos = player->getPosition();
    Vector2 lastPos = playerPos;
    orbitWayNVG->addPoint(local2global(playerPos));

    Vector2 acceleration = player->acceleration;
    Vector2 velocity = player->velocity;

    while (i < 10000) {
        acceleration = {0, 0};
        spPlanet collidedPlanet;
        map<int, BodyInfo> bodyInfos;
        tie(playerPos, collidedPlanet, bodyInfos) = getNextPosition(delta, playerPos, acceleration, velocity);

        if (collidedPlanet) {
            break;
        }

        if ((lastPos - playerPos).length() > 10) {
            orbitWayNVG->addPoint(local2global(playerPos), WayPointType::Default);
            lastPos = playerPos;
        }
        ++i;
    }
}


tuple<Vector2, spPlanet, map<int, BodyInfo>>
Space::getNextPosition(double delta,
                       Vector2 objectPosition,
                       Vector2 &objectAcceleration,
                       Vector2 &objectVelocity) {
    spPlanet collidedPlanet;


    vector<BodyInfo> bodyInfos(planets.size());
    map<int, BodyInfo> bodyInfoMap;

    for (auto planet : planets) {
        bodyInfoMap.emplace(planet->getObjectID(), make_tuple(
                planet->getPosition(),
                planet->getVelocity(),
                planet->getAcceleration()
        ));
    }

    for (auto planet : planets) {
        Vector2 planetPos, planetAcceleration, planetVelocity;
        BodyInfo info = bodyInfoMap.at(planet->getObjectID());
        tie(planetPos, planetAcceleration, planetVelocity) = info;

        auto direct = (planetPos - objectPosition).normalized();
        auto distance = (planetPos - objectPosition).length();
        auto angle = atan2(direct.x, direct.y);
        auto gravityVector = direct * planet->gravity / pow(distance / planet->radius, 2);

        if (planet->isCollide(objectPosition)) {
            objectPosition = planet->getPosition() - direct * (planet->radius);

            collidedPlanet = planet;

            float k = planet->angle_velocity * planet->gravity;

            objectVelocity = Vector2(
                    direct.y * k,
                    -direct.x * k
            ) + planet->velocity;

            objectAcceleration += gravityVector;

            break;
        }

        objectAcceleration += gravityVector;

        planetPos = planetPos + planetVelocity * delta;
        planetAcceleration = {0, 0};
        planetVelocity += planetAcceleration * delta;

        bodyInfoMap.at(planet->getObjectID())
                = make_tuple(planetPos, planetAcceleration, planetVelocity);
    }
    objectPosition = objectPosition + objectVelocity * delta;
    objectVelocity += objectAcceleration * delta;

    return make_tuple(objectPosition, collidedPlanet, bodyInfoMap);
}

void Space::addPlanet(spPlanet planet, Vector2 position) {
    planets.push_back(planet);
    planet->setPosition(position);
    addChild(planet);
}
