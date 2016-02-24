#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "general.h"

class SceneObject
{
    public:
        SceneObject();
        virtual ~SceneObject(){}

    public:
        static bool drawAxis;

        int     cullFace;
        int     textureID;
        bool    lighting;
        bool    enableCulling;
        Colour4 colour;

        Vector3 position;
        Vector3 rotation;
        Vector3 offset;
        Vector3 scale;
        Vector3 rotationSpeed;
        Vector3 orbitSpeed;
        float   orbitAngle;


        virtual void update();
        virtual void display();
        virtual void addChild(SceneObject* nChild);
        virtual void removeChild(SceneObject* nChild);
        virtual void detachFromParent();
        virtual Vector3 getAbsolutePosition();

        SceneObject* getParent();

        protected:
            vector<SceneObject*> children;
            SceneObject* parent;

            virtual void drawModel();
            virtual void drawChildren();
            virtual void updateChildren();
};

#endif // SCENEOBJECT_H
