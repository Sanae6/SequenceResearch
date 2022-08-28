#pragma once

#include "al/audio/BgmDirectorInitInfo.h"
#include "al/audio/SeDirectorInitInfo.h"
#include "types.h"

namespace al {
class AudioSystemInfo;
class Sequence;
class AudioDirectorInitInfo {
public:
    AudioSystemInfo* mAudioSystemInfo;
    Sequence* mSequence;
    char* mCurrentStage;
    s32 mScenarioNo;
    s64 unknown_0x20;
    SeDirectorInitInfo mSeDirectorInitInfo;
    BgmDirectorInitInfo mBgmDirectorInitInfo;
    char* mDuckingName;
};
}  // namespace al