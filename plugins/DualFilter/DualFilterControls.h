// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Vesa Kivimäki <contact/dot/diizy/at/nbl/dot/fi>
// Copyright (c) 2008-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DUALFILTER_CONTROLS_H
#define DUALFILTER_CONTROLS_H

#include "EffectControls.h"
#include "DualFilterControlDialog.h"
#include "ComboBoxModel.h"

namespace noemixerr
{


class DualFilterEffect;


class DualFilterControls : public EffectControls
{
	Q_OBJECT
public:
	DualFilterControls( DualFilterEffect* effect );
	~DualFilterControls() override = default;

	void saveSettings( QDomDocument & _doc, QDomElement & _parent ) override;
	void loadSettings( const QDomElement & _this ) override;
	inline QString nodeName() const override
	{
		return "DualFilterControls";
	}

	int controlCount() override
	{
		return 11;
	}

	gui::EffectControlDialog* createView() override
	{
		return new gui::DualFilterControlDialog( this );
	}


private slots:
	void updateFilters();
	
private:
	DualFilterEffect* m_effect;

	BoolModel m_enabled1Model;
	ComboBoxModel m_filter1Model;
	FloatModel m_cut1Model;
	FloatModel m_res1Model;
	FloatModel m_gain1Model;

	FloatModel m_mixModel;

	BoolModel m_enabled2Model;
	ComboBoxModel m_filter2Model;
	FloatModel m_cut2Model;
	FloatModel m_res2Model;
	FloatModel m_gain2Model;

	friend class gui::DualFilterControlDialog;
	friend class DualFilterEffect;

} ;


} // namespace noemixerr

#endif
