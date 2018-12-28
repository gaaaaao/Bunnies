// Bunnies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "Bunny.h"
#include "Bunnies.h"

std::ofstream file;

void print_label(char label, const std::string msg)
{
	if (msg.length() == 0)
	{
		file << std::string(50, label) << '\n';
		return;
	}
	int n = (50 - msg.length() - 2) >> 1;
	file << std::string(n, label) << ' ' << msg << ' ' << std::string(n, label) << '\n';
}

int main()
{
	// file handler
	file.open("bunnies.txt", std::ofstream::out | std::ofstream::trunc);
	// new random seed
	srand(time(0));

	// Init 5 bunnies
	Bunnies bunnies(5);

	print_label('#', std::string("INIT ENV"));
	bunnies.bunnies_info();
	print_label('#', std::string(""));

	int turn = 0;
	while (!bunnies.empty() && turn++ < 10)
	{
		std::cout << std::string("Round " + std::to_string(turn)) << std::endl;
		print_label('#', std::string("Round " + std::to_string(turn)));
		// If total bunnies are more than 1000, kill half of bunnies
		if (bunnies.count() > 1000)
			bunnies.kill_bunnies(bunnies.count() / 2);

		// If a bunny becomes older than 10 years old, it dies.
		// Radioactive vampire bunnies do not die until they reach age 50.
		bunnies.kill_old_bunnies();

		// New bunnies
		bunnies.reproduction();
		// infect non-rad into rad
		bunnies.infection();
		// age plus 1 and print bunnies
		bunnies.bunnies_info();
		bunnies.grow();
		file.flush();
	}

	print_label('#', "END");
	bunnies.kill_all_bunnies();
	// close file handle
	file.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
