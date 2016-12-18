#include <iostream>
#include <random>
#include <climits>
#include <cstdlib>
#include "primeFactorComputer.h"

//generate numTests random numbers in the range 1 to INT_MAX and plug them into our primeFactorComputer class
//we then calculate whether the answer is correct for each randomly generated input number
//we return 0 if the test succeeds, -1 if it fails
//this is only used for testing purposes and is not part of the main program
int testPrimeFactors(int numTests) {

    if (numTests < 1)
        return -1;

    //setup the random number generator
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> uniform(2, INT_MAX);

    int i = 0;
    //loop until we compute all the tests
    while (i < numTests) {
        int testInput = uniform(rng);
        primeFactorComputer testPrimeFactors(testInput);

        int computed = testPrimeFactors.evaluatePrimeFactors();
        bool allElementsArePrime = testPrimeFactors.testPrimality();

        std::cout << testInput << std::endl;
        testPrimeFactors.printPrimeFactors();

        if (computed != testInput || !allElementsArePrime) {
            std::cout << "*****************************************************************\n";
            std::cout << "ERROR input = " << testInput << " computed product = " << computed << " allElementsArePrime = " << allElementsArePrime << std::endl;
            return -1;
        }

        i++;
    }

    return 0;
}


//If you run the program with no arguments, it runs as specified in the assignment description,
//if you run the program with a single argument that is a positive integer, it will run in test mode.
//Test mode will generate random positive integers (the number of which is specified by the command line argument)
//and then run them through the prime factors algorithm and check the answers for correctness.
int main(int argc, char **argv) {

    if ( argc >= 2 ) {
        std::cout << argv[0] << ' ' << argv[1] << std::endl;
        int i = atoi(argv[1]);
        testPrimeFactors(i);
    } else {

        signed long i;

        while (1) {
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

            if (i < 2) {
                std::cout << "Only positive values larger than 1 are permitted. Exiting." << std::endl;
                return -1;
            }

            primeFactorComputer testPrimeFactors((int) i);
            testPrimeFactors.printPrimeFactors();
        }
    }

    return 0;
}