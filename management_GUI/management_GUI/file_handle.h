#pragma once
#include <string>
#include <vector>
#include "turret.h"
#include <iostream>

using namespace std;

class watchman_repo
{
protected:
	vector<Turret> turrets;
	string f_path;

public:
	watchman_repo() { f_path = ""; };
	watchman_repo(string path);

	int get_the_size();
	void set_path(string path);
	void add_to_mylist(Turret turr);
	virtual void save_file(const vector<Turret>&) = 0;

	Turret turret_at_pos(int pos);
	Turret find_turret(string location);

	vector<Turret> get_all();
};

class watchman_HTML : public watchman_repo
{
public:
	watchman_HTML() {
		f_path = "";
	};
	watchman_HTML(string path) { f_path = path; };
	void save_file(const vector<Turret>& t) override;
};

class watchman_CSV : public watchman_repo
{
public:
	watchman_CSV() { 
		f_path = ""; 
	};
	watchman_CSV(string path) { f_path = path; };
	void save_file(const vector<Turret>& t) override;
};