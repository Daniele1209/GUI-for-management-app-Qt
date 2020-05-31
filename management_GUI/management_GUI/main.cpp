#include "watchman.h"
#include <memory>
#include <QtWidgets/QApplication>
#include "service.h"
#include "management_GUI.h"
#include "Turret_model.h"
#include "TurretWidget.h"
#include "qicon.h"

using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	watchman_CSV repo2{"Mylist.csv"};
	Repository repo{};
	Watchman watch{ repo, repo2 };
	Service service{ repo };
	management_GUI gui{ watch, service };
	Turret_model* model = new Turret_model{ repo2 };

	TurretWidget turr{ model };
	gui.setWindowTitle("Turret management application");
	turr.setWindowTitle("User Turret List");
	QIcon icon1("app.ico");
	QIcon icon2("Towers_icon.ico");
	gui.setWindowIcon(icon1);
	turr.setWindowIcon(icon2);
	turr.show();
	gui.show();

	return a.exec();

}