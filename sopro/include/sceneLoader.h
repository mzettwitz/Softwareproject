#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "scene.h"
#include <memory>
#include <string>

class SceneLoader
{
private:

public:

    static bool loadScene(const std::string &filename, std::shared_ptr<Scene> scene,std::vector<float> &settings);
    static bool saveScene(const std::string &filename, std::shared_ptr<Scene> scene,std::vector<float> &settings);
};


#endif
