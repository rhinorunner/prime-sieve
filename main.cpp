#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

/********************************************/

// prime ceiling
constexpr uint64_t PS_CEIL = 1000;

// pipe output
constexpr bool PS_PIPED = true;

// seperator between printed values
// change to std::string if you want
constexpr char PS_SEP = '\n';

/********************************************/

std::vector<uint64_t> getPrimes(const uint64_t& ceiling)
{
	std::vector<std::pair<uint64_t, bool>> primes;
	std::vector<uint64_t> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	uint64_t maxToAdd = (uint64_t) sqrt(ceiling);
	
	primes.push_back({1,false});
	for (uint64_t i = 2; i < ceiling; i++) primes.push_back({i,true});

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
	std::cout << "processing...\n";
	auto primes = getPrimes(PS_CEIL);
	if (PS_PIPED) {
		std::ofstream out("output.txt");
		for (uint64_t& i : primes) out << i << PS_SEP;
		out.close();
	}
	else for (uint64_t& i : primes) std::cout << i << PS_SEP;

	return 0;
}
