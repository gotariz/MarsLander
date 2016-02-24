#include "glCamera.h"

glCamera::glCamera()
{
    // initialiser lists are annoying
    yaw             = 0;
    pitch           = 0;
    tempPitch       = 0;
    tempYaw         = 0;
    pitchLimit      = 89.999;
    rotationOffset  = 0;

    enablePitchRotation = true;
    enableYawRotation   = true;
    enableUpRotation    = false;
}

void glCamera::setViewport(Viewport* vp)
{
    viewport = vp;
    vp->c = this;
}

void glCamera::activateViewport()
{
    glViewport(
               viewport->r.x,
               viewport->r.y,
               viewport->r.w,
               viewport->r.h
               );
}

void glCamera::call_gluLookAt()
{
    Vector3 position = getPosition();
    position.rotateY(rotationOffset);
    gluLookAt(
              position.x + positionOffset.x,
              position.y + positionOffset.y,
              position.z + positionOffset.z,
			  lookat.x + positionOffset.x,
			  lookat.y + positionOffset.y,
			  lookat.z + positionOffset.z,
			  up.x,
			  up.y,
			  up.z);
}

void glCamera::incrementPitch(float inc)
{
    if (enablePitchRotation)
        setPitch(pitch + inc);
}

void glCamera::incrementYaw(float inc)
{
    if (enableYawRotation)
        setYaw(yaw + inc);
}

void glCamera::setPitch(float nPitch)
{
    if (enablePitchRotation) {
        pitch = nPitch;
        pitch = min(pitch,pitchLimit);
        pitch = max(pitch,-pitchLimit);
    }
}

void glCamera::setYaw(float nYaw)
{
    if (!enableYawRotation) return; // exit if yaw rotation is not enabled

    yaw = nYaw;

    if (enableUpRotation) {
        float ox = 0;
        float oz = 1;
        float yawRadians = yaw * TO_RAD;

        up.x = ox * cos(yawRadians) + oz * sin(yawRadians);
        up.z = ox * -sin(yawRadians) + oz * cos(yawRadians);
    }
}

// get the position of the camera taking into account the rotations
Vector3 glCamera::getPosition()
{
    // rotations are done in world co-ordinates so they should
    // be done in the order roll, pitch, yaw
    Vector3 position;

    // convert pitch to radians for trig functions
    float pitchRadians = pitch * (PI / 180.f);
    // rotate position after pitch rotation
    position.y = (defaultPosition.y * cos(pitchRadians)) + (defaultPosition.z * -sin(pitchRadians));
    position.z = (defaultPosition.y * sin(pitchRadians)) + (defaultPosition.z * cos(pitchRadians));

    // convert yaw to radians for trig functions
    float yawRadians = yaw * (PI / 180.f);
    // calculate position after yaw rotation
    position.x = (defaultPosition.x * cos(yawRadians)) + (position.z * sin(yawRadians));
    position.z = (defaultPosition.x * -sin(yawRadians)) + (position.z * cos(yawRadians));

	return position;
}

Vector3 glCamera::getRotation()
{
    return Vector3(pitch,yaw,0);
}

float glCamera::getYaw()
{
    return yaw;
}

float glCamera::getPitch()
{
    return pitch;
}
