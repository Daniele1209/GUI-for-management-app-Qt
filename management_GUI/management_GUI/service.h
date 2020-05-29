#pragma once
#include "repository.h";
#include <vector>
#include "action.h"
#include <iostream>
#include "custom_exceptions.h"

class Service {
private:
	Repository& repo;
	vector<unique_ptr<Action>> undo_stack;
	vector<unique_ptr<Action>> redo_stack;

public:
	Service(Repository& r) :repo{ r } {}
	Repository& get_repo() const {
		return repo;
	}
	void new_path(std::string path);
	void add_turret_repo(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision);
	std::vector<Turret> get_turret();
	int get_repo_size();
	Repository* saved;
	void delete_turret_list(std::string command);
	void update_list(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision);
	Turret turret_at_index(int index);

	void undo();
	void redo();
};