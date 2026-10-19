// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2014 Tobias Doerffel <tobydox/at/users.sourceforge.net>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_MIX_HELPERS_H
#define NoeMixerr_MIX_HELPERS_H

#include "AudioBufferView.h"

namespace noemixerr
{

class ValueBuffer;
class SampleFrame;

namespace MixHelpers
{

bool isSilent(const SampleFrame* src, int frames);

bool isSilent(std::span<const sample_t> buffer);

/*! \brief Add samples from src to dst */
void add( SampleFrame* dst, const SampleFrame* src, int frames );

/*! \brief Add samples from src to dst */
void add(PlanarBufferView<sample_t> dst, PlanarBufferView<const sample_t> src);

/*! \brief Multiply samples from `dst` by `coeff` */
void multiply(SampleFrame* dst, float coeff, int frames);

/*! \brief Add samples from src multiplied by coeffSrc to dst */
void addMultiplied( SampleFrame* dst, const SampleFrame* src, float coeffSrc, int frames );

/*! \brief Add samples from src multiplied by coeffSrc to dst, swap inputs */
void addSwappedMultiplied( SampleFrame* dst, const SampleFrame* src, float coeffSrc, int frames );

/*! \brief Add samples from src multiplied by coeffSrc and coeffSrcBuf to dst */
void addMultipliedByBuffer( SampleFrame* dst, const SampleFrame* src, float coeffSrc, ValueBuffer * coeffSrcBuf, int frames );

/*! \brief Add samples from src multiplied by coeffSrc and coeffSrcBuf to dst */
void addMultipliedByBuffers( SampleFrame* dst, const SampleFrame* src, ValueBuffer * coeffSrcBuf1, ValueBuffer * coeffSrcBuf2, int frames );

/*! \brief Add samples from src multiplied by coeffSrcLeft/coeffSrcRight to dst */
void addMultipliedStereo( SampleFrame* dst, const SampleFrame* src, float coeffSrcLeft, float coeffSrcRight, int frames );

/*! \brief Multiply dst by coeffDst and add samples from src multiplied by coeffSrc */
void multiplyAndAddMultiplied( SampleFrame* dst, const SampleFrame* src, float coeffDst, float coeffSrc, int frames );

/*! \brief Multiply dst by coeffDst and add samples from srcLeft/srcRight multiplied by coeffSrc */
void multiplyAndAddMultipliedJoined( SampleFrame* dst, const sample_t* srcLeft, const sample_t* srcRight, float coeffDst, float coeffSrc, int frames );

} // namespace MixHelpers


} // namespace noemixerr

#endif // NoeMixerr_MIX_HELPERS_H
