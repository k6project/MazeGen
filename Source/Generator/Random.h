#pragma once

#include <cstdint>

namespace Random
{
    uint32_t UInt32();
    uint16_t UInt16();
    uint32_t UInt32(uint32_t min, uint32_t max);
    uint16_t UInt16(uint16_t min, uint16_t max);
}
