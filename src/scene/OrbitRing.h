#ifndef ORBITRING_H
#define ORBITRING_H

#include "SceneObject.h"


class OrbitRing : public SceneObject
{
    public:
        float radius;
    protected:
        virtual void drawModel();
};

#endif // ORBITRING_H
