// implementation of high precision modular arithmetic functions

#include "numthy/modarithx.hpp"

using namespace boost::multiprecision;

namespace nt
{
    //Greatest Common Divisor
    cpp_int gcd(cpp_int a, cpp_int b)
    {
	cpp_int temp;
	a = abs(a);
	b = abs(b);

	while(b>0)
	{
	    temp = b;
	    b = a%b;
	    a = temp;
	}
	return a;
}

    //Least Common Multiple
    cpp_int lcm(cpp_int a, cpp_int b)
    {
	cpp_int x =  abs(a*b);
	// answer is zero if either is zero, don't need to find GCD in that case
	return x ? x/gcd(a,b) : cpp_int(0); 
    }

    //Fast Modular Exponentiation
    long powmod(long base, long exponent, long modulus)
    {
	modulus = abs(modulus);
	int128_t ans = 1;
	int128_t aux = (base % modulus);
	if(aux<0) aux += modulus;

	if(exponent < 0)
	{
	    aux = (int128_t)modularInverse(aux, modulus);
	    if(aux==0) return -1;
	    exponent = -exponent;
	}
	
	while(exponent>0)
	{
	    if(exponent&1) ans = (ans * aux) % modulus;
	    exponent >>= 1;
	    aux = (aux * aux) % modulus;
	}
	return (long)ans;
    }
    cpp_int powmod(cpp_int base, cpp_int exponent, cpp_int modulus)
    {
	if(modulus==0) return -1;
	modulus = abs(modulus);
	cpp_int ans = 1;
	cpp_int aux = (base % modulus);
	if(aux<0) aux += modulus;

	if(exponent < 0)
	{
	    aux = modularInverse(aux, modulus);
	    if(aux==0) return -1;
	    exponent = -exponent;
	}
	
	while(exponent>0)
	{
	    if(exponent&1) ans = (ans * aux) % modulus;
	    exponent >>= 1;
	    aux = (aux * aux) % modulus;
	}
	return ans;
    }

    //Modular Factorial
    cpp_int factmod(long n, cpp_int modulus)
    {
	if(n<0 || modulus==0) return -1;
	modulus = abs(modulus);
	if(n>=modulus) return 0;

	cpp_int ans = 1;
	for(long k=2; k<=n; k++)
	{
	    ans = (ans * k) % modulus;
	}
	return ans;
    }

    //Modular Inverse, using Extended Euclidean Algorithm
    cpp_int modularInverse(cpp_int a, cpp_int modulus)
    {
	if(modulus==0) return 0;
	modulus = abs(modulus);
	if(modulus==1) return 1;
	a = a%modulus;
	if(a<0) a += modulus;

	cpp_int b = modulus;
	cpp_int temp, quot;
	cpp_int s=1, t=0; //will eventually solve a*s+modulus*t = 1

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
    cpp_int solveModularSystem(cpp_int a, cpp_int firstModulus, cpp_int b, cpp_int secondModulus)
    {
	if(firstModulus==0 || secondModulus==0) return -1;
	firstModulus = abs(firstModulus);
	secondModulus = abs(secondModulus);
	
	
	cpp_int g = gcd(firstModulus, secondModulus);
	if(g>1)
	{
	    if((b-a)%g != 0) return -1; //inconsistent congruences
	}
	cpp_int diff = ((b-a)%secondModulus)/g;
	cpp_int overallModulus = (firstModulus*secondModulus)/g;
	cpp_int ans = firstModulus * ((diff*modularInverse(firstModulus/g, secondModulus/g)) % (secondModulus/g)) + a;
	ans = ans % overallModulus;
	if(ans < 0) ans += overallModulus;

	return ans;
    }
	

    
}
