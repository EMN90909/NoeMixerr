// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2008-2009 Paul Giblock <drfaygo/at/gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_PEAK_CONTROLLER_H
#define NoeMixerr_PEAK_CONTROLLER_H

#include "Controller.h"
#include "ControllerDialog.h"

class QWidget;

namespace noemixerr
{


class PeakControllerEffect;

using PeakControllerEffectVector = std::vector<PeakControllerEffect*>;

class NoeMixerr_EXPORT PeakController : public Controller
{
	Q_OBJECT
public:
	PeakController( Model * _parent,
		PeakControllerEffect *_peak_effect = nullptr );


	~PeakController() override;

	void saveSettings( QDomDocument & _doc, QDomElement & _this ) override;
	void loadSettings( const QDomElement & _this ) override;
	QString nodeName() const override;

	static void initGetControllerBySetting();
	static PeakController * getControllerBySetting( const QDomElement & _this );

	static PeakControllerEffectVector s_effects;


public slots:
	gui::ControllerDialog * createDialog( QWidget * _parent ) override;
	void handleDestroyedEffect();
	void updateCoeffs();

protected:
	// The internal per-controller get-value function
	void updateValueBuffer() override;

	PeakControllerEffect * m_peakEffect;

	friend class PeakControllerDialog;

private:
	float m_currentSample;
	//backward compatibility for <= 0.4.15
	static int m_getCount;
	static int m_loadCount;
	static bool m_buggedFile;
	
	float m_attackCoeff;
	float m_decayCoeff;
	bool m_coeffNeedsUpdate;
} ;

namespace gui
{

class PeakControllerDialog : public ControllerDialog
{
	Q_OBJECT
public:
	PeakControllerDialog( Controller * _controller, QWidget * _parent );
	~PeakControllerDialog() override = default;

protected:
	void contextMenuEvent( QContextMenuEvent * _me ) override;
	void paintEvent( QPaintEvent * _pe ) override;
	void modelChanged() override;

	PeakController * m_peakController;

};


} // namespace gui

} // namespace noemixerr

#endif // NoeMixerr_PEAK_CONTROLLER_H
