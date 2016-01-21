//
// Created by mk on 17.01.16.
//

#include "Space.h"
#include <boost/format.hpp>

using namespace oxygine;
using namespace std;
using namespace boost;


void Space::doUpdate(const UpdateState &us) {
    Actor::doUpdate(us);

    auto playerPos = player->getPosition();
    auto planetPos = planet->getPosition();

    auto delta = (float) us.dt / 1000;

    auto distance = (planetPos - playerPos).length();
    auto direct = (planetPos - playerPos).normalized();
    auto gravityVector = direct * planet->gravity / pow(distance / planet->radius, 2);


    if (planet->isCollide(player)) {
        player->setPosition(planet->getPosition() - direct * (planet->radius));
        player->toggleLanded(true);

        float k = planet->angle_velocity * planet->gravity;

        player->velocity = Vector2(
                direct.y * k,
                -direct.x * k
        ) + planet->velocity;
    } else {
        player->toggleLanded(false);
    }

    player->acceleration = gravityVector;

    if (this->globalState->keys_pressed[SDL_SCANCODE_A]) {
        player->acceleration -= direct * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_D]) {
        player->acceleration += direct * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_W]) {
        player->acceleration += player->velocity.normalized() * 15;
    }

    if (this->globalState->keys_pressed[SDL_SCANCODE_S]) {
        player->acceleration -= player->velocity.normalized() * 15;
    }

    if (addAcceleration.length()) {
        player->acceleration = addAcceleration;
    }

    auto info = format("скорость: %1$.1f\nвысота: %2%;");
    info % player->velocity.length() % (int) (distance - planet->radius);
    player->edtInfo->setText(info.str());

    player->velocity += player->acceleration * delta * player->accelerationEffeciency;
    player->setPosition(player->getNextPosition(delta));
    planet->setPosition(planet->getPosition() + planet->velocity * delta);

    showOrbit();
}

Space::Space(Resources &gameResources, GlobalState *state) {
    globalState = state;

    planet = new Planet(gameResources, 150);
    planet->velocity = Vector2{1, 1};
    player = new Player(gameResources);
    orbitWay = new Way(&gameResources, "line_2", false);

    addChild(orbitWay);
    addChild(planet);
    addChild(player);

    planet->setPosition(getStage()->getSize() / 2);
    player->setPosition(planet->getPosition() + planet->getSize() + Vector2(-planet->radius, 0));

    auto callback = [=](Event *event) {
//        addAcceleration = spacePosition - player->getPosition();
    };

    getStage()->addEventListener(TouchEvent::TOUCH_DOWN, (const EventCallback &) [=](Event *event) {
        auto touchEvent = dynamic_cast<TouchEvent *>(event);
        if (touchEvent->getPointer()->isPressed(MouseButton_Left)) {
            touchDown = true;
            callback(event);
        }
    });

    getStage()->addEventListener(TouchEvent::MOVE, (const EventCallback &) [=](Event *event) {
        auto touchEvent = dynamic_cast<TouchEvent *>(event);
        auto lastPointerPosition = pointerPosition;

        pointerPosition = touchEvent->getPointer()->getPosition();
        spacePosition = global2local(pointerPosition);

        if (touchDown) {
            callback(event);
        }

        if (touchEvent->getPointer()->isPressed(MouseButton_Middle)) {
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
    Vector2 playerPos = player->getPosition();
    Vector2 planetPos = planet->getPosition();
    Vector2 lastPos = playerPos;

    Vector2 acceleration = player->acceleration;
    Vector2 velocity = player->velocity;
    auto delta = 1.0f / 100;
    int i = 0;

    orbitWay->clear();
    orbitWay->minLength = 5;
    orbitWay->setPosition(player->getPosition());

    if (player->getLanded()) {
        return;
    }

    while (i < 10000) {
        auto distance = (planetPos - playerPos).length();
        auto direct = (planetPos - playerPos).normalized();
        auto gravityVector = direct * planet->gravity / pow(distance / planet->radius, 2);

        acceleration = gravityVector;

        velocity += acceleration * delta * player->accelerationEffeciency;
        playerPos = playerPos + velocity * delta ;
        planetPos = planet->getPosition() + planet->velocity * delta;

        orbitWay->addPoint(playerPos);
        if (i > 0 && abs((player->getPosition() - playerPos).length()) < 0.1) {
            break;
        }
        ++i;
    }
}
