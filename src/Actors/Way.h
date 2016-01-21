//
// Created by mk on 19.01.16.
//

#ifndef ORBIT2_WAY_H
#define ORBIT2_WAY_H


#include <Actor.h>
#include <res/Resources.h>
#include <Sprite.h>
#include "../Helpers/types.h"

using namespace std;
using namespace oxygine;

class Way : public Actor {
private:
    Resources* resources;
    ResAnim *lineSprite;
//    NVGcontext *nvGcontext;

    vector<Vector2> points;

    bool hide;
public:
    Vector2 lastPoint;
    float minLength;
    Way(Resources *resources, string spriteName="dashed", bool hide=true);

    void addPoint(Vector2 point);

    void clear();


    virtual ~Way();

};
typedef intrusive_ptr<Way> spWay;

#endif //ORBIT2_WAY_H
