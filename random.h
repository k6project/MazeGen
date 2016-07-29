/*! \file random.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of Random class (PRN generator).
*/

#ifndef RANDOM_H
#define RANDOM_H

#include <boost/random.hpp>
#include <boost/uuid/seed_rng.hpp>

/*! \brief Pseudo-random number generator class

    Utility class that incapsulates Boost::Random PRNG, providing adapter to
    generate integers in a specified [min,max] range.
*/
class Random
{
public:

    /*! \brief Method, that initializes underlying RNG

        This methid initializes random number generator with a seed based on
        current PID and system time. This method should be called first-hand
        after Random object is created.
    */
    void init();

    /*! Operator, that generates a pseudo-random number in range [min,max]

        \param min Lower boundary
        \param max Upper boundary
        \return Pseudo-random number in range [min,max]
    */
    int operator()(int min, int max);

private:
    boost::mt11213b _rawRNG;
    typedef boost::variate_generator
    <
         boost::mt11213b &,
         boost::uniform_int<>
    > variate_gen_t;
};

#endif // RANDOM_H
