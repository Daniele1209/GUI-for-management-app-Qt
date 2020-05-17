#include "watchman.h"
#include <memory>
#include "GUI.h"
#include <QtWidgets/QApplication>
using namespace std;

int main(int argc, char *argv[]) {

	QApplication a(argc, argv);

	watchman_CSV repo2{"Mylist.csv"};
	Repository repo{};
	Watchman watch{ repo, repo2 };
	Service service{ repo };
	GUI gui{ service , watch };
	gui.show();

	return a.exec();

}