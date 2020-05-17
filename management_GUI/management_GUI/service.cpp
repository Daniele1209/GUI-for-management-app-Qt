#include "service.h"
#include <iostream>
#include "custom_exceptions.h"

void Service::add_turret_repo(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision) {
	Turret tur{ location, size, aura_level,parts, vision };
		this->repo.add_turret(tur);
}

void Service::new_path(std::string set_path) {
	this->repo.path_set(set_path);
}

void Service::delete_turret_list(std::string command) {
	Turret remove{ command, "", 0, 0, "" };
	this->repo.delete_turret(remove);
}

std::vector<Turret> Service::get_turret() {
	return this->repo.get_turrets();
}

int Service::get_repo_size() {
	return this->repo.get_the_size();
}

void Service::update_list(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision) {
	Turret tur = Turret(location, size, aura_level,parts, vision);
	this->repo.delete_turret(tur);
	this->repo.add_turret(tur);

}
