//
// Created by mk on 22.01.16.
//

#ifndef ORBIT2_WAYNVG_H
#define ORBIT2_WAYNVG_H

#include "Way.h"

using namespace std;

enum class WayPointType {
    Default,
    Apoapsis,
    Pereapsis
};

class WayNVG : public Way {
private:
    vector<tuple<Vector2, WayPointType >> points;
    Vector2 apoapsis;
    Vector2 pereapsis;
    NVGcontext *vg;
public:
    WayNVG(Resources *resources);

    virtual void doRender(const RenderState &rs) override;

    virtual ~WayNVG();

    virtual void addPoint(Vector2 point, WayPointType type);
    virtual void addPoint(Vector2 point) override;

    virtual void clear() override;
};
typedef intrusive_ptr<WayNVG> spWayNVG;


#endif //ORBIT2_WAYNVG_H
