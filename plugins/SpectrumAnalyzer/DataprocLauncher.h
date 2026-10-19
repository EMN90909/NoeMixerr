// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2019 Martin Pavelek <he29/dot/HS/at/gmail/dot/com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef DATAPROCLAUNCHER_H
#define DATAPROCLAUNCHER_H

#include <QThread>

#include "SaProcessor.h"
#include "LocklessRingBuffer.h"

namespace noemixerr
{


class DataprocLauncher : public QThread
{
public:
	explicit DataprocLauncher(SaProcessor &proc, LocklessRingBuffer<SampleFrame> &buffer)
		: m_processor(&proc),
		m_inputBuffer(&buffer)
	{
	}

private:
	void run() override
	{
		m_processor->analyze(*m_inputBuffer);
	}

	SaProcessor *m_processor;
	LocklessRingBuffer<SampleFrame> *m_inputBuffer;
};


} // namespace noemixerr

#endif // DATAPROCLAUNCHER_H
