// Bunnies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "utils.h"
#include "Bunny.h"
#include "Bunnies.h"

std::ofstream file;

std::atomic<bool> rabit_cull;
std::atomic<bool> quit;
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

void keyboard_monitor()
{
	char k;
	while (!quit) 
	{
		if (_kbhit())
			k = _getch();
		else
			continue;
		if (!rabit_cull && (tolower(k)))
			rabit_cull = true;
	}
	std::cout << "quitting subthread" << std::endl;
}

int main()
{
	// file handler
	file.open("bunnies.txt", std::ofstream::out | std::ofstream::trunc);
	// new random seed
	srand(time(0));

	// Init environment
	quit = false;
	rabit_cull = false;

	// Keyboard Monitor
	 std::thread t_keyboard(keyboard_monitor);

	// Global starting time
	auto global_start = Time::now();
	// Init 5 bunnies
	Bunnies bunnies(5);

	print_label('#', std::string("INIT ENV"));
	bunnies.bunnies_info();
	print_label('#', std::string(""));

	// local start, end
	std::chrono::time_point<std::chrono::system_clock> start, end;
	char ch;
	int turn = 0;
	while (!bunnies.empty() && turn++ < 10)
	{
		std::cout << std::string("Round " + std::to_string(turn)) << std::endl;
		print_label('#', std::string("Round " + std::to_string(turn)));

		// Round starting now
		start = Time::now();
		// If total bunnies are more than 1000, kill half of bunnies
		if (bunnies.count() > 1000)
			bunnies.kill_bunnies(bunnies.count() / 2);

		// If a bunny becomes older than 10 years old, it dies.
		// Radioactive vampire bunnies do not die until they reach age 50.
		bunnies.kill_old_bunnies();

		if (rabit_cull)
		{
			bunnies.kill_bunnies(bunnies.count() / 2);
			rabit_cull = 0;
		}
		sleep_util(start, 0.5);

		// New bunnies
		bunnies.reproduction();

		if (rabit_cull)
		{
			bunnies.kill_bunnies(bunnies.count() / 2);
			rabit_cull = 0;
		}
		sleep_util(start, 1);

		// infect non-rad into rad
		bunnies.infection();

		if (rabit_cull)
		{
			bunnies.kill_bunnies(bunnies.count() / 2);
			rabit_cull = 0;
		}
		sleep_util(start, 1.5);

		// age plus 1 and print bunnies
		bunnies.bunnies_info();
		bunnies.grow();

		if (rabit_cull)
		{
			bunnies.kill_bunnies(bunnies.count() / 2);
			rabit_cull = 0;
		}
		sleep_util(start, 2);

		print_label('#', "This round takes " + std::to_string(dsec(Time::now() - start).count()));
		file.flush();
		sleep(1000);
	}

	print_label('#', "END");
	// Global ending
	auto global_end = Time::now();
	print_label('#', "Total " + std::to_string(turn--) + " rounds, elapsed time: " + std::to_string((std::chrono::duration<double>(global_end - global_start)).count()));
	bunnies.kill_all_bunnies();

	// Quitting threads
	quit = true;
	t_keyboard.join();

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
