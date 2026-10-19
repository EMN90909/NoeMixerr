// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2006-2008 Danny McRae <khjklujn/at/users.sourceforge.net>
// Copyright (c) 2009 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef _LADSPA_EFFECT_H
#define _LADSPA_EFFECT_H

#include <QMutex>

#include "Effect.h"
#include "ladspa.h"
#include "LadspaControls.h"
#include "LadspaManager.h"

namespace noemixerr
{

struct port_desc_t;
using multi_proc_t = QVector<port_desc_t*>;

class LadspaEffect : public Effect
{
	Q_OBJECT
public:
	LadspaEffect( Model * _parent,
			const Descriptor::SubPluginFeatures::Key * _key );
	~LadspaEffect() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	void setControl( int _control, LADSPA_Data _data );

	EffectControls * controls() override
	{
		return m_controls;
	}

	inline const multi_proc_t & getPortControls()
	{
		return m_portControls;
	}

	ch_cnt_t processorCount() const
	{
		return m_processors;
	}

private slots:
	void changeSampleRate();


private:
	void pluginInstantiation();
	void pluginDestruction();

	static sample_rate_t maxSamplerate( const QString & _name );

	QMutex m_pluginMutex;
	LadspaControls * m_controls;

	ladspa_key_t m_key;
	int m_portCount;
	bool m_inPlaceBroken;

	const LADSPA_Descriptor * m_descriptor;
	QVector<LADSPA_Handle> m_handles;

	QVector<multi_proc_t> m_ports;
	multi_proc_t m_portControls;

	ch_cnt_t m_processors = 1;
};


} // namespace noemixerr

#endif
