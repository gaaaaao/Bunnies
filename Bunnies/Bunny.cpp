#include "pch.h"
#include "Bunny.h"

Bunny::Bunny(int a, COLOR c): m_sex(random(2)), m_color(c), m_age(a), m_name(std::to_string(id++)), m_vampire(!random(50))
{
	if (m_vampire)
		file << "Radioactive Mutant Vampire Bunny " << m_name << " was born!" << '\n';
	else
		file << "Bunny " << m_name << " was born!" << '\n';
}

bool Bunny::sex() { return m_sex; }
int Bunny::color() { return m_color; }
int Bunny::age() { return m_age; }
void Bunny::grown() { m_age++; }
bool Bunny::vampire() { return m_vampire; }
void Bunny::mutate() { m_vampire = true; }
std::string Bunny::name() { return m_name; }

std::string Bunny::p_bunny()
{
	std::string output = "";
	output += std::string("SEX:\t") + (m_sex ? "M\n" : "F\n");
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
	output += "AGE:\t" + std::to_string(m_age) + '\n';
	output += "NAME:\t" + m_name + '\n';
	output += std::string("VAMPIRE:\t") + (m_vampire ? "V\n" : "NV\n");
	return output;
}

Bunny::~Bunny()
{
	if (m_vampire)
		file << "Radioactive Mutant Vampire Bunny " << m_name << " died!" << '\n';
	else
		file << "Bunny " << m_name << " died!" << '\n';
}