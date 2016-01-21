#include <oxygine-framework.h>
#include "Actors/Space.h"
#include "Actors/GlobalState.h"
#include <functional>
#pragma clang diagnostic push
using namespace oxygine;

Resources gameResources;

void preinit() {}

//called from entry_point.cpp
void init()
{
    GlobalState *globalState = new GlobalState();
    //load xml file with resources definition
    gameResources.loadXML("res.xml");

    //lets create our client code simple actor
    //spMainActor was defined above as smart intrusive pointer (read more: http://www.boost.org/doc/libs/1_57_0/libs/smart_ptr/intrusive_ptr.html)
    spSpace actor = new Space(gameResources, globalState);

    //and add it to Stage as child
    getStage()->addChild(actor);
    getStage()->addEventListener(KeyEvent::KEY_DOWN, (const EventCallback &) [=](Event *e) {
        KeyEvent *event = dynamic_cast<KeyEvent *>(e);
        globalState->keys_pressed[event->data->keysym.scancode] = true;
    });

    getStage()->addEventListener(KeyEvent::KEY_UP, (const EventCallback &) [=](Event *e) {
        KeyEvent *event = dynamic_cast<KeyEvent *>(e);
        globalState->keys_pressed[event->data->keysym.scancode] = false;
    });

}


//called each frame from entry_point.cpp
void update()
{
}

//called each frame from entry_point.cpp
void destroy()
{
    //free previously loaded resources
    gameResources.free();
}

