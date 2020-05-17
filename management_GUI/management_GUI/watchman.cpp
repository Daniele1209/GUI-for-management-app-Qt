#include "watchman.h"
#include <vector>
#include <iostream>
#include <string>
#include "custom_exceptions.h"
using namespace std;

Turret Watchman::next() {
	index++;
	if (index == repo.get_the_size())
		index = 0;
	if (repo.get_the_size() > index)
		return repo.turret_at_pos(index);
}

void Watchman::add_turret_mylist(string elements) {
	Turret turr = repo.find_turret(elements);

	mylist.add_to_mylist(turr);
}

vector<Turret> Watchman::turret_list(string size, int parts) {
	index = 0;
	vector<Turret> turrets = repo.get_turrets();
	vector<Turret> list;
	for (auto turr : turrets) {
		if(turr.get_parts() < parts)
			if (turr.get_size() == size) {
				list[index] = turr;
				index++;
			}
	}
	if (index == 0)
		throw service_exception("No such items were found !\n");
	else {
		return list;
	}
}

vector<Turret> Watchman::get_turret_list() {
	return this->mylist.get_all();
}

