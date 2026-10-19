// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PLUGIN_BROWSER_H
#define NoeMixerr_GUI_PLUGIN_BROWSER_H

#include <QPixmap>

#include "SideBarWidget.h"
#include "Plugin.h"

class QTreeWidget;

namespace noemixerr::gui
{

class PluginBrowser : public SideBarWidget
{
	Q_OBJECT
public:
	PluginBrowser( QWidget * _parent );
	~PluginBrowser() override = default;

private slots:
	void onFilterChanged( const QString & filter );

private:
	void addPlugins();
	void updateRootVisibility( int index );
	void updateRootVisibilities();

	QWidget * m_view;
	QTreeWidget * m_descTree;
};


class PluginDescWidget : public QWidget
{
	Q_OBJECT
public:
	using PluginKey = Plugin::Descriptor::SubPluginFeatures::Key;
	PluginDescWidget( const PluginKey & _pk, QWidget * _parent );
	QString name() const;
	void openInNewInstrumentTrack(QString value);

protected:
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
	void enterEvent(QEnterEvent* event) override;
#else
	void enterEvent(QEvent* event) override;
#endif
	void leaveEvent( QEvent * _e ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void paintEvent( QPaintEvent * _pe ) override;
	void contextMenuEvent(QContextMenuEvent* e) override;

private:
	constexpr static int DEFAULT_HEIGHT{24};

	PluginKey m_pluginKey;
	QPixmap m_logo;

	bool m_mouseOver;
};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_PLUGIN_BROWSER_H
