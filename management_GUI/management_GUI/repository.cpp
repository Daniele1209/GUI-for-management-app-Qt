#include "repository.h"
#include "turret.h"
#include <string>
#include <Windows.h>
#include <fstream>
#include <vector>
#include "custom_exceptions.h"

using namespace std;

void Repository::add_turret(Turret tur) {
	vector<Turret> turrets;
	turrets = get_turrets();
	for (auto turr : turrets) {
		if (turr.get_location() == tur.get_location())
			throw repo_exception("Turret already exists !\n");
	}
	turrets.push_back(tur);
	save_elements(turrets);

}


int Repository::get_the_size() {
	vector<Turret> turrets;
	turrets = load_elements();

	return turrets.size();
}

Turret Repository::find_turret(string location) {
	vector<Turret> turrets;
	turrets = load_elements();
	for (auto turr : turrets)
		if (turr.get_location() == location)
			return turr;
	throw repo_exception("No turret found !\n");
}

void Repository::delete_turret(Turret tur) {
	if (this->file_path == "") {
		throw repo_exception("File location not provided !\n");
	}
	vector<Turret> turrets = get_turrets();
	auto it = find_if(turrets.begin(), turrets.end(), [&tur](auto& turr) {return turr.get_location() == tur.get_location(); });
	if (it == turrets.end()) {
		throw repo_exception("No such turret found !\n");
	}
	turrets.erase(it);
	save_elements(turrets);
}

vector<Turret> Repository::get_turrets() {
	vector<Turret> turrets;
	turrets = load_elements();

	return turrets;
}

//for files

void Repository::path_set(std::string path_of_file) {
	this->file_path = path_of_file;
}

vector<Turret> Repository::load_elements() {
	if (this->file_path == "") {
		throw repo_exception("File location not found ! :/\n");
	}
	vector<Turret> turrets_list;
	Turret turr{};
	ifstream fi(this->file_path);
	while (fi >> turr) {
		turrets_list.push_back(turr);
	}
	fi.close();

	return turrets_list;
}

void Repository::save_elements(vector<Turret> turrets) {
	if (this->file_path == "") {
		throw repo_exception("No path set to save turrets !\n");
	}
	ofstream fo(this->file_path);
	for (auto turret : turrets) {
		fo << turret;
	}
	fo.close();
}

Turret Repository::turret_at_pos(int pos) {
	vector<Turret> elements = load_elements();
	if (elements.size() <= pos) {
		throw repo_exception("No such element !\n");
	}
	return elements[pos];
}