#include "Random.h"

#include <random>

uint32_t Random::UInt32()
{
    static std::mt19937 prng;
    static bool initialized = false;
    
    if (!initialized)
    {
        //TODO: seed generator with current time
        prng.seed(0);
        initialized = true;
    }

    return prng();
}

uint16_t Random::UInt16()
{
    uint32_t retVal = UInt32();
    return (retVal & UINT16_MAX);
}

uint32_t Random::UInt32(uint32_t min, uint32_t max)
{
    uint64_t modulo = (static_cast<uint64_t>(max) + 1) - min;
    uint64_t retVal = min + UInt32() % modulo;
    return (retVal & UINT32_MAX);
}

uint16_t Random::UInt16(uint16_t min, uint16_t max)
{
    uint32_t retVal = UInt32(min, max);
    return (retVal & UINT16_MAX);
}
