#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

////////////////////////////
// Function declarations. //
////////////////////////////
// Input: An integer, n. 
// Output: True if that integer is prime, false if it isn't.
bool PrimalityCheck(int n)
{
    for (int x = n - 1; x > 1; x--)
    {
        if (n % x == 0)
        {
            return false;
        }
    }

    return true;
}
// Input: 
//      coinCount -> An integer that limits the amount of coins to be used.
//      coinSumTotal -> An integer to keep track of the current sum of coins through recursive calls.
//      primeList -> A vector of integers that holds the current primes.
// Output: The amount of solutions that were found in the search tree. 
int PrimePermutations(int coinCount, int coinSumTotal, vector<int> primeList) 
{
    // If we have used up all of our coins and have found a correct sum.
    // Of if the total sum has reached the same amount of coins used. 
    if ((coinCount == 0 && coinSumTotal == 0) || (coinCount == coinSumTotal))
    {
        return 1;
    }
    // If there is still numbers to add to the sum, or coins to use, but we have reached the max
    // of either, it's not a solution.
    if ((coinSumTotal <= 0 && coinCount != 0) || (coinCount == 0 && coinSumTotal != 0))
    {
        return 0;
    }
    int solutionCount = 0;
    // Each prime in the list is treated as a root node. 
    // So find all solutins for each tree.
    // But each level will decrease the amount of primes.
    for (int i = 0; i < primeList.size(); i++)
    {
        vector<int> newPrimeList(primeList.begin() + i, primeList.end());
        solutionCount += PrimePermutations(coinCount - 1, coinSumTotal - primeList[i], newPrimeList);
    }
    return solutionCount;
}

////////////////////
// Main function. //
////////////////////
int main(int argc, char** argv) 
{
    // Variable declarations.
    int n, coinCount, upperBound, lowerBound, solutionCount;
    vector<int> primesOfN;
    clock_t timer;
    // Variable assignments.
    coinCount = upperBound = lowerBound = solutionCount = 0;
    n = atoi(argv[1]);
    for (int i = n; i >= 1; i--)
    {
        if (PrimalityCheck(i)) 
        {
            primesOfN.push_back(i);
        }
    }
    // Switch cases based on input type.
    switch (argc)
    {
        // The first case, where there is only one argument. 
        // Just a prime number. Returns how many permutations of primes make up n.
        case 2:
            timer = clock();
            for (int i = 0; i < primesOfN.size(); i++) {
                solutionCount += PrimePermutations(primesOfN[i], n, primesOfN);
            }
            cout << solutionCount << " solutions were found in " << (float)(clock() - timer)/CLOCKS_PER_SEC << " seconds.";
            break;
        // Second case, giving the prime number to check and a limit on the amount of coins that can be used.
        case 3:
            timer = clock();
            coinCount = atoi(argv[2]);
            cout << PrimePermutations(coinCount, n, primesOfN) + 1 << " solutions were found in " << (float)(clock() - timer)/CLOCKS_PER_SEC << " seconds.";
            break;
        // Last cast, giving the prime to be checked and an upper and lower bound of the amount of coins that can be used.
        case 4:
            timer = clock();
            lowerBound = atoi(argv[2]);
            upperBound = atoi(argv[3]);
            for (int i = lowerBound; i <= upperBound; i++)
            {
                solutionCount += PrimePermutations(i, n, primesOfN);
            }
            cout << solutionCount << " solutions were found in " << (float)(clock() - timer)/CLOCKS_PER_SEC << " seconds.";
            break;
    }
    return 0;
}