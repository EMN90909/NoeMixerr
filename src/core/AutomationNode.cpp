// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2020 Ian Caio <iancaio_dev/at/hotmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AutomationNode.h"
#include "AutomationClip.h"


namespace noemixerr
{

// Dummy constructor for the QMap
AutomationNode::AutomationNode() :
	m_clip(nullptr),
	m_pos(0),
	m_inValue(0),
	m_outValue(0),
	m_inTangent(0),
	m_outTangent(0),
	m_lockedTangents(false)
{
}

AutomationNode::AutomationNode(AutomationClip* clip, float value, int pos) :
	m_clip(clip),
	m_pos(pos),
	m_inValue(value),
	m_outValue(value),
	m_inTangent(0),
	m_outTangent(0),
	m_lockedTangents(false)
{
}

AutomationNode::AutomationNode(AutomationClip* clip, float inValue, float outValue, int pos) :
	m_clip(clip),
	m_pos(pos),
	m_inValue(inValue),
	m_outValue(outValue),
	m_inTangent(0),
	m_outTangent(0),
	m_lockedTangents(false)
{
}

void AutomationNode::setInValue(float value)
{
	m_inValue = value;

	// Recalculate the tangents from neighbor nodes
	AutomationClip::timeMap & tm = m_clip->getTimeMap();

	// Get an iterator pointing to this node
	AutomationClip::timeMap::iterator it = tm.lowerBound(m_pos);
	// If it's not the first node, get the one immediately behind it
	if (it != tm.begin()) { --it; }

	// Generate tangents from the previously, current and next nodes
	m_clip->generateTangents(it, 3);
}

void AutomationNode::setOutValue(float value)
{
	m_outValue = value;

	// Recalculate the tangents from neighbor nodes
	AutomationClip::timeMap & tm = m_clip->getTimeMap();

	// Get an iterator pointing to this node
	AutomationClip::timeMap::iterator it = tm.lowerBound(m_pos);
	// If it's not the first node, get the one immediately behind it
	if (it != tm.begin()) { --it; }

	// Generate tangents from the previously, current and next nodes
	m_clip->generateTangents(it, 3);
}

void AutomationNode::resetOutValue()
{
	// Calls setOutValue so it also takes care of generating
	// the tangents
	setOutValue(m_inValue);
}

} // namespace noemixerr
