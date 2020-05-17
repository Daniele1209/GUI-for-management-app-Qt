#include "GUI.h"
#include <qlayout.h>
#include <qformlayout.h>
#include <qgridlayout.h>
#include <qmessagebox.h>
#include <qcoreapplication>

using namespace std;

GUI::GUI(Service& s, Watchman& w) : service{ s }, watchman{ w } {
	this->init_GUI();
	this->populate_list();
	this->connect_signals();
}

void GUI::init_GUI() {
	this->location_line = new QLineEdit{};
	this->size_line = new QLineEdit{};
	this->aura_level_line = new QLineEdit{};
	this->parts_line = new QLineEdit{};
	this->vision_line = new QLineEdit{};
	this->list_turrets_widget = new QListWidget{};
	this->add_turret_button = new QPushButton{"Add"};
	this->delete_button = new QPushButton{"Delete"};
	this->update_button = new QPushButton{ "Update" };
	this->exit_button = new QPushButton{ "Exit" };

	QVBoxLayout* main_layout = new QVBoxLayout{ this };
	main_layout->addWidget(this->list_turrets_widget);
	QFormLayout* turret_details_layout = new QFormLayout{};

	turret_details_layout->addRow("Location", this->location_line);
	turret_details_layout->addRow("Size", this->size_line);
	turret_details_layout->addRow("Aura Level", this->aura_level_line);
	turret_details_layout->addRow("Parts", this->parts_line);
	turret_details_layout->addRow("Vision", this->vision_line);

	main_layout->addLayout(turret_details_layout);

	QGridLayout* buttons_layout = new QGridLayout{};
	buttons_layout->addWidget(this->add_turret_button, 0, 0);
	buttons_layout->addWidget(this->delete_button, 0, 1);
	buttons_layout->addWidget(this->update_button, 0, 2);
	buttons_layout->addWidget(this->exit_button, 0, 3);
	main_layout->addLayout(buttons_layout);
}

void GUI::populate_list() {
	this->list_turrets_widget->clear();
	vector<Turret> turrets = this->service.get_turret();
	for (auto turr : turrets)
		this->list_turrets_widget->addItem(QString::fromStdString(turr.get_location()));
}

void GUI::connect_signals() {
	QObject::connect(this->list_turrets_widget, &QListWidget::itemSelectionChanged, [this]() {
		int selected_index = this->get_selected();
		if (selected_index < 0)
			return;
		Turret turr = this->service.get_turret()[selected_index];
		this->location_line->setText(QString::fromStdString(turr.get_location()));
		this->size_line->setText(QString::fromStdString(turr.get_size()));
		this->aura_level_line->setText(QString::fromStdString(to_string(turr.get_aura_level())));
		this->parts_line->setText(QString::fromStdString(to_string(turr.get_parts())));
		this->vision_line->setText(QString::fromStdString(turr.get_vision()));

	});

	QObject::connect(this->add_turret_button, &QPushButton::clicked, this, &GUI::add_turret);
	QObject::connect(this->delete_button, &QPushButton::clicked, this, &GUI::delete_turret);
	QObject::connect(this->update_button, &QPushButton::clicked, this, &GUI::update_turret);
	QObject::connect(this->exit_button, SIGNAL(clicked()), qApp, SLOT(quit()));
}

int GUI::get_selected() const {
	QModelIndexList selected_indexes = this->list_turrets_widget->selectionModel()->selectedIndexes();
	if (selected_indexes.size() == 0) {
		this->location_line->clear();
		this->size_line->clear();
		this->aura_level_line->clear();
		this->parts_line->clear();
		this->vision_line->clear();
		return -1;
		//means nothing is selected
	}
	int selected_index = selected_indexes.at(0).row();

	return selected_index;
}

void GUI::add_turret() {
	string location = this->location_line->text().toStdString();
	string size = this->size_line->text().toStdString();
	int aura_level = this->aura_level_line->text().toInt();
	int parts = this->parts_line->text().toInt();
	string vision = this->vision_line->text().toStdString();
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
	this->list_turrets_widget->setCurrentRow(last_elem);
}

void GUI::delete_turret() {
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

void GUI::update_turret() {
	int selected = this->get_selected();
	if (selected < 0) {
		QMessageBox::critical(this, "Error", "No Turret selected !");
		return;
	}
	string location = this->location_line->text().toStdString();
	string size = this->size_line->text().toStdString();
	int aura_level = this->aura_level_line->text().toInt();
	int parts = this->parts_line->text().toInt();
	string vision = this->vision_line->text().toStdString();
	//validate the input data 
	if (!this->validate_input(location, size, aura_level, parts, vision))
		return;

	this->service.update_list(location, size, aura_level, parts, vision);
	//update the gui list
	this->populate_list();
	int last_elem = this->service.get_turret().size() - 1;
	this->list_turrets_widget->setCurrentRow(last_elem);

}

bool GUI::validate_input(string location, string size, int aura_level, int parts, string vision) {

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