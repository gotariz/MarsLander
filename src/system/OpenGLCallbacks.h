#ifndef OPENGLCALLBACKS_H_INCLUDED
#define OPENGLCALLBACKS_H_INCLUDED

// declarations
void drawAxis();
void glCallback_display();
void glCallback_reshape(int width, int height);
void glCallback_motion(int x, int y);
void glCallback_passiveMotion(int x, int y);
void glCallback_mouse(int button, int state, int x, int y);
void glCallback_keyboard(unsigned char key, int x, int y);

void drawAxis()
{
    glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glBegin(GL_LINES);
          glColor3f(1,0,0);//red
		  glVertex3f(0, 0, 0);
		  glVertex3f(100, 0, 0); /* draw x-axis */
		  glColor3f(0,1,0);//green
		  glVertex3f(0, 0, 0);
		  glVertex3f(0, 100, 0); /* draw y-axis */
		  glColor3f(0,0,1);//blue
		  glVertex3f(0, 0, 0);
		  glVertex3f(0, 0, 100); /* draw z-axis */
	glEnd();
}

void animateSceneTimer(int milliseconds)
{
    g.app->animateScene();
    glutTimerFunc(milliseconds,animateSceneTimer,milliseconds);
}

void glCallback_display()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	//draw the main viewport
	g.app->setupCamera1();
    g.app->drawScene();
    drawAxis();

    g.app->setupCamera2();
    g.app->drawScene();
    drawAxis();

    g.app->setupCamera3();
    g.app->drawScene();
    drawAxis();

    g.app->setupCamera4();
    g.app->drawScene();
    drawAxis();

    g.app->setupGUI();
    g.app->drawGUI();

	//OpenGL house cleaning
	glFlush();//put everything on the pipeline
	glutPostRedisplay();//post the ready scenes.
	glutSwapBuffers();//swap the buffers
}

void glCallback_reshape(int width, int height)
{
    g.screenWidth = width;
    g.screenHeight = height;

    float smallHeight = height * 0.25;

    g.viewMain.r    = Rec(0,smallHeight,width,height-smallHeight);
    g.view2.r       = Rec(0,0,width/3,smallHeight);
    g.view3.r       = Rec(width/3,0,width/3,smallHeight);
    g.view4.r       = Rec((width/3)*2,0,width/3,smallHeight);


    glCallback_display();
}

void glCallback_motion(int x, int y)
{
    g.mouse.set(x,g.screenHeight - y - 1);

    if (g.app->activeCamera != NULL) {
        g.deltaRotation = Vector2(x,y) - g.clickPosition;
        g.deltaRotation *= CAMERA_SENSITIVITY;
        g.app->activeCamera->setPitch( g.app->activeCamera->tempPitch + -g.deltaRotation.y );
        g.app->activeCamera->setYaw( g.app->activeCamera->tempYaw + -g.deltaRotation.x );
    }
}

void glCallback_passiveMotion(int x, int y)
{
    g.mouse.set(x,g.screenHeight - y - 1);
}

void glCallback_mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON) {

            if (g.viewMain.r.isInside(g.mouse)) {
                g.app->activeCamera = g.viewMain.c;
            } else if (g.view2.r.isInside(g.mouse)) {
                g.app->activeCamera = g.view2.c;
            } else if (g.view3.r.isInside(g.mouse)) {
                g.app->activeCamera = g.view3.c;
            } else if (g.view4.r.isInside(g.mouse)) {
                g.app->activeCamera = g.view4.c;
            }


            g.clickPosition = Vector2(x,y);
            g.deltaRotation = Vector2(0,0);

            if (g.app->activeCamera != NULL) {
                g.app->activeCamera->tempPitch = g.app->activeCamera->getPitch();
                g.app->activeCamera->tempYaw = g.app->activeCamera->getYaw();
            }

        } else if (button == GLUT_RIGHT_BUTTON) {
            if (g.view2.r.isInside(g.mouse)) {
                glCamera*   oldMain = g.viewMain.c;
                glCamera*   newMain = g.view2.c;

                oldMain->setViewport(&g.view2);
                newMain->setViewport(&g.viewMain);
            } else if (g.view3.r.isInside(g.mouse)) {
                glCamera*   oldMain = g.viewMain.c;
                glCamera*   newMain = g.view3.c;

                oldMain->setViewport(&g.view3);
                newMain->setViewport(&g.viewMain);
            } else if (g.view4.r.isInside(g.mouse)) {
                glCamera*   oldMain = g.viewMain.c;
                glCamera*   newMain = g.view4.c;

                oldMain->setViewport(&g.view4);
                newMain->setViewport(&g.viewMain);
            }
        } else if (button == 3) {
            // we want to zoom in
            if (g.app->camera1.viewport->r.isInside(g.mouse)) {
                g.app->camera1.defaultPosition.z -= g.app->camera1.defaultPosition.z * 0.1;
            } else if (g.app->camera2.viewport->r.isInside(g.mouse)) {
                g.app->camera2.defaultPosition.y -= g.app->camera2.defaultPosition.y * 0.1;
            } else if (g.app->camera4.viewport->r.isInside(g.mouse)) {
                g.app->camera4.defaultPosition.z -= g.app->camera4.defaultPosition.z * 0.1;
            }
        } else if (button == 4) {
            // we want to zoom in
            if (g.app->camera1.viewport->r.isInside(g.mouse)) {
                g.app->camera1.defaultPosition.z += g.app->camera1.defaultPosition.z * 0.1;
            } else if (g.app->camera2.viewport->r.isInside(g.mouse)) {
                g.app->camera2.defaultPosition.y += g.app->camera2.defaultPosition.y * 0.1;
            } else if (g.app->camera4.viewport->r.isInside(g.mouse)) {
                g.app->camera4.defaultPosition.z += g.app->camera4.defaultPosition.z * 0.1;
            }
        }
    }
    else if (state == GLUT_UP)
    {
        if (button == GLUT_LEFT_BUTTON) {
            g.clickPosition = Vector2(0,0);
            g.deltaRotation = Vector2(0,0);

            if (g.app->activeCamera != NULL) {
                g.app->activeCamera->tempYaw = 0;
                g.app->activeCamera->tempPitch = 0;

                g.app->activeCamera = NULL;
            }
        }
    }
}

void glCallback_keyboard(unsigned char key, int x, int y)
{
    if (key == 'a')
    {
        SceneObject::drawAxis = !SceneObject::drawAxis;
    } else if (key == '1') {
        g.app->camera1Anchor = g.app->objSun;
    } else if (key == '2') {
        g.app->camera1Anchor = g.app->objEarth;
    } else if (key == '3') {
        g.app->camera1Anchor = g.app->objMoon;
    } else if (key == '4') {
        g.app->camera1Anchor = g.app->objSpaceship;
    } else if (key == '5') {
        g.app->camera1Anchor = g.app->objMars;
    } else if (key == '6') {
        g.app->camera1Anchor = g.app->objPhobos;
    } else if (key == '7') {
        g.app->camera1Anchor = g.app->objDeimos;
    } else if (key == 'l') {

        if (g.app->objSpaceship->getParent() == g.app->objMars) return;

        if (g.app->objSpaceship->getDistanceFromOrigin() >= 0) {

            float dangle = g.app->objMars->orbitAngle - g.app->objEarth->orbitAngle;

            if      (dangle > 180)  dangle -= 360;
            else if (dangle < -180) dangle += 360;

            if (dangle < CLOSE_ROTATION and dangle > FAR_ROTATION)
            {
                Vector3 ap = g.app->objSpaceship->getAbsolutePosition();
                g.app->objSpaceship->detachFromParent();
                g.app->objSpaceship->position = ap;
                g.app->sceneRoot.at(0)->addChild(g.app->objSpaceship);
                g.app->objSpaceship->launched = true;
            }
        }
    }
}
#endif // OPENGLCALLBACKS_H_INCLUDED
