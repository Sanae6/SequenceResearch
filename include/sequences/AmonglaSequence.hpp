#pragma once

#include "al/sequence/Sequence.h"
#include "al/sequence/SequenceInitInfo.h"

class AmonglaSequence : public al::Sequence {
public:
    AmonglaSequence(const char* name);
    void init(const al::SequenceInitInfo &initInfo) override;
    // void update() override;
    // void kill() override;
    void drawMain() override;
    constexpr static const char* name = "AmonglaSeqeunce";
private:
    // AMONG US
};
