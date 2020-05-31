#include "file_handle.h"
#include <fstream>
#include "custom_exceptions.h"

using namespace std;

watchman_repo::watchman_repo(string path) {
	this->f_path = path;
}

vector<Turret> watchman_repo::load_file() {
	vector<Turret> turrets_list;
	Turret turr{};
	ifstream fi(this->f_path);
	while (fi >> turr) {
		turrets_list.push_back(turr);
	}
	fi.close();

	return turrets_list;
}

int watchman_repo::get_the_size() {
	return this->turrets.size();
}

void watchman_repo::set_path(string path) {
	this->f_path = path;
}

void watchman_repo::add_to_mylist(Turret turr) {
	for (auto turret : this->turrets)
		if (turret.get_location() == turr.get_location())
			throw repo_exception("Turret already in list !\n");
	this->turrets.push_back(turr);
	save_file(this->turrets);
}

Turret watchman_repo::turret_at_pos(int pos) {
	if (this->turrets.size() <= pos)
		throw repo_exception("Turret not found ! :(\n");

	return this->turrets[pos];
}

Turret watchman_repo::find_turret(string location) {
	for (auto turret : this->turrets)
	{
		if (turret.get_location() == location)
			return turret;
	}
	throw repo_exception("Turret not found ! :(\n");
}

bool watchman_repo::exists(string location) {
	for (auto turr : this->turrets)
		if (turr.get_location() == location)
			return true;
	return false;
}

void watchman_HTML::save_file(const vector<Turret>& t) {
	if (this->f_path.size() == 0)
		throw repo_exception("File path for HTML not set !\n");
	try {
		ofstream of(this->f_path);
		of << "<!DOCTYPE html>" << "\n";
		of << "<html>" << "\n";
		of << "\t" << "<head>" << "\n";
		of << "\t\t" << "<title>" << "Title" << "</title>" << "\n";
		of << "\t" << "</head>" << "\n";
		of << "\t" << "<body>" << "\n";
		of << "\t\t" << "<table border=\"1\">" << "\n";
		of << "\t" << "<tr>" << "\n";
		of << "\t\t" << "<td>" << "Location" << "</td>" << "\n";
		of << "\t\t" << "<td>" << "Size" << "</td>" << "\n";
		of << "\t\t" << "<td>" << "Aura Level" << "</td>" << "\n";
		of << "\t\t" << "<td>" << "Parts" << "</td>" << "\n";
		of << "\t\t" << "<td>" << "Vision" << "</td>" << "\n";
		of << "\t" << "</tr>" << "\n";
		for (auto turret : this->turrets) {
			of << "\t" << "<tr>" << "\n";
			of << "\t\t" << "<td>" << turret.get_location() << "</td>" << "\n";
			of << "\t\t" << "<td>" << turret.get_size() << "</td>" << "\n";
			of << "\t\t" << "<td>" << turret.get_aura_level() << "</td>" << "\n";
			of << "\t\t" << "<td>" << turret.get_parts() << "</td>" << "\n";
			of << "\t\t" << "<td>" << turret.get_vision() << "</td>" << "\n";
			of << "\t" << "</tr>" << "\n";
		}
		of << "\t\t" << "</table>" << "\n";
		of << "\t" << "</body>" << "\n";
		of << "</html>";
		of.close();
	}
	catch (exception&) {
		throw repo_exception("Not a valid path !\n");
	}
}

void watchman_CSV::save_file(const vector<Turret>& t) {
	if (this->f_path.size() == 0)
		throw repo_exception("File path for CSV not set !\n");
	try {
		ofstream of(this->f_path);
		for (auto turret : this->turrets) {
			of << turret;
		}
		of.close();
	}
	catch (exception&) {
		throw repo_exception("Not a valid path !\n");
	}
}

vector<Turret> watchman_repo::get_all() {

	return this->turrets;
}





