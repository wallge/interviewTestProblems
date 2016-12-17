#include <iostream>
#include <random>

#include "primeFactorComputer.h"

//generate numTests random numbers in the range 1 to INT_MAX and plug them into our primeFactorComputer class
//we then calculate whether the answer is correct for each randomly generated input number
//we return 0 if the test succeeds, -1 if it fails
int testPrimeFactors(int numTests) {

    //setup the random number generator
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> uniform(1, INT_MAX);

    int i = 0;
    //loop until we compute all the tests
    while (i < numTests) {
        int testInput = uniform(rng);
        primeFactorComputer testPrimeFactors(testInput);

        int computed = testPrimeFactors.evaluatePrimeFactors();
        bool allElementsArePrime = testPrimeFactors.testPrimality();

        if (computed != testInput || !allElementsArePrime) {
            std::cout << "input = " << testInput << " computed product = " << computed << " allElementsArePrime = " << allElementsArePrime << std::endl;
            return -1;
        }
        i++;
    }

    return 0;
}

int main() {
    //int input = 5280;

    //primeFactorsVectorType primeFactors = findPrimeFactors(input);
    //std::cout << "size = " << primeFactors.size() << std::endl;
    //std::cout << std::endl << "input = " << input << " check = " << evaluatePrimeFactors(primeFactors);

    std::cout << testPrimeFactors(1000000);

    return 0;
}