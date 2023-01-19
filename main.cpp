#include <iostream>
#include <vector>
#include <fstream>

/********************************************/

// prime ceiling
constexpr uint16_t PS_CEIL = 1000;

// pipe output
// CURRENTLY DOES NOT WORK, KEEP TO FALSE
constexpr bool PS_PIPED = false;

/********************************************/

std::vector<uint16_t> getPrimes(const uint16_t& ceiling)
{
	std::vector<std::pair<uint16_t, bool>> primes;
	std::vector<uint16_t> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	uint16_t maxToAdd = (uint16_t) sqrt(ceiling);
	
	primes.push_back({1,false});
	for (uint16_t i = 2; i <= ceiling; i++) primes.push_back({i,true});

	for (auto i : primes) {
		// if number is prime
		if (i.second) {
			primesReturn.push_back(i.first);

			if (i.first < maxToAdd) {
				for (uint16_t x = (i.first * 2); x <= ceiling; x += i.first) {
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
	for (uint16_t i : primes) std::cout << i << " ";

	return 0;
}
