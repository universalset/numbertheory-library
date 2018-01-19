/**
 * This file contains functions which produce information about prime numbers
 * or use that information to compute other number-theoretical functions.
 * Many of the functions are sieve methods that dump a large amount of
 * information into data structures that they are passed.
 */

#ifndef BR_PRIMES_HPP
#define BR_PRIMES_HPP

#include<vector>
#include<map>

namespace nt
{
    /**
     * Sieve of Eratosthenes
     *
     * PARAMETERS: Max range for the sieve, a reference to a 
     * vector<bool> to hold the sieve.
     * RETURN: Nothing, but the vector will hold the completed sieve in its 
     * first (max) entries.  The vector will hold the value "true" in position p
     * if and only if p is prime. Entries in the vector past (max) will not be 
     * changed.
     * Note: This method changes the parameter vector!
     */
    void primeSieve(int max, std::vector<bool> & sieve);

    /**
     * Sieve of Eratosthenes with list of primes
     * As above, but also returns a vector containing all the prime numbers 
     * found.
     *
     * PARAMETERS: Max range for the sieve, a reference to a 
     * vector<bool> to hold the sieve.
     * RETURN: a vector<int> containing all primes numbers less than (max) in 
     * order. In addition, the parameter vector will hold the completed sieve 
     * in its first (max) entries.  The vector will hold the value "true" in
     * position p if and only if p is prime.  Entries in the vector past (max) 
     * will not be changed.
     * Note: This method changes the parameter vector!
 */
    std::vector<int> primes(int max, std::vector<bool> & sieve);
    
    /**
     * Sieve of Eratosthenes with list of primes, no input vector
     * Exactly as above, but no vector parameter.  The sieve is produced and
     * then discarded.
     */
    std::vector<int> primes(int max);

    /**
     * Vector From Sieve
     * Given a vector of bools, produce a vector with values for which
     * the corresponding bool is true.
     *
     * PARAMETER: a vector (sieve) of bools
     * RETURN: a vector containing (in order) all k such that sieve[k]=true
     * Note: particularly useful with many of the sieve methods below that
     * don't return a vector of primes.
     */
    std::vector<int> vectorFromSieve(std::vector<bool> & sieve);


    /**
     * Smallest Prime Factor Sieve
     * Sieve of Eratosthenes that also produces the smallest prime factor of
     * each number less than max.
     *
     * PARAMETERS: the max range for the sieve, a vector (sieve)
     * to hold the bools indicating prime numbers, and a vector 
     * (smallPrimeFactors) of ints to hold the smallest prime factors.
     * RETURN: Nothing, but the vectors will hold the completed sieve
     * information in their first (max) entries.  sieve will hold whether each
     * index is a prime number; smallPrimeFactors will hold the smallest prime
     * factor of the index.
     * Notes: This function changes the vector parameters!  By convention, the
     * "smallest prime factor" of 0 will be 0, and of 1 will be 1.
     */
    
    void smallestPrimeFactors(int max, std::vector<bool> & sieve, std::vector<int> & smallPrimeFactors);


    /**
     * Smallest Prime Power Sieve
     * Sieve of Eratosthenes that also produces the smallest prime factor of
     * each number less than max, as well as the maximum power of that prime 
     * dividing the number and the corresponding exponent.
     *
     * This function is particularly useful for enabling the computation of
     * prime factorizations and various multiplicative functions.
     *
     * PARAMETERS: the max range for the sieve, a vector (sieve)
     * to hold the bools indicating prime numbers, a vector 
     * (smallPrimeFactors) of ints to hold the smallest prime factors, a vector
     * (smallPrimePowers) of ints to hold the corresponding power of that prime,
     * and a vector (exponents) of ints to hold the corresponding exponents.
     * RETURN: Nothing, but the vectors will hold the completed sieve
     * information in their first (max) entries.  sieve will hold whether each
     * index is a prime number; smallPrimeFactors will hold the smallest prime
     * factor of the index; smallPrimePowers will hold the corresponding power
     * of that smallest prime factor in the prime factorization of the index;
     * and exponents will hold the exponents in those powers.
     * Notes: This function changes the vector parameters!  By convention, the
     * "smallest prime factor" of 0 will be 0, and of 1 will be 1, with
     * corresponding exponents 0.
     */
    void smallestPrimePowers(int max, std::vector<bool> & sieve, std::vector<int> & smallPrimeFactors, std::vector<int> & smallPrimePowers, std::vector<int> & exponents);



    /**
     * Euler's Totient Function Sieve
     * Modification of Sieve of Eratosthenes that also produces the value of
     * Euler's totient function phi(n) for each integer.
     *
     * PARAMETERS: the max range (max) for the sieve, an integer, a vector
     * (sieve) to hold the bools indicating prime numbers, and a vector
     * (totients) of ints to hold the values of Euler's totient function.
     * RETURN: Nothing, but the vectors will hold the completed sieve
     * information in their first (max) entries.  sieve will hold whether each
     * index is a prime number; totients will hold the value of Euler's totient
     * function at each index.
     * Notes: This function changes the vector parameters!  By convention,
     * phi(0) = 0 and phi(1) = 1.
     * This function is somewhat slower than a traditional sieve of Eratosthenes
     * because it must visit numbers already known not to be prime.
     */

    void eulerTotientSieve(int max, std::vector<bool> & sieve, std::vector<int> & totients);


    /**
     * Prime Counting Function
     * 
     * PARAMETERS: (max), the number to count all primes up to, and (primes), a
     * vector of ints containing all primes up to sqrt(max) in order.
     * RETURN: the number of primes up to (and including) max.
     * Notes: The vector (primes) must contain all primes up to sqrt(max) or 
     * behavior is undefined (may crash, produce wrong answer, etc.)
     */

    long countPrimes(long max, std::vector<int> & primes);


    /**
     * Memoized Prime Counting Function
     * For using repeatedly to avoid recomputing values
     * PARAMETERS: (max), the number to count all primes up to, (primes), a
     * vector of ints containing all primes up to sqrt(max) in order, and
     * (memo), a map<long, long> containing some values of the function.
     * RETURN: the number of primes up to (and including) max.  memo is updated
     * to inlude any correct values of the function used in computation.
     * Notes: The map (memo) is modified by this function! 
     * The vector (primes) must contain all primes up to sqrt(max) or 
     * behavior is undefined (may crash, produce wrong answer, etc.)
     */

    long countPrimesMemoized(long max, std::vector<int> & primes, std::map<long, long> & memo);

}

#endif
