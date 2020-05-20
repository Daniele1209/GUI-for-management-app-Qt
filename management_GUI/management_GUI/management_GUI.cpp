#include "management_GUI.h"

using namespace std;

management_GUI::management_GUI(Service& s, QWidget* parent)
	: QMainWindow(parent), service{ s }
{
	ui.setupUi(this);
	this->populate_list();
	this->connect_signal_slots();
}

void management_GUI::populate_list() {
	this->ui.turret_list_widget->clear();
	vector<Turret> turrets = this->service.get_turret();
	for (auto turr : turrets)
		this->ui.turret_list_widget->addItem(QString::fromStdString(turr.get_location()));
}

void management_GUI::connect_signal_slots() {
	QObject::connect(this->ui.add_button, &QPushButton::clicked, this, &management_GUI::add_turret);
	QObject::connect(this->ui.delete_button, &QPushButton::clicked, this, &management_GUI::delete_turret);
	QObject::connect(this->ui.update_button, &QPushButton::clicked, this, &management_GUI::update_turret);
	QObject::connect(this->ui.exit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void management_GUI::delete_turret() {
	int selected = this->get_selected();
	if (selected < 0) {
		QMessageBox::critical(this, "Error", "No Turret selected !");
		return;
	}

	Turret turr = this->service.get_turret()[selected];
	this->service.delete_turret_list(turr.get_location());
	//update the gui list
	this->populate_list();
}

int management_GUI::get_selected() const {
	QModelIndexList selected_indexes = this->ui.turret_list_widget->selectionModel()->selectedIndexes();
	if (selected_indexes.size() == 0) {
		this->ui.location_line->clear();
		this->ui.size_line->clear();
		this->ui.aura_level_line->clear();
		this->ui.parts_line->clear();
		this->ui.vision_line->clear();
		return -1;
		//means nothing is selected
	}
	int selected_index = selected_indexes.at(0).row();

	return selected_index;
}

void management_GUI::add_turret() {
	string location = this->ui.location_line->text().toStdString();
	string size = this->ui.size_line->text().toStdString();
	int aura_level = this->ui.aura_level_line->text().toInt();
	int parts = this->ui.parts_line->text().toInt();
	string vision = this->ui.vision_line->text().toStdString();
	//validate the input data 
	if (!this->validate_input(location, size, aura_level, parts, vision))
		return;
	//check if turret already exists
	for (auto turr : this->service.get_turret()) {
		if (turr.get_location() == location) {
			QMessageBox::critical(this, "Error", "Turret already exists !");
			return;
		}
	}

	this->service.add_turret_repo(location, size, aura_level, parts, vision);
	//syncronise the repo with the gui list that is displayed
	this->populate_list();
	int last_elem = this->service.get_turret().size() - 1;
	this->ui.turret_list_widget->setCurrentRow(last_elem);
}

void management_GUI::update_turret() {
	int selected = this->get_selected();
	if (selected < 0) {
		QMessageBox::critical(this, "Error", "No Turret selected !");
		return;
	}
	string location = this->ui.location_line->text().toStdString();
	string size = this->ui.size_line->text().toStdString();
	int aura_level = this->ui.aura_level_line->text().toInt();
	int parts = this->ui.parts_line->text().toInt();
	string vision = this->ui.vision_line->text().toStdString();
	//validate the input data 
	if (!this->validate_input(location, size, aura_level, parts, vision))
		return;

	this->service.update_list(location, size, aura_level, parts, vision);
	//update the gui list
	this->populate_list();
	int last_elem = this->service.get_turret().size() - 1;
	this->ui.turret_list_widget->setCurrentRow(last_elem);

}

bool management_GUI::validate_input(string location, string size, int aura_level, int parts, string vision) {

	if (location.empty()) {
		QMessageBox::critical(this, "Error", "Empty location !");
		return false;
	}
	if (size.empty()) {
		QMessageBox::critical(this, "Error", "Empty size !");
		return false;
	}
	if (aura_level == 0) {
		QMessageBox::critical(this, "Error", "Empty aura level !");
		return false;
	}
	if (parts == 0) {
		QMessageBox::critical(this, "Error", "Empty parts !");
		return false;
	}
	if (vision.empty()) {
		QMessageBox::critical(this, "Error", "Empty vision !");
		return false;
	}
	return true;
}