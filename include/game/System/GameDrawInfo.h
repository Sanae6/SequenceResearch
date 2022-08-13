#pragma once

#include "agl/DrawContext.h"
#include "agl/RenderBuffer.h"

namespace al {
class GameDrawInfo {
public:
    agl::RenderBuffer* mDockedRenderBuffer;
    agl::RenderBuffer* mHandheldRenderBuffer;
    bool mIsDocked;
    agl::DrawContext* mDrawContext;
};
}  // namespace al
