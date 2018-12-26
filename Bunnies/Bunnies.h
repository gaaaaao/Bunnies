#pragma once
#include <vector>
#include "Bunny.h"

class Bunnies
{
private:
	int id;
	std::vector<Bunny *> bunnies;
	int m_flag;
	int f_flag;
	void swap_to_back(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag);
public:
	Bunnies();
	Bunnies(int num);
	Bunnies(std::vector<Bunny *> & bunnies);
	void add_bunny(std::vector<Bunny *> &bunnies, Bunny *bunny, int &m_flag, int &f_flag);
	void infection(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag);
	void kill_bunny(std::vector<Bunny *> &bunnies, int index, int &m_flag, int &f_flag);
	void kill_half_bunnies(std::vector<Bunny *> &bunnies, int num, int &m_flag, int &f_flag);
	void kill_old_bunnies(std::vector<Bunny *> &bunnies, int &m_flag, int &f_flag);
}; 
