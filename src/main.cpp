#include "general.h"
#include "system/OpenGLApp.h"

int main(int argc, char *argv[])
{
    OpenGLApp app;
    app.initGlobals();
    app.initOpenGL(argc,argv);
    app.loadScene();
    app.run();

    return EXIT_SUCCESS;
}
