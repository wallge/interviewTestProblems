#include <iostream>
#include <random>
#include <climits>
#include "primeFactorComputer.h"

//generate numTests random numbers in the range 1 to INT_MAX and plug them into our primeFactorComputer class
//we then calculate whether the answer is correct for each randomly generated input number
//we return 0 if the test succeeds, -1 if it fails
//this is only used for testing purposes and is not part of the main program
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

    unsigned long i;

    while(1) {
        //executes loop if the input fails (e.g., no characters were read)
        while (std::cout << "Please enter an integer.\n" && !(std::cin >> i)) {
            std::cin.clear(); //clear bad input flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
            std::cout << "Invalid input. Exiting." << std::endl;
            return -1;
        }

        if (i > INT_MAX) {
            std::cout << "Input exceeds maximum int32 value: " << INT_MAX << ". Exiting." << std::endl;
            return -1;
        }

        primeFactorComputer testPrimeFactors((int)i);
        testPrimeFactors.printPrimeFactors();
    }

    return 0;
}