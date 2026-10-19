// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2018-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "Lv2ControlBase.h"

#ifdef NoeMixerr_HAVE_LV2

#include <algorithm>
#include <QDebug>
#include <QtGlobal>

#include "Engine.h"
#include "noemixerr_constants.h"
#include "Lv2Manager.h"
#include "Lv2Proc.h"


namespace noemixerr
{


Plugin::Type Lv2ControlBase::check(const LilvPlugin *plugin,
	std::vector<PluginIssue> &issues)
{
	// for some reason, all checks can be done by one processor...
	return Lv2Proc::check(plugin, issues);
}




Lv2ControlBase::Lv2ControlBase(Model* that, const QString &uri) :
	m_plugin(Engine::getLv2Manager()->getPlugin(uri))
{
	if (m_plugin)
	{
		init(that);
	}
	else
	{
		qCritical() << "No Lv2 plugin found for URI" << uri;
		throw std::runtime_error("No Lv2 plugin found for given URI");
	}
}




Lv2ControlBase::~Lv2ControlBase() = default;




void Lv2ControlBase::init(Model* meAsModel)
{
	int channelsLeft = DEFAULT_CHANNELS; // NoeMixerr plugins are stereo
	while (channelsLeft > 0)
	{
		std::unique_ptr<Lv2Proc> newOne = std::make_unique<Lv2Proc>(m_plugin, meAsModel);
		channelsLeft -= std::max(
			1 + static_cast<bool>(newOne->inPorts().m_right),
			1 + static_cast<bool>(newOne->outPorts().m_right));
		Q_ASSERT(channelsLeft >= 0);
		m_procs.push_back(std::move(newOne));
	}
	m_channelsPerProc = DEFAULT_CHANNELS / m_procs.size();
	linkAllModels();
}




void Lv2ControlBase::shutdown()
{
	// currently nothing to do here
}




void Lv2ControlBase::reload()
{
	for (const auto& c : m_procs) { c->reload(); }
}




LinkedModelGroup *Lv2ControlBase::getGroup(std::size_t idx)
{
	return (m_procs.size() > idx) ? m_procs[idx].get() : nullptr;
}




const LinkedModelGroup *Lv2ControlBase::getGroup(std::size_t idx) const
{
	return (m_procs.size() > idx) ? m_procs[idx].get() : nullptr;
}




void Lv2ControlBase::copyModelsFromNoeMixerr() {
	for (const auto& c : m_procs) { c->copyModelsFromCore(); }
}




void Lv2ControlBase::copyModelsToNoeMixerr() const
{
	for (const auto& c : m_procs) { c->copyModelsToCore(); }
}




void Lv2ControlBase::copyBuffersFromNoeMixerr(const SampleFrame* buf, f_cnt_t frames) {
	unsigned firstChan = 0; // tell the procs which channels they shall read from
	for (const auto& c : m_procs) 
	{
		c->copyBuffersFromCore(buf, firstChan, m_channelsPerProc, frames);
		firstChan += m_channelsPerProc;
	}
}




void Lv2ControlBase::copyBuffersToNoeMixerr(SampleFrame* buf, f_cnt_t frames) const {
	unsigned firstChan = 0; // tell the procs which channels they shall write to
	for (const auto& c : m_procs) {
		c->copyBuffersToCore(buf, firstChan, m_channelsPerProc, frames);
		firstChan += m_channelsPerProc;
	}
}




void Lv2ControlBase::run(f_cnt_t frames) {
	for (const auto& c : m_procs) { c->run(frames); }
}




void Lv2ControlBase::saveSettings(QDomDocument &doc, QDomElement &that)
{
	LinkedModelGroups::saveSettings(doc, that);
	
	// TODO: save state if supported by plugin
}




void Lv2ControlBase::loadSettings(const QDomElement &that)
{
	LinkedModelGroups::loadSettings(that);
	
	// TODO: load state if supported by plugin
}




void Lv2ControlBase::loadFile(const QString &file)
{
	(void)file;
}




std::size_t Lv2ControlBase::controlCount() const {
	std::size_t res = 0;
	for (const auto& c : m_procs) { res += c->controlCount(); }
	return res;
}




bool Lv2ControlBase::hasNoteInput() const
{
	return std::any_of(m_procs.begin(), m_procs.end(),
		[](const auto& c) { return c->hasNoteInput(); });
}




void Lv2ControlBase::handleMidiInputEvent(const MidiEvent &event,
	const TimePos &time, f_cnt_t offset)
{
	for (const auto& c : m_procs) { c->handleMidiInputEvent(event, time, offset); }
}


} // namespace noemixerr


#endif // NoeMixerr_HAVE_LV2
