#include "watchman.h"
#include <vector>
#include <iostream>
#include <string>
#include "custom_exceptions.h"
using namespace std;

Turret Watchman::next() {
	this->index++;
	if (this->index == this->repo.get_the_size())
		this->index = 0;
	if (this->repo.get_the_size() > this->index)
		return this->repo.turret_at_pos(this->index);
}

void Watchman::add_turret_mylist(string elements) {
	Turret turr = this->repo.find_turret(elements);

	this->mylist.add_to_mylist(turr);
}

Turret Watchman::find_from_list(string location) {
	Turret turr = this->repo.find_turret(location);

	return turr;
}

bool Watchman::check(string location) {
	if (this->mylist.exists(location))
		return true;
	return false;
}

vector<Turret> Watchman::turret_list(string size, int parts) {
	bool ok = true;
	vector<Turret> turrets = this->repo.get_turrets();
	vector<Turret> list;
	for (Turret turr : turrets) {
		if(turr.get_parts() < parts)
			if (turr.get_size() == size) {
				list.push_back(turr);
				ok = false;
			}
	}
	if (ok)
		throw service_exception("No such items were found !\n");
	return list;
}

vector<Turret> Watchman::get_turret_list() {
	return this->mylist.get_all();
}

vector<Turret> Watchman::get_loaded() {
	vector<Turret> turr = this->mylist.load_file();
	return turr;
}