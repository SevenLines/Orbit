//
// Created by mk on 18.01.16.
//

#ifndef ORBIT2_ANCHOR_H
#define ORBIT2_ANCHOR_H

#include <oxygine-framework.h>

using namespace oxygine;

class Anchor : public Actor{
    spSprite spriteLine;
    spSprite spriteAnchor;
    spSprite spriteOrigin;
    float length;

public:
    Anchor(Resources &resources);
    void setLength(float newLength);
    void setVector(Vector2 vector);
    void setColor(Color color);

protected:
    virtual void doUpdate(const UpdateState &us) override;
};
typedef intrusive_ptr<Anchor> spAnchor;


#endif //ORBIT2_ANCHOR_H
