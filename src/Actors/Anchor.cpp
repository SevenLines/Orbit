//
// Created by mk on 18.01.16.
//

#include "Anchor.h"

Anchor::Anchor(Resources &resources) : Actor() {
    spriteLine = new Sprite();
    spriteAnchor = new Sprite();
    spriteOrigin = new Sprite();

    spriteOrigin->setResAnim(resources.getResAnim("mark"));
    spriteLine->setResAnim(resources.getResAnim("line"));
    spriteAnchor->setResAnim(resources.getResAnim("anchor"));

    spriteAnchor->setAnchor(0.5, 0.5);
    spriteLine->setAnchor(0, 0.5);
    spriteOrigin->setAnchor(0.5, 0.5);

    addChild(spriteLine);
    addChild(spriteAnchor);

    spriteLine->setPosition(0, 0);
}

void Anchor::doUpdate(const UpdateState &us) {
    Actor::doUpdate(us);
}

void Anchor::setLength(float newLength) {
    length = newLength;
    spriteLine->setScale(length, 3);
    spriteAnchor->setPosition(length, 0);
}

void Anchor::setVector(Vector2 vector2) {
    setLength(vector2.length());
    setRotation((float) atan2(vector2.y, vector2.x));
}

void Anchor::setColor(Color color) {
    spriteAnchor->setColor(color);
    spriteLine->setColor(color);
    spriteOrigin->setColor(color);
}
