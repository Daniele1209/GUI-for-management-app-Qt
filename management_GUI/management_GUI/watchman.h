#pragma once
#include "repository.h"
#include "turret.h"
#include "file_handle.h"

class Watchman {
private:
	Repository& repo;
	watchman_repo& mylist;
	int index = 0;

public:

	Watchman(Repository& r, watchman_repo& l): repo{ r }, mylist{ l } {}

	Turret next();
	std::vector<Turret> turret_list(std::string size, int parts);
	void add_turret_mylist(std::string elements);
	std::vector<Turret> get_turret_list();
};