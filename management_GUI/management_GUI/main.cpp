#include "watchman.h"
#include <memory>
#include <QtWidgets/QApplication>
#include "service.h"
#include "management_GUI.h"

using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	watchman_CSV repo2{"Mylist.csv"};
	Repository repo{};
	Repository* saved{};
	Watchman watch{ repo, repo2 };
	Service service{ repo , saved };

	management_GUI gui{ watch, service };
	gui.show();

	return a.exec();

}