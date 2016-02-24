#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "Mesh.h"

class SpaceShip : public Mesh
{
    public:
        SpaceShip();
        virtual ~SpaceShip(){}

    public:
        SceneObject*    mars;

        float           speed;
        bool            launched;

        virtual void update();
        float getDistanceFromOrigin();
};

#endif // SPACESHIP_H
