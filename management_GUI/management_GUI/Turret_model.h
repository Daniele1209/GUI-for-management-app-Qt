#pragma once
#include <qabstractitemmodel.h>
#include "file_handle.h"
#include "watchman.h"


class Turret_model : public QAbstractTableModel
{
private:
	watchman_repo& watchman;

public:
	Turret_model(watchman_repo& r) : watchman{ r } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

};

