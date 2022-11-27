#include <iostream>
#include <vector>
#include <fstream>

/********************************************/

// prime ceiling
constexpr int PS_CEIL = 1000;

// pipe output
// CURRENTLY DOES NOT WORK, KEEP TO FALSE
constexpr bool PS_PIPED = false;

/********************************************/

std::vector<int> getPrimes(const int &ceiling)
{
	std::vector<std::pair<int, bool>> primes;
	std::vector<int> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	int maxToAdd = (int) sqrt(ceiling);
	
	primes.push_back({1,false});
	for (int i = 2; i <= ceiling; i++) primes.push_back({i,true});

	for (auto i : primes) {
		// if number is prime
		if (i.second) {
			primesReturn.push_back(i.first);

			if (i.first < maxToAdd) {
				for (int x = (i.first * 2); x <= ceiling; x += i.first) {
					if (x > ceiling) break;
					primes[x-1].second = false;
				}
			}
		}
	}
	return primesReturn;
}

int main()
{
	if (PS_PIPED) {
		// pipe output to output.txt
		std::ofstream out("output.txt");
		std::streambuf* coutbuf = std::cout.rdbuf();
		std::cout.rdbuf(out.rdbuf());
	}
	auto primes = getPrimes(PS_CEIL);
	for (int i : primes) std::cout << i << " ";

	return 0;
}
