#pragma once
// only used to store random declarations! so cool!

#include "heap/seadDisposer.h"
namespace sead {
class Heap;
}

namespace agl {
class RenderBuffer;
}

namespace al {
class Scene;
class SceneInitInfo;
class LayoutKit;
class Sequence;
class LayoutSystem;
class IUseSceneCreator;
class GraphicsInitArg {
private:
    char details[0x48];
};

class ShaderHolder {
    SEAD_SINGLETON_DISPOSER(ShaderHolder);
public:
    void initAndLoadAllFromDir(const char*, sead::Heap*, sead::Heap*);
};

void initSceneAudioKeeper(al::Scene*, const al::SceneInitInfo&, const char*);
void setRenderBuffer(LayoutKit*, const agl::RenderBuffer*);
void executeUpdate(LayoutKit*);
void setSceneAndUseInitThread(al::IUseSceneCreator*, al::Scene*, int, const char*, int, const char*,
                              sead::Heap*);
bool tryEndSceneInitThread(al::IUseSceneCreator*);
// is this actually useCategory? lol idk but whatever, always set it to false.
void createSceneHeap(const char* name, bool useCategory);
// don't use sceneheapsetter, just use getSceneHeap and the sead equivalent
}  // namespace al

struct SequenceFactory {
    static al::Sequence* createSequence(const char* name);
};

// if (al::isPadHoldA(-1)) {
//     auto* renderer = sead::PrimitiveRenderer::instance();
//     renderer->setDrawContext(getDrawInfo()->mDrawContext);
//     sead::LookAtCamera camera(sead::Vector3f::zero, sead::Vector3f::ez, sead::Vector3f::ey);
//     sead::OrthoProjection proj;
//     renderer->setProjection(proj);
//     renderer->setCamera(camera);
//     renderer->begin();
//     renderer->setModelMatrix(sead::Matrix34f::ident);
//     renderer->end();
// }