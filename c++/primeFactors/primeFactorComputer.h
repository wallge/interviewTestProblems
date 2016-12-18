//
// Created by Geoffrey Wall on 12/17/16.
//

#ifndef PROJECTS_PRIMEFACTORCOMPUTER_H
#define PROJECTS_PRIMEFACTORCOMPUTER_H

#include <iostream>
#include <vector>
#include <math.h>

#define DEBUG 0


//store each prime factor and its exponent in a pair
typedef std::pair<int, int> primeFactorType;
//this vector type will store the list of prime factors
typedef std::vector<primeFactorType> primeFactorsVectorType;

//this class will compute all the prime numbers for a given number
//and also contains test routines to verify correctness
class primeFactorComputer {

public:
    int number;
    primeFactorsVectorType primeFactors;

    //the constructor: pass in the number we want to find
    //the prime factors for and then compute them
    primeFactorComputer(int n) : number(n) {
        if (n < 2)
            return;
        findPrimeFactors();
    }

    //for a given input int, find the prime factors and store them in a vector
    void findPrimeFactors() {
        int i = 0;
        int n = number;
#if DEBUG
        std::cout << std::endl << "input = " << n << " prime factors:";
#endif
        // First handle all of the prime factors which are equal to 2
        while (n%2 == 0) {
#if DEBUG
            std::cout << 2 << " ";
#endif
            n = n/2;
            //prime factor does not exist in the vector yet, go ahead and add it
            if (primeFactors.empty()) {
                primeFactors.push_back(std::make_pair(2, 1));
            } else {
                //this prime factor already exists in the vector, go ahead and increment its exponent
                primeFactors.back().second++;
            }
        }

        // n must be odd at this point.  So we can skip one element (Note i = i+2)
        for (i = 3; i <= sqrtf(n); i = i+2) {
            // While i divides n, print i and divide n
            while (n%i == 0) {
#if DEBUG
                std::cout << i << " ";
#endif
                n = n/i;

                //this prime factor does not exist in the list yet, go ahead and add it
                if (primeFactors.empty() || (primeFactors.back().first != i)) {
                    primeFactors.push_back(std::make_pair(i, 1));
                } else {
                    //this prime factor already exists in the vector, go ahead and increment its exponent
                    primeFactors.back().second++;
                }
            }
        }
        // This condition is to handle the case when n is a prime number
        // greater than 2
        if (n > 2) {
#if DEBUG
            std::cout << n << " ";
#endif
            primeFactors.push_back(std::make_pair(n, 1));
        }

        std::cout << std::endl;
    }

    //this prints the result of the calculation formatted per the interview question's requirement
    void printPrimeFactors() {
        if (primeFactors.empty())
            return;

        for (auto i = primeFactors.begin(); i != primeFactors.end(); ++i) {
            std::cout << i->first;
            //only print the exponent if it is larger than 1
            if (i->second > 1)
                std::cout << '^' << i->second;
            //if we are not at the last item in the vector, print the asterisk
            if (i+1 != primeFactors.end())
                std::cout << " * ";
            else
                std::cout << std::endl << std::endl;
        }
    }

    //check if a number is prime (this is only used to verify correctness)
    bool is_prime(int n) {
        if (n <= 1)
            return false;
        else if (n <= 3)
            return true;
        else if ((n % 2 == 0) || (n % 3 == 0))
            return false;

        int i = 5;
        while (i * i <= n) {
            if ((n % i == 0) || (n % (i + 2) == 0))
                return false;
            i += 6;
        }
        return true;
    }

    //check if each element in the vector is a prime number, (this is only used to verify correctness)
    bool testPrimality() {
        if (primeFactors.empty())
            return false;

        bool result = true;

        for (auto i = primeFactors.begin(); i != primeFactors.end(); ++i)
            result = result && is_prime(i->first);

        return result;
    }

    //multiply together all of the prime factors in order to verify that
    //their product is equal to the original input number, (this is only used to verify correctness)
    int evaluatePrimeFactors() {
        if (primeFactors.empty())
            return - 1;

        int result = 1;

        for (auto i = primeFactors.begin(); i != primeFactors.end(); ++i)
            for (int j = 1; j <= i->second; j++)
                result *= i->first;

        return result;
    }

};

#endif //PROJECTS_PRIMEFACTORCOMPUTER_H
