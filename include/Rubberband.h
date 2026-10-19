// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_RUBBERBAND_H
#define NoeMixerr_GUI_RUBBERBAND_H

#include <QRubberBand>
#include <QVector>

namespace noemixerr::gui
{


class selectableObject : public QWidget
{
	Q_OBJECT
public:
	selectableObject( QWidget * _parent ) :
		QWidget( _parent ),
		m_selected( false )
	{
	}

	~selectableObject() override = default;

	inline void setSelected(bool selected)
	{
		if (m_selected == selected) { return; }
		m_selected = selected;
		update();
	}

	inline bool isSelected() const
	{
		return( m_selected );
	}


public slots:
	virtual void update()
	{
		QWidget::update();
	}


private:
	bool m_selected;

} ;




class RubberBand : public QRubberBand
{
public:
	RubberBand( QWidget * _parent );
	~RubberBand() override = default;

	QVector<selectableObject *> selectedObjects() const;
	QVector<selectableObject *> selectableObjects() const;


protected:
	void resizeEvent( QResizeEvent * _re ) override;

private:

};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_RUBBERBAND_H
