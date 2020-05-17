#pragma once
#include <vector>
#include <iostream>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

class Turret {
private:
	std::string location;
	std::string size;
	int aura_level;
	int parts;
	std::string vision;

public:
	Turret();

	Turret(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision);

	std::string get_location() const { 
		return location; 
	}
	std::string get_size() const { 
		return size; 
	}
	int get_aura_level() const { 
		return aura_level; 
	}
	int get_parts() const {
		return parts;
	}
	std::string get_vision() const { 
		return vision; 
	}

	bool operator==(const Turret& t);
	friend std::vector<std::string> tokenize(const std::string str, char delimiter);
	friend std::istream& operator>>(std::istream& is, Turret& instance);
	friend std::ostream& operator<<(std::ostream& os, Turret& instance);

	std::string message();
	std::string text() const;
};