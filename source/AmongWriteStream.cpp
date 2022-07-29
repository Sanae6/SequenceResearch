#include "AmongWriteStream.hpp"
#include "logger.hpp"

u32 AmongWriteStreamFormat::write(const void* data, u32 size) {
    Logger::log_buffer(data, size);
    return size;
}

AmongWriteStream::AmongWriteStream() : sead::WriteStream() {
    mSrc = &format;
    setMode(Modes::Text);
}