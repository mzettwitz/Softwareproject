#include "../include/program3.h"
#include "../include/display.h"
#include "../include/scene.h"


int program3(int argc, char* argv[])
{
    Display::init(argc,argv);
    std::string title = "program3";

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();

    Display::run(title,scene);
    return 0;
}
