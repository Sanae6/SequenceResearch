#pragma once

namespace al {
class AudioDirector;
class Sequence;
class AudioSystemInfo;
class AudioDirectorInitInfo;
class Scene;
class SceneInitInfo;

void initAudioDirector(al::Sequence*, al::AudioSystemInfo*, al::AudioDirectorInitInfo&);
void initAudioDirector2D(al::Scene*, const al::SceneInitInfo&, al::AudioDirectorInitInfo&);
void initAudioDirector3D(al::Scene*, const al::SceneInitInfo&, al::AudioDirectorInitInfo&);
};  // namespace al