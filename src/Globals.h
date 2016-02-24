#ifndef GLOBALS_H
#define GLOBALS_H

#include "GL/glut.h"
#include "utils/structs.h"
#include "consts.h"

class OpenGLApp;

class Globals
{
    public:

        OpenGLApp* app;

        float screenWidth;
        float screenHeight;

        Vector2 deltaRotation;
        Vector2 clickPosition;

        Viewport    viewMain;
        Viewport    view2;
        Viewport    view3;
        Viewport    view4;

        Vector2 mouse;

        GLuint texture[MAX_NO_TEXTURES];
};

extern Globals g;

#endif // GLOBALS_H
