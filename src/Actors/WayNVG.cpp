//
// Created by mk on 22.01.16.
//
#include <oxygine-framework.h>
#include <nanovg.h>
#include <Material.h>

#define NANOVG_GLES3_IMPLEMENTATION

#include <GLES3/gl3.h>
#include <nanovg_gl.h>

#include "WayNVG.h"

WayNVG::WayNVG(Resources *resources)
        : Way(resources) {
    vg = nvgCreateGLES3(NVG_STENCIL_STROKES | NVG_ANTIALIAS);
}

WayNVG::~WayNVG() {
    if (vg) {
        nvgDeleteGLES3(vg);
    }
}

void WayNVG::addPoint(Vector2 point, WayPointType type) {
    points.push_back(make_tuple(point, type));
}

void WayNVG::addPoint(Vector2 point) {
    addPoint(point, WayPointType::Default);
}


void WayNVG::doRender(const RenderState &rs) {
    Material::setCurrent(0);

    nvgBeginFrame(vg, rs.clip->getWidth(), rs.clip->getHeight(), 1.0); // nanovg drawing begin
    nvgTransform(vg,
                 rs.transform.a,
                 rs.transform.b,
                 rs.transform.c,
                 rs.transform.d,
                 rs.transform.x,
                 rs.transform.y
    );

    nvgBeginPath(vg);
    NVGcolor col = nvgRGBA(20, 204, 255, 255); // pick another color
    bool first = true;

    Vector2 pereapsis(NAN, NAN), apoapsis(NAN, NAN);
    for (auto& point_info : points) {
        Vector2 point;
        WayPointType type;
        tie(point, type) = point_info;

        switch(type) {
            case WayPointType::Apoapsis: apoapsis = point; break;
            case WayPointType::Pereapsis: pereapsis = point; break;
        }

        if (first) {
            first = false;
            nvgMoveTo(vg, point.x, point.y);
        } else {
            nvgLineTo(vg, point.x, point.y);
        }
    }
    nvgStrokeWidth(vg, 5);
    nvgStrokeColor(vg, col);
    nvgStroke(vg);

    if (!isnan(pereapsis.x)) {
        nvgBeginPath(vg);
        nvgCircle(vg, pereapsis.x, pereapsis.y, 10);
        nvgFillColor(vg, nvgRGB(20, 255, 255));
        nvgFill(vg);
        nvgStrokeColor(vg, nvgRGB(20, 204, 255));
        nvgStroke(vg);
    }

    if (!isnan(pereapsis.x)) {
        nvgBeginPath(vg);
        nvgCircle(vg, apoapsis.x, apoapsis.y, 10);
        nvgFillColor(vg, nvgRGB(255, 20, 255));
        nvgFill(vg);
        nvgStrokeColor(vg, nvgRGB(20, 204, 255));
        nvgStroke(vg);
    }

    nvgEndFrame(vg); // nanovg draw end
}

void WayNVG::clear() {
    points.clear();
}
