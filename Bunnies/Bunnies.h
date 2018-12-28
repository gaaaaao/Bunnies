#pragma once
#include <vector>
#include <string>
#include "Bunny.h"

class Bunnies
{
private:
	int id;
	std::vector<Bunny *> bunnies;
	int m_flag;
	int f_flag;
	void swap_to_back(int index);
public:
	Bunnies();
	Bunnies(int num);
	Bunnies(std::vector<Bunny *> & bunnies);
	~Bunnies();
	void add_bunny(Bunny *bunny);
	void infection();
	void kill_bunny(int index);
	void kill_bunnies(int num);
	void kill_all_bunnies();
	void kill_old_bunnies();
	void bunnies_info();
	bool empty();
	int count();
	void reproduction();
	void grow();
};
