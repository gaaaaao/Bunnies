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

	// bunnies list
	std::vector<Bunny *> bunnies;
	int m_flag = -1;
	int f_flag = -1;
	// Init 5 bunnies
	for (int i = 0; i < 5; ++i)
	{
		add_bunny(bunnies, new Bunny(random(3), static_cast<COLOR>(random(4))), m_flag, f_flag);
	}

	print_label('#', std::string("INIT ENV"));
	for (int i = 0; i < bunnies.size(); ++i)
		file << bunnies[i]->p_bunny() << '\n';
	print_label('#', std::string(""));

	int turn = 0;
	while (!bunnies.empty() && turn++ < 10)
	{
		std::cout << std::string("Round " + std::to_string(turn)) << std::endl;
		print_label('#', std::string("Round " + std::to_string(turn)));
		// If total bunnies are more than 1000, kill half of bunnies
		if (bunnies.size() > 1000)
			kill_bunny(bunnies, bunnies.size() / 2, m_flag, f_flag);

		// If a bunny becomes older than 10 years old, it dies.
		// Radioactive vampire bunnies do not die until they reach age 50.
		kill_old_bunnies(bunnies, m_flag, f_flag);

		// New bunnies
		for (int i = 0; i <= m_flag; ++i)
		{
			if (bunnies[i]->age() >= 2)
			{
				int tmp = f_flag;
				for (int j = m_flag + 1; j <= tmp; ++j) // till tmp f_flag, cause if the new born bunny is male and not vampire, it will swap with the first female bunny, and it will cause duplication.
				{
					if (bunnies[j]->age() >= 2 && !bunnies[j]->vampire())
						add_bunny(bunnies, new Bunny(0, static_cast<COLOR>(bunnies[j]->color())), m_flag, f_flag);
				}
				break;
			}
		}
		// infect non-rad into rad
		for (int i = f_flag + 1; i < bunnies.size() && f_flag > 0; ++i)
			infection(bunnies, random(f_flag + 1), m_flag, f_flag);

		// age plus 1 and print bunnies
		for (auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		{
			file << (*iter)->p_bunny() << '\n';
			(*iter)->grown();
		}
		file.flush();
	}

	print_label('#', "END");
	//release everything
	for (auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		delete *iter;

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
