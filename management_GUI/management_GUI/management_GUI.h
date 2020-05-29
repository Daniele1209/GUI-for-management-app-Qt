#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_management_GUI.h"
#include "service.h"
#include "watchman.h"
#include <qmessagebox.h>
#include <QInputDialog>
#include <QDir>
#include <qshortcut>
using namespace std;


class management_GUI : public QMainWindow
{
	Q_OBJECT

public:
	management_GUI(Watchman& w, Service& s, QWidget *parent = Q_NULLPTR);

private:
	Service& service;
	Watchman& watchman;
	Ui::management_GUIClass ui;
	QShortcut* undo;
	QShortcut* redo;

	int get_selected() const;

	void connect_signal_slots();
	//functions for admin
	void populate_list();
	void delete_turret();
	void add_turret();
	void update_turret();
	bool validate_input(string location, string size, int aura_level, int parts, string vision);

	void undo_function();
	void redo_function();

	//functions for user
	void next_turret();
	void save_turret();
	void filter_list();
	void populate_mylist();
	int get_selected_user() const;
};
