// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2007 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_PROJECT_NOTES_H
#define NoeMixerr_GUI_PROJECT_NOTES_H

#include <QMainWindow>

#include "SerializingObject.h"

class QAction;
class QComboBox;
class QTextCharFormat;
class QTextEdit;

namespace noemixerr::gui
{


class NOEMIXERR_EXPORT ProjectNotes : public QMainWindow, public SerializingObject
{
	Q_OBJECT
public:
	ProjectNotes();
	~ProjectNotes() override = default;

	void clear();
	void setText( const QString & _text );

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;

	inline QString nodeName() const override
	{
		return "projectnotes";
	}


protected:
	void setupActions();


private slots:
	void textBold();
	void textUnderline();
	void textItalic();
	void textFamily( const QString & _f );
	void textSize( const QString & _p );
	void textColor();
	void textAlign( QAction * _a );

	void formatChanged( const QTextCharFormat & _f );
	void alignmentChanged( int _a );


private:
	QTextEdit * m_edit;
	QAction * m_actionTextBold,
		* m_actionTextUnderline,
		* m_actionTextItalic,
		* m_actionTextColor,
		* m_actionAlignLeft,
		* m_actionAlignCenter,
		* m_actionAlignRight,
		* m_actionAlignJustify;
	QComboBox * m_comboFont;
	QComboBox * m_comboSize;

} ;


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_PROJECT_NOTES_H
