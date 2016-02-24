#ifndef GLCAMERA_H
#define GLCAMERA_H

#include "general.h"

class glCamera
{
    public:
        glCamera();
        virtual ~glCamera(){}

    protected:
        float   yaw;
        float   pitch;

    public:

        Vector3 up;
        Vector3 lookat;
        float   pitchLimit;

        Viewport*   viewport;       // the view port associated with this camera

        float tempYaw;              //
        float tempPitch;            //

        Vector3 defaultPosition;    // position relative to virtual parent
        Vector3 positionOffset;     // absolute position of virtual parent
        float   rotationOffset;     // rotation of virtual parent

        bool enablePitchRotation;   // enables rotation of the camera around the x axis
        bool enableYawRotation;     // enables rotation of the camera around the y axis
        bool enableUpRotation;      // enables rotation of the up vector

        void    call_gluLookAt();

        float   getYaw();
        float   getPitch();
        Vector3 getPosition();
        Vector3 getRotation();

        void    setPitch(float nPitch);
        void    setYaw(float nYaw);
        void    incrementPitch(float inc);
        void    incrementYaw(float inc);
        void    activateViewport();
        void    setViewport(Viewport* vp);
};

#endif // GLCAMERA_H
