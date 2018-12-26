#include "pch.h"
#include "Bunnies.h"

Bunnies::Bunnies() : id(0), m_flag(-1), f_flag(-1){}
Bunnies::Bunnies(int num) : id(0), m_flag(-1), f_flag(-1)
{
	for (int i = 0; i < num; ++i)
	{
		Bunnies::add_bunny(bunnies, new Bunny(random(3), static_cast<COLOR>(random(4))), m_flag, f_flag);
	}
}
Bunnies::Bunnies(std::vector<Bunny *> & bunnies) : id(0), m_flag(-1), f_flag(-1) {} // TODO

void Bunnies::swap_to_back(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag)
{
	if (index >= bunnies.size())
		return;
	if (index > f_flag)
		std::swap(bunnies[index], bunnies.back());
	else if (bunnies[index]->sex())
	{
		std::swap(bunnies[index], bunnies[m_flag]);
		std::swap(bunnies[m_flag--], bunnies[f_flag]);
		std::swap(bunnies[f_flag--], bunnies.back());
	}
	else
	{
		std::swap(bunnies[index], bunnies[f_flag]);
		std::swap(bunnies[f_flag--], bunnies.back());
	}
}

void Bunnies::add_bunny(std::vector<Bunny *> &bunnies, Bunny *bunny, int &m_flag, int &f_flag)
{
	bunnies.push_back(bunny);
	if (bunny->vampire())
		return;
	if (!bunnies.back()->sex())
		std::swap(bunnies.back(), bunnies[++f_flag]);
	else
	{
		std::swap(bunnies.back(), bunnies[++f_flag]);
		std::swap(bunnies[f_flag], bunnies[++m_flag]);
	}
}

void Bunnies::infection(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag)
{
	Bunnies::swap_to_back(bunnies, index, m_flag, f_flag);
	bunnies.back()->mutate();
}

void Bunnies::kill_bunny(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag)
{
	Bunnies::swap_to_back(bunnies, index, m_flag, f_flag);
	delete bunnies.back();
	bunnies.pop_back();
}

void Bunnies::kill_half_bunnies(std::vector<Bunny *> &bunnies, int num, int &m_flag, int &f_flag)
{
	if (num > bunnies.size())
		return;
	for (int i = 0; i * 2 < bunnies.size(); ++i)
	{
		int index = random(bunnies.size());
		Bunnies::kill_bunny(bunnies, index, m_flag, f_flag);
	}
}

void Bunnies::kill_old_bunnies(std::vector<Bunny *> &bunnies, int &m_flag, int &f_flag)
{
	for (int i = 0; i < bunnies.size(); ++i)
	{
		if ((!bunnies[i]->vampire() && bunnies[i]->age() > 10) || (bunnies[i]->vampire() && bunnies[i]->age() > 50))
			Bunnies::kill_bunny(bunnies, i--, m_flag, f_flag);
	}
}