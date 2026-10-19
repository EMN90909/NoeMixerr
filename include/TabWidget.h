// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TAB_WIDGET_H
#define NoeMixerr_GUI_TAB_WIDGET_H

#include <QWidget>
#include <QMap>

namespace noemixerr::gui
{

const int TEXT_TAB_HEIGHT = 14;
const int GRAPHIC_TAB_HEIGHT = 17;

class TabWidget : public QWidget
{
	Q_OBJECT
public:
	//! @param caption Text describing the tab group as a whole
	//! @param parent The parent widget
	//! @param usePixmap Whether to enable use of pixmap icons in tabs
	//! @param resizable If true, the widget resizes to fit the size of all tabs.
	//! If false, all child widget will be cut down to the TabWidget's size.
	TabWidget(
		const QString& caption,
		QWidget* parent,
		bool usePixmap = false,
		bool resizable = false
	);
	~TabWidget() override = default;

	void addTab(QWidget* w, const QString& name, const char* pixmap = nullptr, int idx = -1);

	void setActiveTab(int idx);

	int findTabAtPos(const QPoint& pos);

	inline int activeTab() const
	{
		return(m_activeTab);
	}

	// Themeability
	Q_PROPERTY(QColor tabText READ tabText WRITE setTabText)
	Q_PROPERTY(QColor tabTitleText READ tabTitleText WRITE setTabTitleText)
	Q_PROPERTY(QColor tabSelected READ tabSelected WRITE setTabSelected)
	Q_PROPERTY(QColor tabTextSelected READ tabTextSelected WRITE setTabTextSelected)
	Q_PROPERTY(QColor tabBackground READ tabBackground WRITE setTabBackground)
	Q_PROPERTY(QColor tabBorder READ tabBorder WRITE setTabBorder)

	QColor tabText() const;
	void setTabText(const QColor & c);
	QColor tabTitleText() const;
	void setTabTitleText(const QColor & c);
	QColor tabSelected() const;
	void setTabSelected(const QColor & c);
	QColor tabTextSelected() const;
	void setTabTextSelected(const QColor & c);
	QColor tabBackground() const;
	void setTabBackground(const QColor & c);
	QColor tabBorder() const;
	void setTabBorder(const QColor & c);

protected:
	bool event(QEvent* event) override;
	void mousePressEvent(QMouseEvent* me) override;
	void paintEvent(QPaintEvent* pe) override;
	void resizeEvent(QResizeEvent* re) override;
	void wheelEvent(QWheelEvent* we) override;
	QSize minimumSizeHint() const override;
	QSize sizeHint() const override;

private:
	struct widgetDesc
	{
		QWidget* w;         // ptr to widget
		const char* pixmap; // artwork for the widget
		QString name;        // name for widget
		int nwidth;          // width of name when painting (only valid for text tab)
	} ;
	using widgetStack = QMap<int, widgetDesc>;

	widgetStack m_widgets;

	bool	m_resizable;
	int 	m_activeTab;
	QString m_caption;      // Tab caption, used as the tooltip text on icon tabs
	quint8 	m_tabbarHeight; // The height of the tab bar
	quint8 	m_tabheight;    // The height of the tabs
	bool	m_usePixmap;      // true if the tabs are to be displayed with icons. False for text tabs.

	QColor m_tabText;       // The color of the tabs' text.
	QColor m_tabTitleText;  // The color of the TabWidget's title text.
	QColor m_tabSelected;   // The highlighting color for the selected tab.
	QColor m_tabTextSelected;// The text color for the selected tab.
	QColor m_tabBackground; // The TabWidget's background color.
	QColor m_tabBorder;     // The TabWidget's borders color.
} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TAB_WIDGET_H
