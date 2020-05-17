#include "turret.h"
#include <string>
#include <sstream>
#include <stdio.h>

Turret::Turret() : location(""), size(""), aura_level(0), parts(0), vision(""){}

Turret::Turret(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision) {
	this->location = location;
	this->size = size;
	this->aura_level = aura_level;
	this->parts = parts;
	this->vision = vision;
}

bool Turret::operator==(const Turret& t)
{
	return (this->location == t.location);
}

std::string Turret::message() {
	return "Location: " + this->get_location() + "  Size: " + this->get_size() + "  Aura level: " + std::to_string(this->get_aura_level()) + "  Parts: " + std::to_string(this->get_parts()) + "  Vision: " + this->get_vision();
}

std::string Turret::text() const {
	std::stringstream t;
	t << this->location << ',' << this->size << ',' << this->aura_level << ',' << this->parts << ',' << this->vision << '\n';
	return t.str();
}

std::vector<std::string> tokenize(const std::string str, char delimiter) {
	std::vector<std::string> s_new;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		s_new.push_back(token);

	return s_new;
}

std::istream& operator>>(std::istream& is, Turret& turret) {
	std::string str;
	getline(is, str);
	std::vector<std::string> tokens = tokenize(str, ',');

	if (tokens.size() != 5) {
		return is;
	}
	Turret t{ tokens[0], tokens[1], stoi(tokens[2]), stoi(tokens[3]), tokens[4] };
	turret = t;
	return is;
}

std::ostream& operator<<(std::ostream& os, Turret& turret) {
	os << turret.text();

	return os;
}


