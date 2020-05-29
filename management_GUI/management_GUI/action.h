#pragma once
#include "turret.h"
#include "repository.h"
#include <cstddef>

class Action {
public:
	virtual void undo_action() = 0;
	virtual void do_action() = 0;
	virtual ~Action() {}
};

class Add_action : public Action {
private:
	Repository& repo;
	Turret turret;

public:
	Add_action(Repository& repo, Turret turret) : repo{ repo }, turret{ turret } {}
	Add_action(const Add_action& second) : repo{ second.repo }, turret{ second.turret } {}
	void do_action() override;
	void undo_action() override;
	~Add_action() {}
};

class Remove_action : public Action {
private:
	Repository& repo;
	Repository* saved;
	Turret turret;

public:
	Remove_action(Repository& repo, Turret turret, Repository* saved = nullptr) : repo{ repo }, saved{ saved }, turret{ turret } {}
	Remove_action(const Remove_action& second) : repo{ second.repo }, saved{ second.saved }, turret{ second.turret } {}
	void do_action() override;
	void undo_action() override;
	~Remove_action() {}
};

class Update_action : public Action {
private:
	Repository& repo;
	Repository* saved;
	Turret turret1;
	Turret turret2;

public:
	Update_action(Repository& repo, Turret turret1, Turret turret2, Repository* saved = nullptr) : repo{ repo }, saved{ saved }, turret1{ turret1 }, turret2{ turret2 } {}
	Update_action(const Update_action& second) : repo{ second.repo }, saved{ second.saved }, turret1{ turret1 }, turret2{ turret2 } {}
	void do_action() override;
	void undo_action() override;
	~Update_action() {}
};