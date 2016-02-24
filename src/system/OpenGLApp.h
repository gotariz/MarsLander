#ifndef OPENGLAPP_H
#define OPENGLAPP_H

#include "general.h"
#include "system/glCamera.h"
#include "scene/SceneObject.h"
#include "scene/QuadSphere.h"
#include "scene/SpaceShip.h"
#include "scene/OrbitRing.h"
#include "scene/SkyBox.h"
#include "scene/Mesh.h"

class OpenGLApp
{
    public:
        OpenGLApp();
        virtual ~OpenGLApp();

    public:
        vector<SceneObject*> sceneRoot;
        vector<RawSceneData> myRawData;
        glCamera camera1;
        glCamera camera2;
        glCamera camera3;
        glCamera camera4;

        glCamera*       activeCamera;
        //SpaceShip*      ss;
        //SceneObject*    m;
        //SceneObject*    e;
        SceneObject*    camera1Anchor;

        SceneObject*    objSun;
        SceneObject*    objEarth;
        SceneObject*    objMoon;
        SceneObject*    objMars;
        SceneObject*    objPhobos;
        SceneObject*    objDeimos;
        SpaceShip*      objSpaceship;
    public:
        void initGlobals();
        void initOpenGL(int argc, char** argv);
        void run();

        void setupCamera1();
        void setupCamera2();
        void setupCamera3();
        void setupCamera4();
        void setupGUI();
        void drawGUI();

        void drawScene();
        void animateScene();

        void loadScene();
        int loadTexture(const char* filename);
};

#endif // OPENGLAPP_H
