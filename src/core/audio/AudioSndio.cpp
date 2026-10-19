// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2010-2016 jackmsr@openbsd.net
// Copyright (c) 2016-2017 David Carlier <devnexen@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "AudioSndio.h"

#ifdef NoeMixerr_HAVE_SNDIO

#include <cstdlib>
#include <QFormLayout>
#include <QLineEdit>

#include "endian_handling.h"
#include "LcdSpinBox.h"
#include "AudioEngine.h"

#include "ConfigManager.h"


namespace noemixerr
{

AudioSndio::AudioSndio(bool& _success_ful, AudioEngine* _audioEngine)
	: AudioDevice(std::clamp<ch_cnt_t>(ConfigManager::inst()->value("audiosndio", "channels").toInt(), DEFAULT_CHANNELS,
					  DEFAULT_CHANNELS),
		  _audioEngine)
{
	_success_ful = false;

	QString dev = ConfigManager::inst()->value( "audiosndio", "device" );

	if (dev == "")
	{
		m_hdl = sio_open( nullptr, SIO_PLAY, 0 );
	}
	else
	{
		m_hdl = sio_open( dev.toLatin1().constData(), SIO_PLAY, 0 );
	}

	if( m_hdl == nullptr )
	{
		printf( "sndio: failed opening audio-device\n" );
		return;
	}

	sio_initpar(&m_par);

	m_par.pchan = channels();
	m_par.bits = sizeof(int_sample_t) * 8;
	m_par.sig = 1; // int_sample_t must be signed
	m_par.le = SIO_LE_NATIVE;
	m_par.rate = sampleRate();
	m_par.round = audioEngine()->framesPerAudioBuffer();
	m_par.appbufsz = m_par.round * 2;

	struct sio_par reqpar = m_par;

	if (!sio_setpar(m_hdl, &m_par))
	{
		printf( "sndio: sio_setpar failed\n" );
		return;
	}
	if (!sio_getpar(m_hdl, &m_par))
	{
		printf( "sndio: sio_getpar failed\n" );
		return;
	}

	if (reqpar.pchan != m_par.pchan ||
		reqpar.bits != m_par.bits ||
		reqpar.le != m_par.le ||
		(::abs(static_cast<int>(reqpar.rate) - static_cast<int>(m_par.rate)) * 100)/reqpar.rate > 2)
	{
		printf( "sndio: returned params not as requested\n" );
		return;
	}

	if (!sio_start(m_hdl))
	{
		printf( "sndio: sio_start failed\n" );
		return;
	}

	_success_ful = true;
}


AudioSndio::~AudioSndio()
{
	if (m_hdl != nullptr)
	{
		sio_close( m_hdl );
		m_hdl = nullptr;
	}
}


void AudioSndio::startProcessingImpl()
{
	start(QThread::HighPriority);
}


void AudioSndio::stopProcessingImpl()
{
	stopProcessingThread( this );
}

void AudioSndio::run()
{
	const auto framesPerAudioBuffer = audioEngine()->framesPerAudioBuffer();
	const auto samplesPerAudioBuffer = framesPerAudioBuffer * channels();
	auto fbuf = std::vector<sample_t>(samplesPerAudioBuffer);
	auto ibuf = std::vector<int_sample_t>(samplesPerAudioBuffer);

	while (AudioDevice::isRunning())
	{
		audioEngine()->renderNextBuffer({fbuf.data(), channels(), framesPerAudioBuffer});

		// Sndio doesn't speak float, so convert samples to signed int.
		// While convertToS16() exists, it is intentionally not used
		// here. There is no need to convert endian-ness since sndio was
		// initialized with SIO_LE_NATIVE, and there's no reason to
		// also convert to SampleFrame.
		for (auto i = 0u; i < samplesPerAudioBuffer; ++i)
		{
			ibuf[i] = static_cast<int_sample_t>(AudioEngine::clip(fbuf[i]) * OUTPUT_SAMPLE_MULTIPLIER);
		}

		sio_write(m_hdl, ibuf.data(), ibuf.size() * sizeof(int_sample_t));
	}
}


AudioSndio::setupWidget::setupWidget( QWidget * _parent ) :
	AudioDeviceSetupWidget( AudioSndio::name(), _parent )
{
	QFormLayout * form = new QFormLayout(this);

	m_device = new QLineEdit( "", this );
	form->addRow(tr("Device"), m_device);

	gui::LcdSpinBoxModel * m = new gui::LcdSpinBoxModel( /* this */ );
	m->setRange(DEFAULT_CHANNELS, DEFAULT_CHANNELS);
	m->setStep( 2 );
	m->setValue( ConfigManager::inst()->value( "audiosndio",
	    "channels" ).toInt() );

	m_channels = new gui::LcdSpinBox( 1, this );
	m_channels->setModel( m );

	form->addRow(tr("Channels"), m_channels);
}


void AudioSndio::setupWidget::saveSettings()
{
	ConfigManager::inst()->setValue( "audiosndio", "device",
	    m_device->text() );
	ConfigManager::inst()->setValue( "audiosndio", "channels",
	    QString::number( m_channels->value<int>() ) );
}


} // namespace noemixerr

#endif	// NoeMixerr_HAVE_SNDIO
