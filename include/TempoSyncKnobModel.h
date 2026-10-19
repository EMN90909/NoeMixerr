// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2008 Danny McRae <khjklujn/at/yahoo.com>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_TEMPO_SYNC_KNOB_MODEL_H
#define NoeMixerr_TEMPO_SYNC_KNOB_MODEL_H

#include "MeterModel.h"

class QAction;

namespace noemixerr
{

namespace gui
{

class TempoSyncKnob;

} // namespace gui


class NOEMIXERR_EXPORT TempoSyncKnobModel : public FloatModel
{
	Q_OBJECT
	MODEL_IS_VISITABLE
public:
	enum class SyncMode
	{
		None,
		DoubleWholeNote,
		WholeNote,
		HalfNote,
		QuarterNote,
		EighthNote,
		SixteenthNote,
		ThirtysecondNote,
		Custom
	} ;

	TempoSyncKnobModel( const float _val, const float _min,
				const float _max, const float _step,
				const float _scale, Model * _parent,
				const QString & _display_name = QString() );
	~TempoSyncKnobModel() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _this, const QString& name ) override;
	void loadSettings( const QDomElement & _this, const QString& name ) override;

	SyncMode syncMode() const
	{
		return m_tempoSyncMode;
	}

	void setSyncMode( SyncMode _new_mode );

	float scale() const
	{
		return m_scale;
	}

	void setScale( float _new_scale );

	MeterModel & getCustomMeterModel() { return m_custom; }
	MeterModel const & getCustomMeterModel() const { return m_custom; }

signals:
	void syncModeChanged( noemixerr::TempoSyncKnobModel::SyncMode _new_mode );
	void scaleChanged( float _new_scale );


public slots:
	inline void disableSync()
	{
		setTempoSync( SyncMode::None );
	}
	void setTempoSync( SyncMode _note_type );
	void setTempoSync( QAction * _item );


protected slots:
	void calculateTempoSyncTime( noemixerr::bpm_t _bpm );
	void updateCustom();


private:
	SyncMode m_tempoSyncMode;
	SyncMode m_tempoLastSyncMode;
	float m_scale;

	MeterModel m_custom;


	friend class gui::TempoSyncKnob;

} ;

} // namespace noemixerr

#endif // NoeMixerr_TEMPO_SYNC_KNOB_MODEL_H
