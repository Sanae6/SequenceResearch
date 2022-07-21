#pragma once

#include "al/audio/SeDirectorInitInfo.h"
#include "types.h"

namespace al {
class AudioSystemInfo;
class AudioDirectorInitInfo {
public:
    AudioSystemInfo* mAudioSystemInfo;
    s64 unknown_0x8;
    char* mCurrentStage;
    s64 unknown_0x18;
    s64 unknown_0x20;
    SeDirectorInitInfo mSeDirectorInitInfo;
    s32 unknown_0x2c;
    s32 unknown_0x30;
    const char* mName;
    s64 unknown_0x40;
    bool unknwon_0x48;
    bool unknwon_0x49;
    s64 unknown_0x50;
    s32 unknown_0x58;
    s64 unknown_0x60;
    s64 unknown_0x68;
    s64 unknown_0x70;
    s64 unknown_0x78;
    s64 unknown_0x80;
    s64 mBgmDirectorInitInfo;
};
}  // namespace al