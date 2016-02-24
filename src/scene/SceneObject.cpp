#include "SceneObject.h"

bool SceneObject::drawAxis = true;

SceneObject::SceneObject()
{
    parent      = NULL;
	lighting    = true;
	orbitAngle  = 0;
	cullFace    = GL_BACK;
	scale       = Vector3(1,1,1);
	colour      = Colour4(1,1,1,1);
	enableCulling = true;

	textureID = NO_TEXTURE;//this means it doesn't have a texture ID.
}

SceneObject* SceneObject::getParent()
{
    return parent;
}

Vector3 SceneObject::getAbsolutePosition()
{
    if (parent == NULL)
        return position;

    Vector3 apos = parent->getAbsolutePosition() + position;
    return apos;
}

void SceneObject::update()
{
    orbitAngle += (360 * orbitSpeed.y) / FPS; // angle delta for frame
    //quick fix
    while (orbitAngle >= 360) {
        orbitAngle -= 360;
    }

    float angle = orbitAngle* TO_RAD;
    position.x = (offset.x * cos(angle)) + (offset.z * sin(angle));
    position.z = (offset.x * -sin(angle)) + (offset.z * cos(angle));

    rotation += (rotationSpeed * 360) / FPS;

    updateChildren();
}

void SceneObject::display()
{
    glPushMatrix();
    glTranslatef(position.x,position.y,position.z);

    glPushMatrix();
    glRotatef(rotation.y,0,1,0);//yaw
    glRotatef(rotation.z,0,0,1);//pitch
    glRotatef(rotation.x,1,0,0);//roll
    glScalef(scale.x,scale.y,scale.z);

    if (drawAxis)
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_TEXTURE_2D);
        glBegin(GL_LINES);
            glColor3f(1,0,0);//red
            glVertex3f(0, 0, 0);
            glVertex3f(5, 0, 0); /* draw x-axis */
            glColor3f(0,1,0);//green
            glVertex3f(0, 0, 0);
            glVertex3f(0, 5, 0); /* draw y-axis */
            glColor3f(0,0,1);//blue
            glVertex3f(0, 0, 0);
            glVertex3f(0, 0, 5); /* draw z-axis */
        glEnd();
    }

    if(lighting)
    {
        GLfloat col[4] = { colour.r,colour.g,colour.b, colour.a};
        GLfloat specular[4] = { 1, 1, 1, 1};
        GLfloat shininess = 50;

        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, col);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular );
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
    } else {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);

        glColor3f(colour.r,colour.g,colour.b); // place this some where else
    }

    //deal with the texturing
    if(textureID >= 0)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,textureID);
    } else {
        glDisable(GL_TEXTURE_2D);
    }

    if (enableCulling) {
        glCullFace(cullFace);
        glEnable(GL_CULL_FACE);
    } else {
        glDisable(GL_CULL_FACE);
    }

    drawModel();
    glPopMatrix();
    drawChildren();
    glPopMatrix();

    // unbind the texture and disable texturing
	glBindTexture(GL_TEXTURE,NO_TEXTURE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
}

void SceneObject::addChild(SceneObject* nChild)
{
    nChild->parent = this;
    children.push_back(nChild);
}

void SceneObject::removeChild(SceneObject* nChild)
{
    nChild->parent = NULL;
    vector<SceneObject*>::iterator it = children.begin();
    while (it != children.end()) {

        if (nChild == (*it)) {
            children.erase(it);
            // exit the loop because iterators are now invalid
            it = children.end();
        } else {
            ++it;
        }
    }

}

void SceneObject::detachFromParent()
{
    if (parent != NULL)
        parent->removeChild(this);
}

void SceneObject::drawModel()
{
	glutSolidSphere(0.5,20,20);
}

void SceneObject::drawChildren()
{
    for (unsigned i = 0; i < children.size(); ++i)
    {
        SceneObject* child = children.at(i);
        if(child != NULL)
            child->display();
    }
}

void SceneObject::updateChildren()
{
    for (unsigned i = 0; i < children.size(); ++i)
    {
        SceneObject* child = children.at(i);
        if(child != NULL)
            child->update();
    }
}
