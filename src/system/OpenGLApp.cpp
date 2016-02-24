#include "OpenGLApp.h"
#include "OpenGLCallbacks.h"

OpenGLApp::OpenGLApp()
{
    //ctor
}

OpenGLApp::~OpenGLApp()
{
    //dtor
}

void OpenGLApp::initGlobals()
{
    g.app = this;

    g.screenWidth   = DEFAULT_SCREEN_WIDTH;
    g.screenHeight  = DEFAULT_SCREEN_HEIGHT;

    // camera 1 (free)
    camera1.up = Vector3(0,1,0);
    camera1.defaultPosition = Vector3(0,0,150);
    // camera 2 (top down)
    camera2.up = Vector3(0,0,1);
    camera2.defaultPosition = Vector3(0,250,0);
    // camera 3 (cockpit view)
    camera3.up = Vector3(0,1,0);
    camera3.defaultPosition = Vector3(0,0,0);
    // cmaera 4 (spaceship free)
    camera4.up = Vector3(0,1,0);
    camera4.defaultPosition = Vector3(0,0,5);
    camera4.setYaw(-90);
    camera4.setPitch(-10);

    // set the camera's default view ports
    camera1.viewport = &g.viewMain;
    camera2.viewport = &g.view2;
    camera3.viewport = &g.view3;
    camera4.viewport = &g.view4;

    // add camera references to the view ports (allows easy retrieval of the camera assosiated with the viewport)
    g.viewMain.c = &camera1;
    g.view2.c = &camera2;
    g.view3.c = &camera3;
    g.view4.c = &camera4;

    activeCamera = NULL;                    // the current camera that is being rotated/modified with the mouse (excluding zoom)

    camera2.enablePitchRotation = false;    // don't allow pitch rotation becuase this is a top down view camera
    camera2.enableUpRotation    = true;     // enable rotation of the up vector becuase we want to change the yaw

    camera3.enablePitchRotation = false;
    camera3.enableYawRotation   = false;
}

void OpenGLApp::initOpenGL(int argc, char** argv)
{
	glutInit(&argc, argv);

	//setup double buffering
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	//set up the window
	glutInitWindowSize(g.screenWidth, g.screenHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow ("Voyage to Mars");

	//assign the callback functions
	glutDisplayFunc(glCallback_display);
	glutKeyboardFunc(glCallback_keyboard);
	glutMotionFunc(glCallback_motion);
	glutPassiveMotionFunc(glCallback_passiveMotion);
	glutMouseFunc(glCallback_mouse);
	glutReshapeFunc(glCallback_reshape);

	glEnable(GL_NORMALIZE);
	glClearColor(0.0, 0.0, 0.0, 1.0);
}

void OpenGLApp::run()
{
    animateSceneTimer((float)ONE_SECOND / (float)FPS);
    glutMainLoop();
}

void OpenGLApp::setupCamera1()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fov = (camera1.viewport->r.h / camera1.viewport->r.w) * DEFAULT_FOV;   // create a dynamic FOV so objects don't stretch on the edges of the screen
	fov = std::min(fov,MAX_H_FOV);
	gluPerspective(fov, g.viewMain.r.w/g.viewMain.r.h, NEAR_LIMIT, FAR_LIMIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    camera1.call_gluLookAt();

	//setup the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable( GL_DEPTH_TEST );

	//have a light source at the origin!
	float lp [] = {0.0,0.0,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_LIGHTING);// Enable lighting calculations
	glEnable(GL_LIGHT0);// Turn on light #0.

	camera1.activateViewport();
}

void OpenGLApp::setupCamera2()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fov = (camera2.viewport->r.h / camera2.viewport->r.w) * DEFAULT_FOV;   // create a dynamic FOV so objects don't stretch on the edges of the screen
	fov = std::min(fov,MAX_H_FOV);
	gluPerspective(fov, g.view2.r.w/g.view2.r.h, NEAR_LIMIT, FAR_LIMIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    camera2.call_gluLookAt();

	//setup the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable( GL_DEPTH_TEST );

	//have a light source at the origin!
	float lp [] = {0.0,0.0,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_LIGHTING);// Enable lighting calculations
	glEnable(GL_LIGHT0);// Turn on light #0.

	camera2.activateViewport();
}

void OpenGLApp::setupCamera3()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fov = (camera3.viewport->r.h / camera3.viewport->r.w) * DEFAULT_FOV;   // create a dynamic FOV so objects don't stretch on the edges of the screen
	fov = std::min(fov,MAX_H_FOV);
	gluPerspective(fov, g.view3.r.w/g.view3.r.h, NEAR_LIMIT, FAR_LIMIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    camera3.call_gluLookAt();

	//setup the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable( GL_DEPTH_TEST );

	//have a light source at the origin!
	float lp [] = {0.0,0.0,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_LIGHTING);// Enable lighting calculations
	glEnable(GL_LIGHT0);// Turn on light #0.

	camera3.activateViewport();
}

void OpenGLApp::setupCamera4()
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float fov = (camera4.viewport->r.h / camera4.viewport->r.w) * DEFAULT_FOV;   // create a dynamic FOV so objects don't stretch on the edges of the screen
	fov = std::min(fov,MAX_H_FOV);
	gluPerspective(fov, g.view4.r.w/g.view4.r.h, NEAR_LIMIT, FAR_LIMIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    camera4.call_gluLookAt();

	//setup the depth buffer
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glEnable( GL_DEPTH_TEST );

	//have a light source at the origin!
	float lp [] = {0.0,0.0,0.0,1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, lp);

	glEnable(GL_LIGHTING);// Enable lighting calculations
	glEnable(GL_LIGHT0);// Turn on light #0.

	camera4.activateViewport();
}


void OpenGLApp::setupGUI()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,g.screenWidth,0,g.screenHeight);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glDisable( GL_DEPTH_TEST );

   glViewport(0, 0, g.screenWidth, g.screenHeight);
}

void OpenGLApp::drawGUI()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1,1,1);
    // draw viewport seperator lines
    glBegin(GL_LINES);
        glVertex2f(0,g.screenHeight * 0.25f);
        glVertex2f(g.screenWidth,g.screenHeight * 0.25f);

        glVertex2f(g.screenWidth / 3, 0);
        glVertex2f(g.screenWidth / 3, g.screenHeight * 0.25);

        glVertex2f(g.screenWidth / 3 * 2, 0);
        glVertex2f(g.screenWidth / 3 * 2, g.screenHeight * 0.25);
    glEnd();

    // draw ready to launch indicator
    float dangle = objMars->orbitAngle - objEarth->orbitAngle;

    if      (dangle > 180)  dangle -= 360;
    else if (dangle < -180) dangle += 360;

    if (dangle < CLOSE_ROTATION and dangle > FAR_ROTATION)
    {
        glColor3f(1,0,0);
        glPushMatrix();
        glTranslatef(30,g.screenHeight - 30,0);
        glBegin(GL_POLYGON);
            // draw a circle in the top left corner when you can launch the ship
            Vector2 p = Vector2(20,0);
            for (int i = 0; i < 360; ++i)
            {
                glVertex2f(p.x,p.y);
                p.rotate(1);
            }
        glEnd();
        glPopMatrix();
    }
}


int OpenGLApp::loadTexture(const char* filename)
{
    string name = "textures/";
	name += filename;
	/* load an image file from texture directory as a new OpenGL texture */
	g.texture[0] = SOIL_load_OGL_texture
			(
					name.c_str(),
					SOIL_LOAD_AUTO,
					SOIL_CREATE_NEW_ID,
					SOIL_FLAG_INVERT_Y
			);

	if(g.texture[0] == 0) {
		std::cerr << filename << " : " << SOIL_last_result();
		return false;
	}

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, g.texture[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	return true;// Return Success
}

void OpenGLApp::loadScene()
{
    loadTexture("sun.png");
    loadTexture("earth.jpg");
    loadTexture("uv_moon.png");
    loadTexture("uv_mars.jpg");
    loadTexture("milkyway.jpg");
    loadTexture("ship.png");
    loadTexture("phobos.jpg");
    loadTexture("deimos.jpg");


    SkyBox* skybox = new SkyBox();
    skybox->textureID       = 5;
    skybox->rotation.x      = 90;
    skybox->lighting        = false;
    skybox->drawAxis        = false;
    skybox->cullFace        = GL_FRONT;
    skybox->scale           = Vector3(SKYBOX_SCALE,SKYBOX_SCALE,SKYBOX_SCALE);

    // the sun
    QuadSphere* sun = new QuadSphere();
    sun->textureID          = 1;
    sun->rotationSpeed.y    = SUN_ROTATION_SPEED;
    sun->scale              = Vector3(SUN_SCALE,SUN_SCALE,SUN_SCALE);
    sun->lighting           = false;
    objSun  = sun;
    camera1Anchor = sun;

    QuadSphere* earth = new QuadSphere();
    earth->textureID        = 2;
    earth->offset.z         = EARTH_ORBIT_RADIUS;
    earth->rotation         = Vector3(-90,0,0);
    earth->orbitSpeed.y     = EARTH_ORBIT_SPEED;
    earth->rotationSpeed.y  = EARTH_ROTATION_SPEED;
    earth->scale            = Vector3(EARTH_SCALE,EARTH_SCALE,EARTH_SCALE);
    objEarth = earth;

    QuadSphere* moon = new QuadSphere();
    moon->textureID         = 3;
    moon->offset.z          = MOON_ORBIT_RADIUS;
    moon->orbitSpeed.y      = MOON_ORBIT_SPEED;
    moon->rotationSpeed.y   = MOON_ROTATION_SPEED;
    moon->scale             = Vector3(MOON_SCALE,MOON_SCALE,MOON_SCALE);
    objMoon = moon;

    QuadSphere* mars = new QuadSphere();
    mars->textureID         = 4;
    mars->offset.z          = MARS_ORBIT_RADIUS;
    mars->orbitSpeed.y      = MARS_ORBIT_SPEED;
    mars->rotationSpeed.y   = MARS_ROTATION_SPEED;
    mars->scale             = Vector3(MARS_SCALE,MARS_SCALE,MARS_SCALE);
    objMars = mars;

    QuadSphere* phobos = new QuadSphere();
    phobos->textureID       = 7;
    phobos->offset.z        = PHOBOS_ORBIT_RADIUS;
    phobos->orbitSpeed.y    = PHOBOS_ORBIT_SPEED;
    phobos->rotationSpeed.y = PHOBOS_ROTATION_SPEED;
    phobos->scale           = Vector3(PHOBOS_SCALE,PHOBOS_SCALE,PHOBOS_SCALE);
    objPhobos = phobos;

    QuadSphere* deimos = new QuadSphere();
    deimos->textureID       = 8;
    deimos->offset.z        = DEIMOS_ORBIT_RADIUS;
    deimos->orbitSpeed.y    = DEIMOS_ORBIT_SPEED;
    deimos->rotationSpeed.y = DEIMOS_ROTATION_SPEED;
    deimos->scale           = Vector3(DEIMOS_SCALE,DEIMOS_SCALE,DEIMOS_SCALE);
    objDeimos = deimos;

    SpaceShip* ship = new SpaceShip();
    ship->loadModel("models/ship.obj");
    ship->textureID         = 6;
    ship->mars              = mars;
    ship->speed             = SHIP_SPEED;
    ship->offset.z          = SHIP_ORBIT_RADIUS;
    ship->orbitSpeed.y      = EARTH_ORBIT_SPEED + SHIP_ORBIT_SPEED;
    ship->rotationSpeed.y   = ship->orbitSpeed.y;
    ship->scale             = Vector3(SHIP_SCALE,SHIP_SCALE,SHIP_SCALE);
    objSpaceship = ship;

    float brightness = 0.5;
    OrbitRing* earthOrbit = new OrbitRing();
    earthOrbit->radius      = EARTH_ORBIT_RADIUS;
    earthOrbit->lighting    = false;
    earthOrbit->colour      = Colour4(brightness,brightness,brightness,1.0);

    OrbitRing* marsOrbit = new OrbitRing();
    marsOrbit->radius       = MARS_ORBIT_RADIUS;
    marsOrbit->lighting     = false;
    marsOrbit->colour       = Colour4(brightness,brightness,brightness,1.0);

    OrbitRing* moonOrbit = new OrbitRing();
    moonOrbit->radius       = MOON_ORBIT_RADIUS;
    moonOrbit->lighting     = false;
    moonOrbit->colour       = Colour4(brightness,brightness,brightness,1.0);

    OrbitRing* phobosOrbit = new OrbitRing();
    phobosOrbit->radius       = PHOBOS_ORBIT_RADIUS;
    phobosOrbit->lighting     = false;
    phobosOrbit->colour       = Colour4(brightness,brightness,brightness,1.0);

    OrbitRing* deimosOrbit = new OrbitRing();
    deimosOrbit->radius       = DEIMOS_ORBIT_RADIUS;
    deimosOrbit->lighting     = false;
    deimosOrbit->colour       = Colour4(brightness,brightness,brightness,1.0);

    earth->addChild(moon);
    earth->addChild(ship);
    earth->addChild(moonOrbit);
    mars->addChild(phobos);
    mars->addChild(deimos);
    mars->addChild(phobosOrbit);
    mars->addChild(deimosOrbit);
    sun->addChild(earth);
    sun->addChild(mars);
    sun->addChild(earthOrbit);
    sun->addChild(marsOrbit);
    skybox->addChild(sun);

    sceneRoot.push_back(skybox);
}

void OpenGLApp::drawScene()
{
    glColor3f(1,1,1);
    for(unsigned int i = 0; i < sceneRoot.size(); ++i)
	{
		sceneRoot.at(i)->display();
	}
}

void OpenGLApp::animateScene()
{
    for(unsigned int i = 0; i < sceneRoot.size(); ++i)
	{
		sceneRoot.at(i)->update();
	}

    camera1.positionOffset = camera1Anchor->getAbsolutePosition();

    // update cockpit camera offset
	camera3.positionOffset = objSpaceship->getAbsolutePosition();
	camera3.positionOffset.y += 0.2;
	// calculate and set cockpit camera lookat position
	Vector3 lookat = Vector3(10,0,0);
	lookat.rotateY(objSpaceship->rotation.y);
	camera3.lookat = lookat;

    // update camera 4 offset
	camera4.positionOffset = objSpaceship->getAbsolutePosition();
	camera4.rotationOffset = objSpaceship->rotation.y;
}
