#pragma once
#include "repository.h";
#include <vector>

class Service {
private:
	Repository& repo;

public:
	Service(Repository& r) :repo{ r } {}
	Repository& get_repo() const {
		return repo;
	}
	void new_path(std::string path);
	void add_turret_repo(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision);
	std::vector<Turret> get_turret();
	int get_repo_size();
	void delete_turret_list(std::string command);
	void update_list(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision);
};