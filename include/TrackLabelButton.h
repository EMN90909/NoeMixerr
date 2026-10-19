// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2004-2008 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_TRACK_LABEL_BUTTON_H
#define NoeMixerr_GUI_TRACK_LABEL_BUTTON_H

#include <string>

#include <QToolButton>

namespace noemixerr::gui
{

class TrackView;

class TrackRenameLineEdit;


class TrackLabelButton : public QToolButton
{
	Q_OBJECT
public:
	TrackLabelButton( TrackView * _tv, QWidget * _parent );
	~TrackLabelButton() override = default;


public slots:
	void rename();
	void renameFinished();
	void nameChanged();


protected:
	void dragEnterEvent( QDragEnterEvent * _dee ) override;
	void dropEvent( QDropEvent * _de ) override;
	void mousePressEvent( QMouseEvent * _me ) override;
	void mouseDoubleClickEvent( QMouseEvent * _me ) override;
	void mouseReleaseEvent( QMouseEvent * _me ) override;
	void paintEvent(QPaintEvent* pe) override;
	void resizeEvent( QResizeEvent * _re ) override;

private:
	bool isInCompactMode() const;

private:
	TrackView * m_trackView;
	std::string m_iconName;
	TrackRenameLineEdit * m_renameLineEdit;
	QRect m_buttonRect;
	QString elideName( const QString &name );

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_TRACK_LABEL_BUTTON_H
