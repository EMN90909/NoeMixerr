// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023 saker <sakertooth@gmail.com>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_SAMPLE_DECODER_H
#define NoeMixerr_SAMPLE_DECODER_H

#include <QString>
#include <optional>
#include <string>
#include <vector>

#include "SampleFrame.h"

namespace noemixerr {
class SampleDecoder
{
public:
	struct Result
	{
		std::vector<SampleFrame> data;
		int sampleRate;
	};

	struct AudioType
	{
		std::string name;
		std::string extension;
	};

	static auto decode(const QString& audioFile) -> std::optional<Result>;
	static auto supportedAudioTypes() -> const std::vector<AudioType>&;
};
} // namespace noemixerr

#endif // NoeMixerr_SAMPLE_DECODER_H
