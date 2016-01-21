//
// Created by mk on 19.01.16.
//
#include <iostream>
#include <TweenQueue.h>
#include <RenderState.h>
#include <nanovg.h>
#include "Way.h"

#define NANOVG_GLES2_IMPLEMENTATION

#include <GLES2/gl2.h>
#include <nanovg_gl.h>

using namespace std;

Way::Way(Resources *resources, string spriteName, bool hide)
    : minLength(8) {
    this->hide = hide;
    lineSprite = resources->getResAnim(spriteName);

//    nvGcontext = nvgCreateGLES2(NVG_STENCIL_STROKES | NVG_ANTIALIAS | NVG_DEBUG);
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
        addChild(sprite);

        if (this->hide) {
            spTweenQueue tweenQueue = new TweenQueue();
            tweenQueue->setDelay(1000);
            tweenQueue->add(TweenAlpha(20), 500, 1);
            sprite->addTween(tweenQueue);
            tweenQueue->setDetachActor(true);
        }
        points.push_back(point);
        lastPoint = point;
    }
}


//void Way::doRender(const RenderState &rs) {
////    Actor::doRender(rs);
//
////    _vstyle._apply(rs);
////    rs.renderer->setTexture(Renderer::white, 0); // needed
//    int width = rs.clip->getWidth();
//    int height = rs.clip->getHeight();
//    float pxRatio = 1.0;
//
////    NVGcontext* vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES); // create nanovg context
////
////    glEnable(GL_BLEND); // must be called after the NVGcontext creation!
////    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    nvgBeginFrame(nvGcontext, width, height, pxRatio); // nanovg drawing begin
////    nvgTranslate(nvGcontext,getX(),getY()); // the view position becomes the coordinate system reference point
//
////    NVGcolor bg = nvgRGBA(0,255,0,200); // pick background color
////    nvgFillColor(nvGcontext,bg); // set bg color to use
////    nvgFill(nvGcontext); // fill all the clipped area with the color
//
//    nvgMoveTo(nvGcontext, 0, 0)
//    for (auto point : points) {
//        NVGcolor col = nvgRGBA(255,0,0,128); // pick another color
//    }
//
//    nvgCircle(nvGcontext,500,500,50); // set a circular path
//    nvgFillColor(nvGcontext,col); // set the fill color for the circle
//    nvgFill(nvGcontext); // draw the circle
//
//    nvgEndFrame(nvGcontext); // nanovg draw end
////    nvgDeleteGLES2(vg); // delete nanovg context
//
//    Actor::doRender(rs);
//
//    rs.renderer->resetSettings();
//
//    glEnable(GL_BLEND); // must be called after the NVGcontext creation!
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//}

void Way::clear() {
    points.clear();
    this->removeChildren();
    lastPoint = {0, 0};
}

Way::~Way() {
//    nvgDeleteGLES2(nvGcontext);
}