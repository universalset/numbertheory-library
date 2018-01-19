// implementation of sieves and functions interacting with primes in primes.hpp

#include<algorithm>
#include<vector>
#include<cmath>
#include<map>
#include "numthy/primes.hpp"

using std::vector;
using std::sqrt;
using std::pow;
using std::map;
using std::pair;

namespace nt
{
    // Sieve of Eratosthenes
    void primeSieve(int max, vector<bool> & sieve)
    {
	// initialize the sieve
	if(max>sieve.size()) sieve.resize(max);
	std::fill(sieve.begin(), sieve.begin()+max, true);
	sieve[0] = sieve[1] = false;

	int primeLimit = (int) sqrt(max-0.5);

	for(int p = 2; p<=primeLimit; p++)
	{
	    if(sieve[p])
	    {
		for(int k = p*p; k<max; k += p)
		{
		    sieve[k] = false;
		}
	    }
	}
	return;
    }

  
    // Sieve of Eratosthenes with list of primes
    vector<int> primes(int max, vector<bool> & sieve)
    {
	primeSieve(max, sieve);
	vector<int> pr;

	for(int p=2; p<max; p++)
	{
	    if(sieve[p]) pr.push_back(p);
	}
	return pr;
    }
    // List of primes via sieve; don't return sieve
    vector<int> primes(int max)
    {
	vector<bool> sieve;
	return primes(max, sieve);
    }

    // Vector of True values from sieve
    vector<int> vectorFromSieve(vector<bool> & sieve)
    {
	int max = sieve.size();

	vector<int> listVector;

	for(int k=0; k<max; k++)
	{
	    if(sieve[k]) listVector.push_back(k);
	}
	return listVector;
    }

    // Smallest Prime Factor Sieve
    void smallestPrimeFactors(int max, vector<bool> & sieve, vector<int> & smallPrimeFactors)
    {
	// initialize sieves
	if(max>sieve.size()) sieve.resize(max);
	if(max>smallPrimeFactors.size()) smallPrimeFactors.resize(max);
	std::fill(sieve.begin(), sieve.begin()+max, true);
	std::fill(smallPrimeFactors.begin(), smallPrimeFactors.begin()+max, 0);
	sieve[0] = sieve[1] = false;
	smallPrimeFactors[1] = 1;

	int primeLimit = (int) sqrt(max-0.5);

	for(int p=2; p<max; p++)
	{
	    if(sieve[p])
	    {
		smallPrimeFactors[p] = p;
		if(p<=primeLimit)
		{
		    for(long k = p*p; k<max; k += p)
		    {
			// only set smallPrimeFactors[k] when we find its first
			// prime factor!
			if(sieve[k])
			{
			    sieve[k] = false;
			    smallPrimeFactors[k] = p;
			}
		    }
		}
	    }
	}
	return;
    }

    // Power of Smallest Prime Factor Sieve
    void smallestPrimePowers(int max, vector<bool> & sieve, vector<int> & smallPrimeFactors, vector<int> & smallPrimePowers, vector<int> & exponents)
    {
	// initialize sieves
	if(max>sieve.size()) sieve.resize(max);
	if(max>smallPrimeFactors.size()) smallPrimeFactors.resize(max);
	if(max>smallPrimePowers.size()) smallPrimePowers.resize(max);
	if(max>exponents.size()) exponents.resize(max);
	std::fill(sieve.begin(), sieve.begin()+max, true);
	std::fill(smallPrimeFactors.begin(), smallPrimeFactors.begin()+max, 0);
	std::fill(smallPrimePowers.begin(), smallPrimePowers.begin()+max, 0);
	std::fill(exponents.begin(), exponents.begin()+max, 0);
	sieve[0] = sieve[1] = false;
	smallPrimeFactors[1] = smallPrimePowers[1] = 1;

	int primeLimit = (int) sqrt(max-0.5);

	for(int p=2; p<max; p++)
	{
	    if(sieve[p])
	    {
		smallPrimeFactors[p] = smallPrimePowers[p] = p;
		exponents[p] = 1;
		if(p<=primeLimit)
		{
		    long power = p;
		    int expon = 1;

		    /* have to hit powers in decreasing order so that we set
		     * smallPrimePowers and exponents when at max value
		     * We only set these the first time we find a number isn't
		     * prime to avoid overwriting correct information.
		     */
		    
		    while(power*p < max)
		    {
			power *= p;
			expon++;
		    }
		    while(power > p)
		    {
			for(long k = power; k < max; k += power)
			{
			    if(sieve[k])
			    {
				sieve[k] = false;
				smallPrimeFactors[k] = p;
				smallPrimePowers[k] = power;
				exponents[k] = expon;
			    }
			}
			power /= p;
			expon--;
		    }
			    
		    for(long k = p*p; k<max; k += p)
		    {
			if(sieve[k])
			{
			    sieve[k] = false;
			    smallPrimeFactors[k] = p;
			    smallPrimePowers[k] = p;
			    exponents[k] = 1;
			}
		    }
		}
	    }
	}
	return;
    }


    // Euler's Totient Function Sieve
    void eulerTotientSieve(int max, vector<bool> & sieve, vector<int> & totients)
    {
	// initialize sieves
	if(max>sieve.size()) sieve.resize(max);
	if(max>totients.size()) totients.resize(max);
	std::fill(sieve.begin(), sieve.begin()+max, true);
	std::fill(totients.begin(), totients.begin()+max, 1);
	sieve[0] = sieve[1] = false;
	totients[0] = 0;

	for(int p = 2; p < max; p++)
	{
	    if(sieve[p])
	    {
		// start by multiplying each totient by p for each power of
		// p in its prime factorization beyond the first
		long power = p;
		while(power*p < max) power *= p;
		while(power > p)
		{
		    for(long k = power; k<max; k += power)
		    {
			totients[k] *= p;
		    }
		    power /= p;
		}
		totients[p] = p-1;
		for(long k = 2*p; k < max; k += p)
		{
		    sieve[k] = false;
		    totients[k] *= p-1;
		}
	    }
	}
	return;
    }

    
    //methods to compute PI(n) using Lehmer's method.  Somehow still slowish...
    long countPrimes_phi(long max, long primeNo, map<pair<long, int>, long> & memo, vector<int> & primes)
    {
	if(primeNo == 1) return (max+1)/2;

	if(memo.count(pair<long, int>(max, primeNo)))
	    return memo[pair<long, int>(max, primeNo)];

	long ans = countPrimes_phi(max, primeNo-1, memo, primes) - countPrimes_phi(max/primes[primeNo-1], primeNo-1, memo, primes);
	memo[pair<long, int>(max, primeNo)] = ans;
	return ans;
    }

    long countPrimes_helper(long max, vector<int> & primes, map<long, long> & memo)
    {
	if(max<2) return 0;
	if(memo.count(max)) return memo[max];
	if(max <= primes[primes.size()-1])
	{
	    int mn = 0, mx = primes.size()-1, md;
	    while(mn<mx)
	    {
		md = (mn+mx+1)/2;
		if(primes[md]>max) mx = md-1;
		else mn = md;
	    }
	    memo[max] = mn+1;
	    return mn+1;
	}

	long fthrtMax = (long)(pow(max, 1.0/4)+0.00000001);
	long cbrtMax = (long)(pow(max, 1.0/3)+0.00000001);
	long sqrtMax = (long)(sqrt(max)+0.00000001);

	int piSqrtMax = countPrimes_helper(sqrtMax, primes, memo);
	int piCbrtMax = countPrimes_helper(cbrtMax, primes, memo);
	int piFthrtMax = countPrimes_helper(fthrtMax, primes, memo);
	
	
	map<pair<long, int>, long> phisMemo;
	long ans = countPrimes_phi(max, piFthrtMax, phisMemo, primes) + ((piSqrtMax+piFthrtMax-2)*(piSqrtMax-piFthrtMax+1))/2;

	for(int i = piFthrtMax+1; i <= piSqrtMax; i++)
	{
	    long quot = max / primes[i-1];
	    long piSqrtQuot = countPrimes_helper((long)(sqrt(quot)+0.0000001), primes, memo);

	    ans -= countPrimes_helper(quot, primes, memo);
	    if(i <= piCbrtMax)
	    {
		for(int j = i; j <= piSqrtQuot; j++)
		{
		    ans = ans - countPrimes_helper(quot/primes[j-1], primes, memo) + j - 1;
		}
	    }
	}
	memo[max] = ans;
	return ans;
    }

    long countPrimes(long max, vector<int> & primes)
    {
	map<long, long> piMemo;
	return countPrimes_helper(max, primes, piMemo);
    }

    long countPrimesMemoized(long max, vector<int> & primes, map<long, long> & memo)
    {
	return countPrimes_helper(max, primes, memo);
    }

	
	

}
