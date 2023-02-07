#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

/********************************************/

// prime ceiling
constexpr uint64_t PS_CEIL = 25;

// pipe output
// CURRENTLY DOES NOT WORK, KEEP TO FALSE
constexpr bool PS_PIPED = false;

/********************************************/

std::vector<uint64_t> getPrimes(const uint64_t& ceiling)
{
	std::vector<std::pair<uint64_t, bool>> primes;
	std::vector<uint64_t> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	uint64_t maxToAdd = (uint64_t) sqrt(ceiling);
	
	primes.push_back({1,false});
	for (uint64_t i = 2; i <= ceiling; i++) primes.push_back({i,true});

	for (auto i : primes) {
		// if number is prime
		if (i.second) {
			primesReturn.push_back(i.first);

			if (i.first < maxToAdd) {
				for (uint64_t x = (i.first * 2); x <= ceiling; x += i.first) {
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
	for (uint64_t i : primes) std::cout << i << " ";

	return 0;
}
