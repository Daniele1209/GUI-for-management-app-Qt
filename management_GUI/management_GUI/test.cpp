#include "test.h"
#include "custom_exceptions.h"

void run_service_tests() {
	Repository repo{};
	Service service{ repo };
	service.new_path("file.txt");
	service.add_turret_repo("loc1", "size", 100, 400, "loc");
	assert(service.get_repo_size() == 10);
	service.update_list("loc1", "mid", 0, 0, "tower");
	service.delete_turret_list("loc1");
	assert(service.get_repo_size() == 9);
	std::cout << "service tests passes !\n";
}

void run_repo_services() {
	Repository repo{};
	Service service{ repo };
	Turret tur{ "south", "medium", 230, 2700, "tower" };
	Turret tur2{ "loc1", "zise", 400, 4000, "loc" };
	try {
		repo.add_turret(tur);
		assert(false);
	}
	catch (exception& ex) {
		assert(true);
	}
	repo.add_turret(tur2);
	assert(repo.get_the_size() == 10);
	Turret tur3 = repo.get_turrets()[9];
	assert(tur2 == tur3);
	repo.delete_turret(tur2);
	assert(repo.get_the_size() == 9);
	std::cout << "repo tests passes !\n";
}

void run_turret_test() {
	Turret tur{ "south", "medium", 230, 2700, "tower" };
	assert(tur.get_location() == "south");
	assert(tur.get_size() == "medium");
	assert(tur.get_aura_level() == 230);
	assert(tur.get_parts() == 2700);
	assert(tur.get_vision() == "tower");
	Turret tur2{ "east", "huge", 400, 4000, "tower" };
	assert((tur == tur2) == false);
	Turret tur3{ "east", "huge", 400, 4000, "tower" };
	assert((tur2 == tur3) == true);
	std::cout << "turret tests passes !\n";

}

void run_watchman_test() {
	Repository repo{};
	watchman_CSV list{ "Mylist.csv" };
	Watchman watchman{ repo, list };
	Service service{ repo };
	Turret tur{ "east", "hudge", 400, 4000, "tower" };
	Turret tur2{ "south-west", "medium", 250, 400, "residential area" };
	Turret tur3 = watchman.next();
	assert(tur2 == tur3);
	watchman.add_turret_mylist("east");
	vector<Turret> turr = watchman.get_turret_list();
	assert(tur == turr[0]);
	std::cout << "watchman tests passes !\n\n";
}

void run_all_tests() {
	run_service_tests();
	run_repo_services();
	run_turret_test();
	run_watchman_test();
}