// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// Copyright (c) 2023 Lost Robot <r94231/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_EFFECT_SELECT_DIALOG_H
#define NoeMixerr_GUI_EFFECT_SELECT_DIALOG_H

#include "Effect.h"

#include <QDialog>
#include <QRegularExpression>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>

class QScrollArea;
class QTableView;
class QLineEdit;

namespace noemixerr::gui
{

class DualColumnFilterProxyModel : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	DualColumnFilterProxyModel(QObject* parent = nullptr) : QSortFilterProxyModel(parent)
	{
	}

	void setEffectTypeFilter(const QString& filter)
	{
		m_effectTypeFilter = filter;
		invalidateFilter();
	}

protected:
	bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override
	{
		QModelIndex nameIndex = sourceModel()->index(source_row, 0, source_parent);
		QModelIndex typeIndex = sourceModel()->index(source_row, 1, source_parent);

		QString name = sourceModel()->data(nameIndex, Qt::DisplayRole).toString();
		QString type = sourceModel()->data(typeIndex, Qt::DisplayRole).toString();

		QRegularExpression nameRegularExpression(filterRegularExpression());
		nameRegularExpression.setPatternOptions(QRegularExpression::CaseInsensitiveOption);
		
		bool nameFilterPassed = nameRegularExpression.match(name).capturedStart() != -1;

		bool typeFilterPassed = type.contains(m_effectTypeFilter, Qt::CaseInsensitive);

		return nameFilterPassed && typeFilterPassed;
	}

private:
	QString m_effectTypeFilter;
};


class EffectSelectDialog : public QDialog
{
	Q_OBJECT
public:
	EffectSelectDialog(QWidget* parent);

	Effect* instantiateSelectedPlugin(EffectChain* parent);

protected slots:
	void acceptSelection();
	void rowChanged(const QModelIndex&, const QModelIndex&);
	void updateSelection();
	
	bool eventFilter(QObject* obj, QEvent* event) override;

private:
	EffectKeyList m_effectKeys;
	EffectKey m_currentSelection;

	QStandardItemModel m_sourceModel;
	DualColumnFilterProxyModel m_model;
	QWidget* m_descriptionWidget;
	QTableView* m_pluginList;
	QScrollArea* m_scrollArea;
	QLineEdit* m_filterEdit;
};

} // namespace noemixerr::gui

#endif
