#pragma once
#include <string>

enum COLOR
{
	WHITE,
	BROWN,
	BLACK,
	SPOTTED
};

class Bunny
{
private:
	bool m_sex;
	COLOR m_color;
	int m_age;
	std::string m_name;
	bool m_vampire;
public:
	Bunny(int a, COLOR c);
	bool sex();
	int color();
	int age();
	void grown();
	bool vampire();
	void mutate();
	std::string name();
	std::string p_bunny();
	~Bunny();
};