#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_management_GUI.h"
#include "service.h"
#include <qmessagebox.h>
using namespace std;


class management_GUI : public QMainWindow
{
	Q_OBJECT

public:
	management_GUI(Service& s, QWidget *parent = Q_NULLPTR);

private:
	Service& service;
	Ui::management_GUIClass ui;

	int get_selected() const;

	void connect_signal_slots();

	void populate_list();
	void delete_turret();
	void add_turret();
	void update_turret();
	bool validate_input(string location, string size, int aura_level, int parts, string vision);
};
