#include "action.h"

void Add_action::do_action() {
	this->repo.add_turret(this->turret);
}

void Add_action::undo_action() {
	this->repo.delete_turret(this->turret);
}

void Remove_action::do_action() {
	this->repo.delete_turret(this->turret);
	if (saved != nullptr) {
		this->saved->delete_turret(this->turret);
	}
}

void Remove_action::undo_action() {
	this->repo.add_turret(this->turret);
	if (saved != nullptr) {
		this->saved->add_turret(this->turret);
	}
}

void Update_action::do_action() {
	this->repo.update_turret(this->turret2);
	if (this->saved != nullptr)
		this->saved->update_turret(this->turret2);
}

void Update_action::undo_action() {
	this->repo.update_turret(this->turret1);
	if (this->saved != nullptr)
		this->saved->update_turret(this->turret1);
}