// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_GUI_MIDI_SETUP_WIDGET_H
#define NoeMixerr_GUI_MIDI_SETUP_WIDGET_H

#include <QGroupBox>

class QLineEdit;

namespace noemixerr::gui
{


class MidiSetupWidget : public QGroupBox
{
	Q_OBJECT
	MidiSetupWidget( const QString & caption, const QString & configSection,
		const QString & devName, QWidget * parent );
public:
	// create a widget with editors for all of @MidiClientType's fields
	template <typename MidiClientType> static MidiSetupWidget* create( QWidget * parent )
	{
		QString configSection = MidiClientType::configSection();
		QString dev = MidiClientType::probeDevice();
		return new MidiSetupWidget(MidiClientType::name(), configSection, dev, parent);
	}

	void saveSettings();

	void show();
private:
	QString m_configSection;
	QLineEdit *m_device;

};


} // namespace noemixerr::gui

#endif // NoeMixerr_GUI_MIDI_SETUP_WIDGET_H
