#include "service.h"


void Service::add_turret_repo(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision) {
	Turret tur{ location, size, aura_level,parts, vision };
		this->repo.add_turret(tur);
		//undo and redo fct for add
		this->undo_stack.push_back(make_unique<Add_action>(this->repo, tur));
		this->redo_stack.clear();
}

void Service::new_path(std::string set_path) {
	this->repo.path_set(set_path);
}

void Service::delete_turret_list(std::string command) {
	Turret remove{ command, "", 0, 0, "" };
	this->repo.delete_turret(remove);

	this->undo_stack.push_back(make_unique<Remove_action>(this->repo, remove));
	this->redo_stack.clear();
}

vector<Turret> Service::get_turret() {
	return this->repo.get_turrets();
}

Turret Service::turret_at_index(int index) {
	return this->repo.turret_at_pos(index);
}

int Service::get_repo_size() {
	return this->repo.get_the_size();
}

void Service::update_list(const std::string& location, const std::string& size, const int aura_level, const int parts, const std::string& vision) {
	Turret tur = Turret(location, size, aura_level,parts, vision);
	Turret turret1 = this->repo.find_turret(location);
	this->repo.delete_turret(tur);
	this->repo.add_turret(tur);

	this->undo_stack.push_back(make_unique<Update_action>(this->repo, turret1, tur));
	this->redo_stack.clear();
}

void Service::undo() {
	if (this->undo_stack.empty())
		throw exception("Can not undo !");
	auto action = move(this->undo_stack.back());
	action->undo_action();
	
	this->redo_stack.push_back(move(action));
}

void Service::redo() {
	if (this->redo_stack.empty())
		throw exception("Can not redo !");
	auto action = move(this->redo_stack.back());
	this->redo_stack.pop_back();
	action->do_action();

	this->undo_stack.push_back(move(action));
}