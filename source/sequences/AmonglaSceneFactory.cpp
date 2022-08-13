#include "sequences/AmonglaSceneFactory.hpp"
#include "al/scene/SceneFactory.h"

#include "sequences/TrueScene.hpp"

template <class T>
al::Scene* createSceneFunc() {
    return new T();
}

static al::NameToCreator<sceneCreator> scenes[] = {
    {"TrueScene", createSceneFunc<TrueScene>}
};

AmonglaSceneFactory::AmonglaSceneFactory(const char* name) : alSceneFunction::SceneFactory(name) {
    creatorTable = scenes;
    factoryCount = sizeof(scenes)/sizeof(scenes[0]);
}