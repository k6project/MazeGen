/*! \file random.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Implementation of Random class.
*/

#include "random.h"

void Random::init()
{
    _rawRNG.seed(boost::uuids::detail::seed_rng()());
}

int Random::operator()(int min, int max)
{
    boost::uniform_int<> dist(min, max);
    variate_gen_t theRNG(_rawRNG, dist);
    return theRNG();
}
