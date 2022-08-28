#pragma once

#include "al/layout/LayoutActor.h"

namespace al {
class WipeSimple : al::LayoutActor {
public:
    WipeSimple(const char*, const char*, const al::LayoutInitInfo&, const char*);
    void appear() override;

    void startClose();
    void tryStartClose();
    void startCloseEnd();
    void StartOpen();
    void tryStartOpen();
    void isCloseEnd() const;
    void isOpenEnd() const;

    void exeClose();
    void exeCloseEnd();
    void exeOpen();
};
}  // namespace al