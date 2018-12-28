#include "pch.h"
#include "Bunnies.h"

Bunnies::Bunnies() : id(0), m_flag(-1), f_flag(-1) {}
Bunnies::Bunnies(int num) : id(0), m_flag(-1), f_flag(-1)
{
	for (int i = 0; i < num; ++i)
	{
		Bunnies::add_bunny(new Bunny(random(3), static_cast<COLOR>(random(4)), std::to_string(id++)));
	}
}
Bunnies::Bunnies(std::vector<Bunny *> &bunnies) : id(0), m_flag(-1), f_flag(-1) {} // TODO
Bunnies::~Bunnies()
{
	Bunnies::kill_all_bunnies();
}
bool Bunnies::empty() { return bunnies.empty(); }
int Bunnies::count() { return bunnies.size(); }

void Bunnies::swap_to_back(int index)
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

void Bunnies::add_bunny(Bunny *bunny)
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

void Bunnies::infection()
{
	for (int i = f_flag + 1; i < bunnies.size() && f_flag > 0; ++i)
	{
		Bunnies::swap_to_back(random(f_flag + 1));
		bunnies.back()->mutate();
	}
}

void Bunnies::kill_bunny(int index)
{
	Bunnies::swap_to_back(index);
	delete bunnies.back();
	bunnies.pop_back();
}

void Bunnies::kill_bunnies(int num)
{
	if (num > bunnies.size())
		return;
	for (int i = 0; i < num; ++i)
	{
		int index = random(bunnies.size());
		Bunnies::kill_bunny(index);
	}
}

void Bunnies::kill_old_bunnies()
{
	for (int i = 0; i < bunnies.size(); ++i)
	{
		if ((!bunnies[i]->vampire() && bunnies[i]->age() > 10) || (bunnies[i]->vampire() && bunnies[i]->age() > 50))
			Bunnies::kill_bunny(i--);
	}
}

void Bunnies::kill_all_bunnies()
{
	for (auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		delete *iter;
	bunnies.clear();
}

void Bunnies::bunnies_info()
{
	file << "There are total "
		 << bunnies.size()
		 << " bunnies, "
		 << std::to_string(m_flag + 1)
		 << " male bunnies, "
		 << std::to_string(f_flag - m_flag)
		 << " female bunnies, "
		 << std::to_string(bunnies.size() - f_flag - 1)
		 << " vampire bunnies.\n";
	auto tmp = bunnies;
	std::sort(tmp.begin(), tmp.end());
	for (auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		file << (*iter)->p_bunny() << '\n';
}

void Bunnies::reproduction()
{
	for (int i = 0; i <= m_flag; ++i)
	{
		if (bunnies[i]->age() >= 2)
		{
			int tmp = f_flag;
			for (int j = m_flag + 1; j <= tmp; ++j) // till tmp f_flag, cause if the new born bunny is male and not vampire, it will swap with the first female bunny, and it will cause duplication.
			{
				if (bunnies[j]->age() >= 2 && !bunnies[j]->vampire())
					add_bunny(new Bunny(0, static_cast<COLOR>(bunnies[j]->color()), std::to_string(id++)));
			}
			break;
		}
	}
}

void Bunnies::grow()
{
	for(auto iter = bunnies.begin(); iter != bunnies.end(); ++iter)
		(*iter)->grown();
}