// Bunnies.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

#define random(x) (rand() % (int)x)

// out handle
ofstream file;

enum COLOR
{
	WHITE,
	BROWN,
	BLACK,
	SPOTTED
};

int id = 0;

class Bunny
{
private:
	bool m_sex;
	COLOR m_color;
	int m_age;
	string m_name;
	bool m_vampire;

public:
	Bunny(int a, COLOR c) : m_sex(random(2)), m_color(c), m_age(a), m_name(to_string(id++)), m_vampire(random(50))
	{
		if (!m_vampire)
			file << "Radioactive Mutant Vampire Bunny " << m_name << " was born!" << '\n';
		else
			file << "Bunny " << m_name << " was born!" << '\n';
	}
	bool sex() { return m_sex; }
	int color() { return m_color; }
	int age() { return m_age; }
	void grown() { m_age++; }
	bool vampire() { return m_vampire; }
	string name() { return m_name; }
	string p_bunny()
	{
		string output = "";
		output += string("SEX:\t") + (m_sex ? "M\n" : "F\n");
		switch (m_color)
		{
		case WHITE:
			output += "COLOR:\tWHITE\n";
			break;
		case BROWN:
			output += "COLOR:\tBROWN\n";
			break;
		case BLACK:
			output += "COLOR:\tBLACK\n";
			break;
		case SPOTTED:
			output += "COLOR:\tSPOTTED\n";
			break;
		}
		output += "AGE:\t" + to_string(m_age) + '\n';
		output += "NAME:\t" + m_name + '\n';
		output += string("VAMPIRE:\t") + (m_vampire ? "N\n" : "V\n");
		return output;
	}
	~Bunny()
	{
		if (!m_vampire)
			file << "Radioactive Mutant Vampire Bunny " << m_name << " died!" << '\n';
		else
			file << "Bunny " << m_name << " died!" << '\n';
	}
};

// void kill_bunnies(vector<Bunny *> &bunnies, const int & l)
// {
//     for (auto iter = bunnies.begin() + l; iter < bunnies.end(); ++iter)
//     {
//         cout << "Killing bunny: " << (*iter)->name() << endl;
//         delete *iter;
//     }
//     cout << "There are " << l << " bunnies still in list" << endl;
//     bunnies.resize(l);
// }

void add_bunny(vector<Bunny *> &bunnies, Bunny *bunny, int &m_flag, int &f_flag)
{
	bunnies.push_back(bunny);
	if (!bunnies.back()->sex())
		swap(bunnies.back(), bunnies[++f_flag]);
	else
	{
		swap(bunnies.back(), bunnies[++f_flag]);
		swap(bunnies[f_flag], bunnies[++m_flag]);
	}
}

void infection(vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag)
{
	if (index >= bunnies.size())
		return;
	if (index > f_flag)
		swap(bunnies[index], bunnies.back());
	else if (bunnies[index]->sex())
	{
		swap(bunnies[index], bunnies[m_flag]);
		swap(bunnies[m_flag--], bunnies[f_flag]);
		swap(bunnies[f_flag--], bunnies.back());
	}
	else
	{
		swap(bunnies[index], bunnies[f_flag]);
		swap(bunnies[f_flag--], bunnies.back());
	}
}

void kill_bunny(vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag)
{
	infection(bunnies, index, m_flag, f_flag);
	delete bunnies.back();
	bunnies.pop_back();
}

void kill_half_bunnies(vector<Bunny *> &bunnies, int num, int &m_flag, int &f_flag)
{
	if (num > bunnies.size())
		return;
	for (int i = 0; i * 2 < bunnies.size(); ++i)
	{
		int index = random(bunnies.size());
		kill_bunny(bunnies, index, m_flag, f_flag);
	}
}

void kill_old_bunnies(vector<Bunny *> &bunnies, int &m_flag, int &f_flag)
{
	for (int i = 0; i < bunnies.size(); ++i)
	{
		if (
			(bunnies[i]->vampire() && bunnies[i]->age() > 10) ||
			(!bunnies[i]->vampire() && bunnies[i]->age() > 50))
			kill_bunny(bunnies, i--, m_flag, f_flag);
	}
}

void print_label(char label, const string msg)
{
	if (msg.length() == 0)
	{
		file << string(50, label) << '\n';
		return;
	}
	int n = (50 - msg.length() - 2) >> 1;
	file << string(n, label) << ' ' << msg << ' ' << string(n, label) << '\n';
}

int main()
{
	// file handler
	file.open("bunnies.txt", ios::app);
	// new random seed
	srand(time(0));

	// bunnies list
	vector<Bunny *> bunnies;
	int m_flag = -1;
	int f_flag = -1;
	// Init 5 bunnies
	for (int i = 0; i < 5; ++i)
	{
		add_bunny(bunnies, new Bunny(random(3), static_cast<COLOR>(random(4))), m_flag, f_flag);
	}

	print_label('#', string("INIT ENV"));
	for (int i = 0; i < bunnies.size(); ++i)
		file << bunnies[i]->p_bunny() << '\n';
	print_label('#', string(""));
	// kill_half_bunnies(bunnies, bunnies.size() / 2, m_flag, f_flag);

	// cout << "************************" << endl;
	// kill_old_bunnies(bunnies, m_flag, f_flag);
	// cout << "************************" << endl;
	// for (int i = 0; i < bunnies.size(); ++i)
	//     cout << bunnies[i]->p_bunny() << endl;
	// cout << "************************" << endl;
	int turn = 0;
	while (!bunnies.empty() && turn++ < 10)
	{
		cout << string("Round " + to_string(turn)) << endl;
		print_label('#', string("Round " + to_string(turn)));
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
				for (int j = m_flag + 1; j <= f_flag; ++j)
				{
					if (bunnies[j]->age() >= 2)
						add_bunny(bunnies, new Bunny(-1, static_cast<COLOR>(bunnies[j]->color())), m_flag, f_flag);
				}
				break;
			}
		}
		// infect non-rad into rad
		for (int i = f_flag + 1; i < bunnies.size(); ++i)
		{
			infection(bunnies, random(f_flag + 1), m_flag, f_flag);

		}

		// age plus 1 and print bunnies
		for (auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		{
			file << (*iter)->p_bunny() << '\n';
			(*iter)->grown();
		}
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
