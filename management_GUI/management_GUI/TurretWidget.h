#pragma once

#include <QWidget>
#include "ui_TurretWidget.h"
#include "Turret_model.h"

class TurretWidget : public QWidget
{
	Q_OBJECT

public:
	TurretWidget(Turret_model* model, QWidget *parent = Q_NULLPTR);
	~TurretWidget();

private:
	Ui::TurretWidget ui;
	Turret_model* model;
	void updateSize();
};
