# -*- coding: utf-8 -*-
"""
Created on Sun Nov  1 11:59:44 2015

@author: Geoffrey Wall

usage: python fibonacci.py -n <number of fibonacci numbers to generate>
usage: python fibonacci.py -t <number of fibonacci numbers to generate and test against reference implementation>
           
"""
#!/usr/bin/python

import sys, math
import numpy as np

# generate the fibonacci sequence the traditional recursive way
def genFibRecursive(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        return genFibRecursive(n-1) + genFibRecursive(n-2)


# generate the fibonacci sequence recursively, but this time using a
# dictionary to store already computed fibonacci numbers
def genFibMemoized(n, memo):
    if n == 0:
        return 0
    elif n == 1:
        return 1
    else:
        ##check to see if we have already computed this fibonacci number and stored it in
        ##our dictionary
        if n in memo:
            return memo[n]
        else:
            n_1 = 0
            if n-1 in memo:
                n_1 = memo[n-1]
            else:
                n_1 = genFibMemoized(n-1, memo)

            n_2 = 0
            if n-2 in memo:
                n_2 = memo[n-2]
            else:
                n_2 = genFibMemoized(n-2, memo)

            fib = n_1 + n_2
            memo[n] = fib

    return fib
   
#generate the fibbonacci sequence looping over fibbonacci's 2 thru n and summing previous values   
#this is less expensive in compute time as well as memory consumed compared to the naive recursive formulation
def genFibMemConstrained(n):
    if n == 0:
        return 0
    elif n == 1:
        return 1

    Fn = 0
    FnMinusOne = 1
    FnMinusTwo = 0
    for i in range(2, n+1):
        Fn = FnMinusOne + FnMinusTwo
        FnMinusTwo = FnMinusOne
        FnMinusOne = Fn
        
    return Fn
        
#generate the fibbonacci sequence using the linear algebra formulation by exponentiating
#the fibonacci matrix [1, 1; 1, 0] to the n-1th power and returning the 0,0th element of the resultant matrix
#this comes from the difference equation formulation from here:
#https://en.wikipedia.org/wiki/Fibonacci_number#Matrix_form
#note::this runs into precision issues once we get to n = 94      
def genFibLinAlg(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
                
    M = np.matrix('1, 1; 1, 0')
    M = M.astype(np.uint64)
    #exponentiate the matrix to the n-1'th power
    F = M**(n-1) 
    return F[0, 0]   
    
#this method uses the recurrence relation from here:
# https://en.wikipedia.org/wiki/Fibonacci_number#Closed-form_expression
def genFibFast(n):
    def _inner(n):
        if n == 0:
            return (0, 1)
        else:
            a, b = _inner(n // 2)
            c = a * (b * 2 - a)
            d = a * a + b * b
            if n % 2 == 0:
                return (c, d)
            else:
                return (d, c + d)    
                
    return _inner(n)[0]
    
    
def genFibGoldenRatio(n):
    golden = np.double(1.61803398875)
    
    Fn = (math.pow(golden, n) - math.pow(1 - golden, n)) / math.sqrt(5.0)
    
    return (round(Fn))
    
#loop over all natural numbers in range [2, n-1] and see if they will divide into n without a remainder
#this is the dumb (obvious) way to do this    
def isPrimeNaive(n):
    if n < 2:
        return False

    for i in range(2, n):
        if n % i == 0:
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
            
#this function implements the faster, less naive version of what the 
#interview problem is asking for            
def generateInterviewProblemResult(n):
    myList = []
    for i in range(0, n+1):
        fib = genFibFast(i)
        #method below runs into precision issues 
        #genFibLinAlg(i)
        if fib % 3 == 0:
            myList.append('Buzz')
        elif fib % 5 == 0:
            myList.append('Fizz')
        elif isPrime(i):
            myList.append('BuzzFizz')
        else:
            myList.append(fib)

    return myList            

   
#this function implements the dumb but simpler reference implementation 
#of what the interview problem is asking for 
def generateReferenceResult(n):
    myList = []
    
    for i in range(0, n+1):
        #fib = genFibMemConstrained(i)
        fib = genFibMemoized(i, dict())
        if fib % 3 == 0:
            myList.append('Buzz')
        elif fib % 5 == 0:
            myList.append('Fizz')
        elif isPrimeNaive(i):
             myList.append('BuzzFizz')
        else:
            myList.append(fib)
          
    return myList              
           
        
def main(argv):
    
    if len(argv) < 2:
        print 'usage: python fibonacci.py -n <number of fibonacci numbers to generate>'
        print 'usage: python fibonacci.py -t <number of fibonacci numbers to generate and test against reference implementation>'
        sys.exit(2)
    else:    
        if argv[0] == '-n':
            print generateInterviewProblemResult(int(argv[1]))
        elif argv[0] == '-t':
            myResult = generateInterviewProblemResult(int(argv[1]))
            referenceResult = generateReferenceResult(int(argv[1]))
            
            print myResult
            
            caughtError = False
            for i in range(0, len(myResult)):
                if myResult[i] != referenceResult[i]:
                    print "Reference Implementation does not match my implementation for n = " + str(i)
                    print "Reference value = " + str(referenceResult[i])
                    print "Generated value = " + str(myResult[i])
                    caughtError = True
                    
            if caughtError == False:
               print 'Reference implementation matched my implementation for all ' + str(i) + ' Fibonacci numbers!'
                
        else:
            print 'usage: python fibonacci.py -n <number of fibonacci numbers to generate>'
            print 'usage: python fibonacci.py -t <number of fibonacci numbers to generate and test against reference implementation>'
           

if __name__ == "__main__":
    main(sys.argv[1:])