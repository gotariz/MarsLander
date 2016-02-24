#ifndef SKYBOX_H
#define SKYBOX_H

#include "general.h"
#include "QuadSphere.h"

class SkyBox : public QuadSphere
{
    public:
        SkyBox(){}
        virtual ~SkyBox(){}
    protected:
        virtual void drawModel();
};

#endif // SKYBOX_H
