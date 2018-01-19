/*
 * This file contains functions dealing with modular arithmetic and
 * divisibility that don't produce or require information about primes
 * and prime factorization.
 */


#ifndef BR_MODARITH_HPP
#define BR_MODARITH_HPP

namespace nt
{
    /**
     * Greatest Common Divisor
     * PARAMETERS: two integers (int or long)
     * RETURN: the greatest common divisor of the integers, as the same type
     * Notes: if both integers are zero, returns zero.  Result is otherwise
     * positive.
     */
    int gcd(int a, int b);   
    long gcd(long a, long b);

    /**
     * Least Common Multiple
     * PARAMETERS: two integers (ints)
     * RETURN: the least common multiple of the integers (as long)
     * Notes: Since the least common multiple may not fit in an int, the return
     * type is a long.  The result is always nonnegative.
     */
    long lcm(int a, int b);

    /**
     * Fast Modular Exponentiation
     * PARAMETERS: base of the power and exponent as long, modulus as int
     * long modulus not supported due to potential for overflow
     * RETURN: the base, raised to the exponent, modulo the modulus, as int
     * Notes: In case of a zero modulus, -1 is returned.  Otherwise, the return
     * value is nonnegative.  Modulus is converted to its absolute value before
     * computation.
     * If the exponent is negative, and the base and modulus are relatively
     * prime, then the correct answer is returned (power of inverse).
     * If the exponent is negative and the base and modulus are not relatively
     * prime, -1 is returned.
     * Runtime is O(log(exponent))
     */
    int powmod(long base, long exponent, int modulus);



    /**
     * Modular Factorial
     * PARAMETERS: the number n to be factorialed, and the modulus, as int
     * RETURN: n! modulo the modulus, as int
     * Notes: If you need to compute with many factorials, use a table instead.
     * This function is for one-off uses.  Modulus is converted to its absolute
     * value before computation.  Since negative factorials are not defined,
     * the return value is -1 if n is negative.  Similarly if modulus is 0.
     * Runtime is O(min(n, modulus))
     */
    int factmod(int n, int modulus);


    /**
     * Modular Inverse
     * PARAMETERS: the number a whose inverse is to be computed, and the modulus
     * both as integers (int or long)
     * RETURN: the inverse of a, modulo the modulus
     * Notes: the modulus is converted to its absolute value before computation.
     * In case the modulus is zero or there is no inverse, 0 is returned
     * If the modulus is 1, returns 1.
     */
    int modularInverse(int a, int modulus);
    long modularInverse(long a, long modulus);

    /**
     * System of Congruences Solver
     * PARAMETERS: four ints: a, firstModulus, b, secondModulus
     * RETURN: the smallest nonnegative solution to the system
     * x = a (mod firstModulus), x = b (mod secondModulus)
     * if such a solution exists, and -1 if there is no such x
     * Notes: Moduli are converted to absolute values.
     * If either modulus is 0, -1 is returned
     * Since the solution may be as large as the product of the moduli,
     * inputs are restricted to ints and return type is long to avoid overflow
     */
    long solveModularSystem(int a, int firstModulus, int b, int secondModulus);




}


#endif
