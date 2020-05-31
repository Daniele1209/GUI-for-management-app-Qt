#include "Turret_model.h"

int Turret_model::rowCount(const QModelIndex& parent) const {
	vector<Turret> turr = this->watchman.load_file();
	return turr.size();
}

int Turret_model::columnCount(const QModelIndex& parent) const {

	return 5;
}

QVariant Turret_model::data(const QModelIndex& index, int role) const {
	int row = index.row();
	int col = index.column();
	vector<Turret> turr = this->watchman.load_file();
	Turret curr_turr = turr[row];
	if (role == Qt::DisplayRole) {
		switch (col) {
		case 0:
			return QString::fromStdString(curr_turr.get_location());
		case 1:
			return QString::fromStdString(curr_turr.get_size());
		case 2:
			return QString::number(curr_turr.get_aura_level());
		case 3:
			return QString::number(curr_turr.get_parts());
		case 4:
			return QString::fromStdString(curr_turr.get_vision());
		default:
			break;
		}
	}

	return QVariant();
}

QVariant Turret_model::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("Location");
			case 1:
				return QString("Size");
			case 2:
				return QString("Aura Level");
			case 3:
				return QString("Parts");
			case 4:
				return QString("Vision");
			default:
				break;
			}
		}
	}

	return QVariant();
}
