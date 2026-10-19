// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// Copyright (c) 2014-2017, David French <dave/dot/french3/at/googlemail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef ANALYZER_H
#define ANALYZER_H


#include "DataprocLauncher.h"
#include "Effect.h"
#include "LocklessRingBuffer.h"
#include "SaControls.h"
#include "SaProcessor.h"

namespace noemixerr
{


//! Top level class; handles NoeMixerr interface and feeds data to the data processor.
class Analyzer : public Effect
{
public:
	Analyzer(Model *parent, const Descriptor::SubPluginFeatures::Key *key);
	~Analyzer() override;

	ProcessStatus processImpl(SampleFrame* buf, const f_cnt_t frames) override;

	EffectControls *controls() override {return &m_controls;}

	SaProcessor *getProcessor() {return &m_processor;}

private:
	SaProcessor m_processor;
	SaControls m_controls;

	// Maximum NoeMixerr buffer size (hard coded, the actual constant is hard to get)
	const unsigned int m_maxBufferSize = 4096;

	// QThread::create() workaround
	// Replace DataprocLauncher by QThread and replace initializer in constructor
	// with the following commented line when NoeMixerr CI starts using Qt > 5.9
	//m_processorThread = QThread::create([=]{m_processor.analyze(m_inputBuffer);});
	DataprocLauncher m_processorThread;

	LocklessRingBuffer<SampleFrame> m_inputBuffer;

	#ifdef SA_DEBUG
		int m_last_dump_time;
		int m_dump_count;
		float m_sum_execution;
		float m_max_execution;
	#endif
};


} // namespace noemixerr

#endif // ANALYZER_H

