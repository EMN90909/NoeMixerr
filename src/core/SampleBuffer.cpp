// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2005-2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#include "SampleBuffer.h"

#include <QDebug>
#include <QMessageBox>
#include <cstring>

#include "GuiApplication.h"
#include "PathUtil.h"
#include "SampleDecoder.h"

namespace noemixerr {

SampleBuffer::SampleBuffer(const SampleFrame* data, size_t numFrames, int sampleRate)
	: m_data(data, data + numFrames)
	, m_sampleRate(sampleRate)
{
}

SampleBuffer::SampleBuffer(std::vector<SampleFrame> data, int sampleRate, const QString& audioFile)
	: m_data(std::move(data))
	, m_audioFile(audioFile)
	, m_sampleRate(sampleRate)
{
}

void swap(SampleBuffer& first, SampleBuffer& second) noexcept
{
	using std::swap;
	swap(first.m_data, second.m_data);
	swap(first.m_audioFile, second.m_audioFile);
	swap(first.m_sampleRate, second.m_sampleRate);
}

QString SampleBuffer::toBase64() const
{
	// TODO: Replace with non-Qt equivalent
	const auto data = reinterpret_cast<const char*>(m_data.data());
	const auto size = static_cast<int>(m_data.size() * sizeof(SampleFrame));
	const auto byteArray = QByteArray{data, size};
	return byteArray.toBase64();
}

auto SampleBuffer::emptyBuffer() -> std::shared_ptr<const SampleBuffer>
{
	static auto s_buffer = std::make_shared<const SampleBuffer>();
	return s_buffer;
}

std::shared_ptr<const SampleBuffer> SampleBuffer::fromFile(const QString& filePath)
{
	if (filePath.isEmpty()) { return SampleBuffer::emptyBuffer(); }

	const auto absolutePath = PathUtil::toAbsolute(filePath);
	const auto storedPath = PathUtil::toShortestRelative(filePath);

	auto result = SampleDecoder::decode(absolutePath);

	if (!result)
	{
		// TODO: Improve error handling. We dont always want to show a message box on failure when there is a GUI (e.g.
		// when loading the project), and this function also shouldn't be concerned with handling the error.
		if (gui::getGUI())
		{
			QMessageBox::warning(nullptr, QObject::tr("Failed to load sample"),
				QObject::tr("The sample may be corrupted or unsupported."));
		}
		else
		{
			qWarning() << QObject::tr(
				"Failed to load sample at path %1, the file may not exist, be corrupted, or is unsupported.")
							  .arg(absolutePath);
		}

		return SampleBuffer::emptyBuffer();
	}

	auto& [data, sampleRate] = *result;
	return std::make_shared<SampleBuffer>(std::move(data), sampleRate, storedPath);
}

std::shared_ptr<const SampleBuffer> SampleBuffer::fromBase64(const QString& str, int sampleRate)
{
	if (str.isEmpty()) { return SampleBuffer::emptyBuffer(); }

	const auto bytes = QByteArray::fromBase64(str.toUtf8());

	if (bytes.size() % sizeof(SampleFrame) != 0)
	{
		// TODO: Improve error handling. We dont always want to show a message box on failure when there is a GUI (e.g.
		// when loading the project), and this function also shouldn't be concerned with handling the error.
		if (gui::getGUI())
		{
			QMessageBox::warning(
				nullptr, QObject::tr("Failed to load sample"), QObject::tr("The sample size is invalid."));
		}
		else
		{
			qWarning() << QObject::tr("Failed to load Base64 sample, invalid size");
		}

		return SampleBuffer::emptyBuffer();
	}

	auto data = std::vector<SampleFrame>(bytes.size() / sizeof(SampleFrame));
	std::memcpy(reinterpret_cast<char*>(data.data()), bytes, bytes.size());
	return std::make_shared<SampleBuffer>(std::move(data), sampleRate);
}

} // namespace noemixerr
