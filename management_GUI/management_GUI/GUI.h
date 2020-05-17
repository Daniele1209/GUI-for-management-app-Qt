#pragma once
#include "service.h"
#include "watchman.h"
#include <qwidget.h>
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI : public QWidget {
private:
	Service& service;
	Watchman& watchman;
	QLineEdit* location_line, * size_line, * aura_level_line, * parts_line, * vision_line;
	QListWidget* list_turrets_widget;
	QPushButton* add_turret_button, * delete_button, * update_button, * exit_button;

public:
	GUI(Service& s, Watchman& w);

private:
	void init_GUI();
	void populate_list();
	void connect_signals();
	int get_selected() const;

	void add_turret();
	void delete_turret();
	void update_turret();

	bool validate_input(string location, string size, int aura_level, int parts, string vision);
};