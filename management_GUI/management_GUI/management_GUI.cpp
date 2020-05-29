#include "management_GUI.h"

using namespace std;

management_GUI::management_GUI(Watchman& w, Service& s, QWidget* parent)
	: QMainWindow(parent), service{ s }, watchman{ w }
{
	ui.setupUi(this);
	//admin
	this->populate_list();
	this->connect_signal_slots();

	//user
	this->populate_mylist();
	//initialize sortcuts for fct undo and redo
	this->undo = new QShortcut(QKeySequence(QKeySequence::Undo), this);
	this->redo = new QShortcut(QKeySequence(QKeySequence::Redo), this);
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
	QObject::connect(this->ui.turret_list_widget, &QListWidget::itemSelectionChanged, [this]() {
		int selected_index = this->get_selected();
		if (selected_index < 0)
			return;
		Turret turr = this->service.get_turret()[selected_index];
		this->ui.location_line->setText(QString::fromStdString(turr.get_location()));
		this->ui.size_line->setText(QString::fromStdString(turr.get_size()));
		this->ui.aura_level_line->setText(QString::fromStdString(to_string(turr.get_aura_level())));
		this->ui.parts_line->setText(QString::fromStdString(to_string(turr.get_parts())));
		this->ui.vision_line->setText(QString::fromStdString(turr.get_vision()));

		});
	QObject::connect(this->ui.save_button, &QPushButton::clicked, this, &management_GUI::save_turret);
	QObject::connect(this->ui.next_button, &QPushButton::clicked, this, &management_GUI::next_turret);
	QObject::connect(this->ui.filter_button, &QPushButton::clicked, this, &management_GUI::filter_list);
	QObject::connect(this->ui.undo_button, &QPushButton::clicked, this, &management_GUI::undo_function);
	QObject::connect(this->ui.redo_button, &QPushButton::clicked, this, &management_GUI::redo_function);
	QObject::connect(this->undo, &QShortcut::activated, this, &management_GUI::undo_function);
	QObject::connect(this->redo, &QShortcut::activated, this, &management_GUI::redo_function);

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


//functions for user mode

void management_GUI::populate_mylist() {
	this->ui.mylist_list->clear();
	vector<Turret> turrets = this->watchman.get_turret_list();
	for (auto turr : turrets)
		this->ui.mylist_list->addItem(QString::fromStdString(turr.get_location()));
}

void management_GUI::next_turret() {
	Turret curr_turret = this->watchman.next();
	this->ui.location_line_u->setText(QString::fromStdString(curr_turret.get_location()));
	this->ui.size_line_u->setText(QString::fromStdString(curr_turret.get_size()));
	this->ui.aura_level_line_u->setText(QString::fromStdString(to_string(curr_turret.get_aura_level())));
	this->ui.parts_line_u->setText(QString::fromStdString(to_string(curr_turret.get_parts())));
	this->ui.vision_line_u->setText(QString::fromStdString(curr_turret.get_vision()));

}

void management_GUI::save_turret() {
	string location = this->ui.location_line_u->text().toStdString();
	if (location.empty()) {
		QMessageBox::critical(this, "Error", "Turret is missing !");
		return;
	}
	
	if (this->watchman.check(location) == true) {
		QMessageBox::critical(this, "Error", "Turret already in list !");
		return;
	}

	this->watchman.add_turret_mylist(location);
	//syncronise the repo with the gui list that is displayed
	this->populate_mylist();
	int last_elem = this->watchman.get_turret_list().size() - 1;
	this->ui.turret_list_widget->setCurrentRow(last_elem);
}

void management_GUI::filter_list() {
	bool ok;
	QString s = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("Size:"), QLineEdit::Normal,
		QDir::home().dirName(), &ok);

	QString p = QInputDialog::getText(this, tr("QInputDialog::getText()"),
		tr("Parts:"), QLineEdit::Normal,
		QDir::home().dirName(), &ok);

	int parts = p.toInt();
	string size = s.toStdString();

	try {
		vector<Turret> t_list = this->watchman.turret_list(size, parts);
		this->ui.filter_list->clear();
		for (auto turr : t_list)
			this->ui.filter_list->addItem(QString::fromStdString(turr.get_location()));
	}
	catch (exception&) {
		QMessageBox::critical(this, "Error", "No such turrets exist !");
		return;
	}
}

void management_GUI::undo_function() {
	try {
		this->service.undo();
	}
	catch (exception & e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	this->populate_list();
}

void management_GUI::redo_function() {
	try {
		this->service.redo();
	}
	catch (exception & e) {
		QMessageBox::critical(this, "Error", e.what());
	}
	this->populate_list();
}