#include "OrbitRing.h"

void OrbitRing::drawModel()
{
    int numLines    = 1000;
    Vector3 point   = Vector3(0,0,radius);

    glColor4f(colour.r,colour.g,colour.b,colour.a);
    glBegin(GL_LINE_LOOP);
        for (int i = 0; i < numLines; ++i)
        {
            glVertex3f(point.x + offset.x, point.y + offset.y, point.z + offset.z);
            point.rotateY(360.f / numLines);
        }
    glEnd();
}

