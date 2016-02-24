#include "SkyBox.h"

void gluSphere();

void SkyBox::drawModel()
{
    glColor4f(colour.r,colour.g,colour.b,colour.a);
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricTexture(qobj,true);
    gluSphere(qobj,2,64,64);
}
