#include "file_handle.h"
#include <fstream>
#include "custom_exceptions.h"

using namespace std;

watchman_repo::watchman_repo(string path) {
	f_path = path;
}

int watchman_repo::get_the_size() {
	return turrets.size();
}

void watchman_repo::set_path(string path) {
	f_path = path;
}

void watchman_repo::add_to_mylist(Turret turr) {
	for (auto turret : turrets)
		if (turret.get_location() == turr.get_location())
			throw repo_exception("Turret already in list !\n");
	turrets.push_back(turr);
	save_file(turrets);
}

Turret watchman_repo::turret_at_pos(int pos) {
	if (turrets.size() <= pos)
		throw repo_exception("Turret not found ! :(\n");

	return turrets[pos];
}

Turret watchman_repo::find_turret(string location) {
	for (auto turret : turrets)
	{
		if (turret.get_location() == location)
			return turret;
	}
	throw repo_exception("Turret not found ! :(\n");
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
	if (f_path.size() == 0)
		throw repo_exception("File path for CSV not set !\n");
	try {
		ofstream of(f_path);
		for (auto turret : turrets)
			of << turret;
		of.close();
	}
	catch (exception&) {
		throw repo_exception("Not a valid path !\n");
	}
}

vector<Turret> watchman_repo::get_all() {
	return turrets;
}


