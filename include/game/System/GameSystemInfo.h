#pragma once

#include "GameFrameWorkNx.h"
#include "GameDrawInfo.h"

namespace aal
{
    struct IAudioFrameProcess;
} // namespace aal

namespace al
{
    struct NetworkSystem;
    struct HtmlViewer;
    struct EffectSystem;
    struct LayoutSystem;
    struct MessageSystem;
    struct GamePadSystem;
    struct AudioSystem;
    struct WaveVibrationHolder; // :: aal::IAudioFrameProcess;
    class FontHolder;
} // namespace al

struct ProjectNfpDirector;
struct ApplicationMessageReceiver;
struct Application;

namespace al {
    class GameSystemInfo {
        public:
            AudioSystem* mAudioSys;
            al::EffectSystem *mEffectSys;                  // 0x08 
            al::LayoutSystem *mLayoutSys;                  // 0x10 
            al::MessageSystem *mMessageSys;                // 0x18 
            al::NetworkSystem *mNetworkSys;                // 0x20 
            void *balls;                    // 0x28 
            al::GamePadSystem *mGamePadSys;                // 0x30 
            al::GameDrawInfo *mDrawInfo;                   // 0x38 from Application::sInstance + 0x30
            al::FontHolder* mFontHolder;
            ProjectNfpDirector *mProjNfpDirector;          // 0x48 
            al::HtmlViewer *mHtmlViewer;                   // 0x50 
            ApplicationMessageReceiver *mMessageReciever;  // 0x58 
            al::WaveVibrationHolder *mWaveVibrationHolder; // 0x60 
            void *gap2;
    };
}