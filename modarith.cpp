// implementation of modular arithmetic functions

#include "numthy/modarith.hpp"
#include<cmath>

namespace nt
{
    //Greatest Common Divisor
    int gcd(int a, int b)
    {
	int temp;
	a = std::abs(a);
	b = std::abs(b);

	while(b>0)
	{
	    temp = b;
	    b = a%b;
	    a = temp;
	}
	return a;
    }
    long gcd(long a, long b)
    {
	long temp;
	a = std::abs(a);
	b = std::abs(b);

	while(b>0)
	{
	    temp = b;
	    b = a%b;
	    a = temp;
	}
	return a;
    }

    //Least Common Multiple
    long lcm(int a, int b)
    {
	long x = a;
	x = std::abs(x*b);
	// answer is zero if either is zero, don't need to find GCD in that case
	return x ? x/gcd(a,b) : 0; 
    }

    //Fast Modular Exponentiation
    int powmod(long base, long exponent, int modulus)
    {
	if(modulus==0) return -1;
	modulus = std::abs(modulus);

	long ans = 1;
	long aux = (base % modulus);
	if(aux<0) aux += modulus;

	if(exponent < 0)
	{
	    aux = modularInverse((int)aux, modulus);
	    if(aux==0) return -1;
	    exponent = -exponent;
	}

	while(exponent>0)
	{
	    if(exponent&1) ans = (ans * aux) % modulus;
	    exponent >>= 1;
	    aux = (aux * aux) % modulus;
	}
	return (int)ans;
    }

    //Modular Factorial
    int factmod(int n, int modulus)
    {
	if(n<0 || modulus==0) return -1;
	modulus = std::abs(modulus);
	if(n>=modulus) return 0;

	long ans = 1;
	for(int k=2; k<=n; k++)
	{
	    ans = (ans * k) % modulus;
	}
	return (int)ans;
    }

    //Modular Inverse, using Extended Euclidean Algorithm
    int modularInverse(int a, int modulus)
    {
	if(modulus==0) return 0;
	modulus = std::abs(modulus);
	if(modulus==1) return 1;
	a = a%modulus;
	if(a<0) a += modulus;

	int b = modulus;
	int temp, quot;
	int s=1, t=0; //will eventually solve a*s+modulus*t = 1

	while(b>0)
	{
	    quot = a/b;
	    
	    temp = b;
	    b = a-b*quot;
	    a = temp;

	    temp = t;
	    t = s - quot * t;
	    s = temp;
	}
	if(a>1) return 0; // gcd is >1, no inverse

	if(s < 0) s += modulus;
	return s;
    }
    long modularInverse(long a, long modulus)
    {
	if(modulus==0) return 0;
	modulus = std::abs(modulus);
	if(modulus==1) return 1;
	a = a%modulus;
	if(a<0) a += modulus;

	long b = modulus;
	long temp, quot;
	long s=1, t=0; //will eventually solve a*s+modulus*t = 1

	while(b>0)
	{
	    quot = a/b;
	    
	    temp = b;
	    b = a-b*quot;
	    a = temp;

	    temp = t;
	    t = s - quot * t;
	    s = temp;
	}
	if(a>1) return 0; // gcd is >1, no inverse

	if(s < 0) s += modulus;
	return s;
    }


    //Modular System Solver
    long solveModularSystem(int a, int firstModulus, int b, int secondModulus)
    {
	if(firstModulus==0 || secondModulus==0) return -1;
	firstModulus = std::abs(firstModulus);
	secondModulus = std::abs(secondModulus);
	
	
	int g = gcd(firstModulus, secondModulus);
	if(g>1)
	{
	    if(((long)b-a)%g != 0) return -1; //inconsistent congruences
	}
	long diff = (((long)b-a)%secondModulus)/g;
	long overallModulus = ((long)firstModulus*secondModulus)/g;
	long ans = firstModulus * ((diff*modularInverse(firstModulus/g, secondModulus/g)) % (secondModulus/g)) + a;
	ans = ans % overallModulus;
	if(ans < 0) ans += overallModulus;

	return ans;
    }
	

    
}
