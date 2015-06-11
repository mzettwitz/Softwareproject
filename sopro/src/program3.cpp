#include "../include/program3.h"
#include "../include/display.h"
#include "../include/simpleScene.h"


int program3(int argc, char* argv[])
{
    Display::init(argc,argv);
    std::string title = "program3";

    SimpleScene scene;

    Display::run(title,&scene);

    return 0;
}
