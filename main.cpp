#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>

/********************************************/

// data type, idk make it uint64_t if youre somehow using an absurdly high number
#define PS_DATATYPE uint32_t

// prime ceiling
static constexpr PS_DATATYPE PS_CEIL = 100000000;

// pipe output
static constexpr bool PS_PIPED = true;

// seperator between printed values
// change to std::string if you want
static constexpr char PS_SEP = '\n';

/********************************************/

std::vector<PS_DATATYPE> getPrimes(const PS_DATATYPE& ceiling)
{
	std::vector<std::pair<PS_DATATYPE, bool>> primes;
	std::vector<PS_DATATYPE> primesReturn;
	// any number past this doesnt need to be processed in prime loop
	uint64_t maxToAdd = (PS_DATATYPE) sqrt(ceiling);
	
	primes.push_back({1,false});
	for (PS_DATATYPE i = 2; i < ceiling; i++) primes.push_back({i,true});

	for (auto i : primes) {
		// if number is prime
		if (i.second) {
			primesReturn.push_back(i.first);

			if (i.first < maxToAdd) {
				for (PS_DATATYPE x = (i.first * 2); x <= ceiling; x += i.first) {
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
	const auto TP1c = std::chrono::high_resolution_clock::now();
	auto primes = getPrimes(PS_CEIL);
	const auto TP2c = std::chrono::high_resolution_clock::now();
	std::cout << "done.\n";

	std::cout << "writing...\n";
	const auto TP1w = std::chrono::high_resolution_clock::now();
	if (PS_PIPED) {
		std::ofstream out("output.txt");
		for (PS_DATATYPE& i : primes) out << i << PS_SEP;
		out.close();
	}
	else for (PS_DATATYPE& i : primes) std::cout << i << PS_SEP;
	const auto TP2w = std::chrono::high_resolution_clock::now();
	std::cout << "done.\n";

	auto timeTakenCalc  = std::chrono::duration_cast<std::chrono::duration<double>> (TP2c - TP1c);
	auto timeTakenWrite = std::chrono::duration_cast<std::chrono::duration<double>> (TP2w - TP1w);

	std::cout
		<< "\ncalculate: "
		<< std::to_string(timeTakenCalc.count())
		<< "\nwrite: "
		<< std::to_string(timeTakenWrite.count())
		<< '\n';

	return 0;
}
