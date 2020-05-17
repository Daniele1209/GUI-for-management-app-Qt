#pragma once
#include "turret.h"
#include <vector>
#define _CRT_SECURE_NO_WARNINGS

class Repository {
private:
	std::string file_path;

public:
	//initialise the repo
	Repository() : file_path{ "file.txt" } {}
	//fct for files
	std::vector<Turret> load_elements();
	void save_elements(std::vector<Turret> turrets);
	Turret turret_at_pos(int pos);
	void path_set(std::string path_of_file);

	int get_the_size();
	void add_turret(Turret tur);
	std::vector<Turret> get_turrets();
	Turret find_turret(std::string location);
	void delete_turret(Turret tur);
};