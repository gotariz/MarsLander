#include "QuadSphere.h"

void QuadSphere::drawModel()
{
    glColor4f(colour.r,colour.g,colour.b,colour.a);
    GLUquadric* qobj = gluNewQuadric();
    gluQuadricTexture(qobj,true);
    gluSphere(qobj,0.5,64,64);
}
