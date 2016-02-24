#include "SpaceShip.h"

SpaceShip::SpaceShip()
{
    //ctor
    speed = 0;
    launched = false;
    mars = NULL;
}

float SpaceShip::getDistanceFromOrigin()
{
    Vector3 dist = getAbsolutePosition();
    return sqrt(dist.x*dist.x + dist.y*dist.y+dist.z*dist.z);
}

void SpaceShip::update()
{
    // if not launched just do regular update
    if (!launched) {
        SceneObject::update();
        return;
    }

    // properties to right angle triangle
    Vector3 h_dir = mars->getAbsolutePosition() - getAbsolutePosition();                // hypotenuse as a vector
    float hypotenuse    = h_dir.getMagnitude();                                         // length of the hypotenuse
    float opposite      = offset.z;                                                     // length of the opposite side
    float theta         = asin(opposite / hypotenuse) * TO_DEG;                         // angle betwee hypotenuse and adjacent

    // parent to mars if within orbit range
    if (hypotenuse <= offset.z) {

        position = getAbsolutePosition() - mars->getAbsolutePosition(); // convert absolute position to relative
        orbitAngle = atan2(position.x,position.z) * TO_DEG;             // calculate orbitAngle using relative position

        // remove from old parent and attatch to mars
        detachFromParent();
        mars->addChild(this);
        orbitSpeed.y = MARS_ROTATION_SPEED + 0.04;
        rotationSpeed.y = MARS_ROTATION_SPEED + 0.04;
        launched = false;
    } else {

        Vector3 velocity = h_dir;   // vector from ship to mars
        velocity.rotateY(-theta);   // rotate by -theta to get the get of the right tangent
        velocity.normalise();       // normalise to get length of 1
        velocity *= (speed / 60);   // get position delta for current frame

        position += velocity;       // add delta to get new position

        // make space ship face towards tangent/destination
        rotation.y  = atan2(-velocity.z,velocity.x) * TO_DEG;
    }


}
