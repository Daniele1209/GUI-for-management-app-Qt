#include "TurretWidget.h"


TurretWidget::TurretWidget(Turret_model* model, QWidget *parent) 
	: QWidget(parent), model{ model }
{
	ui.setupUi(this);
	ui.turret_table_view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.turret_table_view->setModel(this->model);
}

TurretWidget::~TurretWidget()
{
}

void TurretWidget::updateSize() {
	this->ui.turret_table_view->resizeRowsToContents();
}