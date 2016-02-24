#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

// OpenGL
static const GLint MAX_NO_TEXTURES          = 10;

// math
static const double PI                      = 3.141592653589793; // why not
static const double TO_RAD                  = PI / 180;
static const double TO_DEG                  = 180 / PI;
static const int ONE_SECOND                 = 1000;

static const int NO_TEXTURE                 = -1;

// camera
static const float FAR_LIMIT                = 1000000.0f;
static const float NEAR_LIMIT               = 0.01f;
static const float DEFAULT_FOV              = 80;
static const float MAX_H_FOV                = 130;
static const float CAMERA_SENSITIVITY       = 1.0;

// screen
static const int FPS                        = 60;
static const float FRAME_TIME               = (float)FPS / (float)ONE_SECOND;
static const int DEFAULT_SCREEN_WIDTH       = 1280;
static const int DEFAULT_SCREEN_HEIGHT      = 720;

// SCENEOBJECT
//scales
static const float SKYBOX_SCALE             = 10000;
static const float SUN_SCALE                = 20;
static const float EARTH_SCALE              = 4;
static const float MOON_SCALE               = 1.5;
static const float MARS_SCALE               = 3;
static const float SHIP_SCALE               = 0.05;
static const float PHOBOS_SCALE             = 0.5;
static const float DEIMOS_SCALE             = 0.5;
// rotation speeds (rotation per second)
static const float SUN_ROTATION_SPEED       = 0.1;
static const float EARTH_ROTATION_SPEED     = 0.5;
static const float MOON_ROTATION_SPEED      = 0.25;
static const float MARS_ROTATION_SPEED      = 0.1;
static const float SHIP_ROTATION_SPEED      = 2.0;
static const float PHOBOS_ROTATION_SPEED    = 1.0;
static const float DEIMOS_ROTATION_SPEED    = 0.5;
// orbit speed (revolutions per second)
static const float EARTH_ORBIT_SPEED        = 0.1f;
static const float MOON_ORBIT_SPEED         = 0.25f;
static const float MARS_ORBIT_SPEED         = 0.02f;
static const float SHIP_ORBIT_SPEED         = 0.5;
static const float PHOBOS_ORBIT_SPEED       = 0.8;
static const float DEIMOS_ORBIT_SPEED       = 0.3;
// orbit radius'
static const float EARTH_ORBIT_RADIUS       = 50.f;
static const float MOON_ORBIT_RADIUS        = 10.f;
static const float MARS_ORBIT_RADIUS        = 100.f;
static const float SHIP_ORBIT_RADIUS        = 5.f;
static const float PHOBOS_ORBIT_RADIUS      = 3;
static const float DEIMOS_ORBIT_RADIUS      = 7;
static const float SHIP_SPEED               = 15.f;

static const float CLOSE_ROTATION           = -30;
static const float FAR_ROTATION             = -80;



#endif // CONSTS_H_INCLUDED
