#pragma once

#include "al/sequence/Sequence.h"
#include "al/sequence/SequenceInitInfo.h"

class AmonglaSequence : public al::Sequence {
public:
    AmonglaSequence(const char* name);
    void init(const al::SequenceInitInfo &initInfo) override;
    void drawMain() const override;
    static const char* name() {
        return "AmonglaSequence";
    }
private:
    // AMONG US
};
