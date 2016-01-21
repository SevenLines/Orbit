//
// Created by mk on 18.01.16.
//

#include "Player.h"

Player::Player(Resources &resources) : Rocket(resources) {
    edtInfo = new TextField();
    edtInfo->setPosition(getStage()->getSize() - Vector2(10, 10));
    edtInfo->setAnchor(0, 0);

    playerWay = new Way(&resources);
    playerWay->setPosition(getPosition());

    TextStyle style;
    style.font = resources.getResFont("main")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_BOTTOM;
    style.hAlign = TextStyle::HALIGN_RIGHT;

    edtInfo->setStyle(style);
    getStage()->addChild(edtInfo);
}

void Player::doUpdate(const UpdateState &us) {
    Rocket::doUpdate(us);
    if (getParent() && !playerWay->getParent()) {
        getParent()->addChild(playerWay);
    }
    if (!landed) {
        playerWay->addPoint(getPosition());
    }
}

void Player::toggleLanded(bool is_landed) {
    Rocket::toggleLanded(is_landed);
    if (landed) {
        spActor child = playerWay->getFirstChild();
        while (child)
        {
            spTweenQueue tweenQueue = new TweenQueue();
            tweenQueue->add(TweenAlpha(0), 100, 1);
            tweenQueue->setDetachActor(true);
            child->addTween(tweenQueue);
            child = child->getNextSibling();
        }
    } else {
        playerWay->setPosition(0, 0);
    }
}
