#pragma once

#include "al/scene/Scene.h"

class TrueScene : public al::Scene {
public:
    TrueScene(const char* name);
    void init(const al::SceneInitInfo & initInfo) override;
    
};