# -*- coding: utf-8 -*-
"""
Created on Sun Nov  1 11:59:44 2015

@author: Geoffrey Wall
"""

import numpy as np

# generate the fibonacci sequence the traditional recursive way
def genFibRecursive(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return genFibRecursive(n-1) + genFibRecursive(n-2)
   
#generate the fibbonacci sequence looping over fibbonacci's 2 thru n and summing previous values   
#this is less expensive in compute time as well as memory consumed compared to above
def genFibMemConstrained(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1

    Fn = 0
    FnMinusOne = 1
    FnMinusTwo = 0
    for i in range(2 , n+1):
        Fn = FnMinusOne + FnMinusTwo
        FnMinusTwo = FnMinusOne
        FnMinusOne = Fn
        
    return Fn
        
#generate the fibbonicci sequence using the linear albebra formulation by exponentiating  
#the fibonacci matrix [1, 1; 1, 0] to the n-1th power and returning the 0,0th element of the resultant matrix
#this comes from the difference equation formulation form here:
#https://en.wikipedia.org/wiki/Fibonacci_number#Matrix_form
        
def genFibLinAlg(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
                
    M = np.matrix('1, 1; 1, 0')
    #exponentiate the matrix to the n-1'th power
    F = M**(n-1) 
    #return the 0,0'th matrix element, which is equal to Fm+1 which is our Nth fibonacci number (Fn)
    return F[0, 0]    
    
    
#loop over all natural numbers in range [2, n-1] and see if they will divide into n without a remainder
#this is the dumb (obvious) way to do this    
def isPrimeNaive(n):
    if n < 2:
        return False
      
    for i in range(2, n):
        if  n % i == 0:
            return False

    return True

    
def isPrime(n):
    #primes are defined as being greater than 1
    if n <= 1:
        return False
    # two and three are prime, return true    
    elif n <= 3:
        return True
    #test if divisible by two or three, return false    
    elif n % 2 == 0 or n % 3 == 0:
        return False
        
    #five is the next divisor to check    
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i + 2) == 0:
            return False
        i = i + 6
    #if we pass the above tests, then this is a prime    
    return True    
            
            
            
        
for i in range(0, 200):
    Fn = genFibLinAlg(i)
    prime = isPrime(Fn)
    
    checkFn = genFibRecursive(i)
    checkIsPrime = isPrimeNaive(checkFn)
    
    if Fn != checkFn or prime != checkIsPrime:
        print [i, Fn, prime, checkFn, checkIsPrime]    
        

print 'checks out!!!'        