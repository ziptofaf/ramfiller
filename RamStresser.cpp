// RamStresser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
struct Filler {
	double a, b, c, d; //32 bytes
	Filler() {
		a = 1;
	}
};
using std::cout;
using std::endl;
using std::cin;
using std::vector;

void fillPart(long long howMany, vector<Filler> &vec)
{
	for (long long i = 0; i < howMany; i++)
		vec.push_back(Filler());
	std::this_thread::sleep_for(std::chrono::milliseconds(1000)); //this delay is added to make memory filling slower
}

void clearPart(long long howMany, vector<Filler> &vec)
{
	auto initialSize = vec.size();
	vec.erase(vec.begin(), vec.begin() + howMany);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int main()
{
	long long megabytes;
	cout << "How much RAM do you have (in megabytes): ";
	cin >> megabytes;
	long long bytes = megabytes * 1000 * 1000; //not 1024 because OS and whatnot wants some of it too
	long long maxElements = bytes / sizeof(Filler);
	vector<Filler> megaVec;

	for (int i = 1; i <= 10; i++)
	{
		cout << "Filling " << i * 10 << "% RAM" << endl;
		fillPart(maxElements / 10, megaVec);
	}

	for (int i = 1; i <= 10; i++)
	{
		clearPart(maxElements / 10, megaVec);
		cout << "Clearing " << i * 10 << "% RAM" << endl;
	}

    return 0;
}

