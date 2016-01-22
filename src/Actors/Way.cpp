//
// Created by mk on 19.01.16.
//
#include <iostream>
#include <TweenQueue.h>
#include <RenderState.h>
#include "Way.h"


using namespace std;

Way::Way(Resources *resources, string spriteName, bool hide)
    : minLength(8) {
    this->hide = hide;
    lineSprite = resources->getResAnim(spriteName);
}

void Way::addPoint(Vector2 point) {
    point = point - getPosition();
    auto vector2 = point - lastPoint;

    if (vector2.length() > minLength) {
        spSprite sprite = new Sprite();
        sprite->setAnimFrame(lineSprite);
        sprite->getAnimFrame().getDiffuse().base->setLinearFilter(false);
        sprite->setScale(vector2.length() / 4, 3);
        sprite->setRotation(atan2(vector2.y, vector2.x));
        sprite->setPosition(point);
        sprite->setAnchor(0, 0.5);
        addChild(sprite);

        if (this->hide) {
            spTweenQueue tweenQueue = new TweenQueue();
            tweenQueue->setDelay(1000);
            tweenQueue->add(TweenAlpha(20), 500, 1);
            sprite->addTween(tweenQueue);
            tweenQueue->setDetachActor(true);
        }
        lastPoint = point;
    }
}

void Way::clear() {
    this->removeChildren();
    lastPoint = {0, 0};
}

Way::~Way() {
}