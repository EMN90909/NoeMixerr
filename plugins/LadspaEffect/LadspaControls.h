// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef LADSPA_CONTROLS_H
#define LADSPA_CONTROLS_H

#include "EffectControls.h"
#include "LadspaMatrixControlDialog.h"

namespace noemixerr
{


class LadspaControl;
using control_list_t = QVector<LadspaControl*>;
namespace gui {
class LadspaControlDialog;
}
class LadspaEffect;


class LadspaControls : public EffectControls
{
	Q_OBJECT
public:
	LadspaControls( LadspaEffect * _eff );
	~LadspaControls() override;

	inline int controlCount() override
	{
		return m_controlCount;
	}

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "ladspacontrols";
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::LadspaMatrixControlDialog( this );
	}


protected slots:
	void updateLinkStatesFromGlobal();
	void linkPort( int _port, bool _state );


private:
	LadspaEffect * m_effect;
	ch_cnt_t m_processors;
	ch_cnt_t m_controlCount;
	bool m_noLink;
	BoolModel m_stereoLinkModel;
	//! control vector for each processor
	QVector<control_list_t> m_controls;


	friend class gui::LadspaControlDialog;
	friend class gui::LadspaMatrixControlDialog;
	friend class LadspaEffect;


signals:
	void effectModelChanged( noemixerr::LadspaControls * );

} ;


} // namespace noemixerr

#endif
