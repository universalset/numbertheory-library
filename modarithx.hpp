/*
 * This file contains higher precision versions of the functions in modarith.hpp
 * These functions are of two types:
 * 1. versions which take long inputs and give long outputs, but which might
 *    experience overflow in between when using only standard c++ types
 * 2. arbitrary-precision versions.  These use the boost cpp_int type.
 */

#ifndef BR_MODARITH_X_HPP
#define BR_MODARITH_X_HPP

#include "boost/multiprecision/cpp_int.hpp"

namespace nt
{
    /**
     * Greatest Common Divisor
     * PARAMETERS: two integers (boost arbitrary precision)
     * RETURN: the greatest common divisor of the integers, as the same type
     * Notes: if both integers are zero, returns zero.  Result is otherwise
     * positive.
     */
    boost::multiprecision::cpp_int gcd(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);

    /**
     * Least Common Multiple
     * PARAMETERS: two integers (boost arbitrary precision)
     * RETURN: the least common multiple of the integers.
     */
    boost::multiprecision::cpp_int lcm(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int b);

    /**
     * Fast Modular Exponentiation
     * PARAMETERS: base, exponent, and modulus, all integers
     * RETURN: the base, raised to the exponent, modulo the modulus
     * Notes: In case of a zero modulus, -1 is returned.  Otherwise, the return
     * value is nonnegative.  Modulus is converted to its absolute value before
     * computation.
     * If the exponent is negative, and the base and modulus are relatively
     * prime, then the correct answer is returned (power of inverse).
     * If the exponent is negative and the base and modulus are not relatively
     * prime, -1 is returned.
     *
     * First version: inputs and output are longs
     * Second version: inputs and output are arbitrary-precision integers
     */
    long powmod(long base, long exponent, long modulus);
    boost::multiprecision::cpp_int powmod(boost::multiprecision::cpp_int base, boost::multiprecision::cpp_int exponent, boost::multiprecision::cpp_int modulus);

    /**
     * Modular Factorial
     * PARAMETERS: the number n to be factorialed (long), and the modulus
     * (boost arbitrary precision integer)
     * If you are trying to take a factorial of something that doesn't fit
     * in an int, please reconsider.
     * RETURN: n! modulo the modulus
     * Notes: If you need to compute with many factorials, use a table instead.
     * This function is for one-off uses.  Modulus is converted to its absolute
     * value before computation.  Since negative factorials are not defined,
     * the return value is -1 if n is negative.
     */
    boost::multiprecision::cpp_int factmod(long n, boost::multiprecision::cpp_int modulus);

    /**
     * Modular Inverse
     * PARAMETERS: the number a whose inverse is to be computed, and the modulus
     * both as boost arbitrary precision integers
     * RETURN: the inverse of a, modulo the modulus
     * Notes: the modulus is converted to its absolute value before computation.
     * In case the modulus is zero or there is no inverse, 0 is returned
     * If the modulus is 1, returns 1.
     */
    boost::multiprecision::cpp_int modularInverse(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int modulus);

    /**
     * System of Congruences Solver
     * PARAMETERS: four integers: a, firstModulus, b, secondModulus
     * all boost arbitrary precision integers
     * RETURN: the smallest nonnegative solution to the system
     * x = a (mod firstModulus), x = b (mod secondModulus)
     * if such a solution exists, and -1 if there is no such x
     * Notes: Moduli are converted to absolute values.
     * If either modulus is 0, -1 is returned
     */
    boost::multiprecision::cpp_int solveModularSystem(boost::multiprecision::cpp_int a, boost::multiprecision::cpp_int firstModulus, boost::multiprecision::cpp_int b, boost::multiprecision::cpp_int secondModulus);

}












#endif
