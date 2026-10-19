// SPDX-License-Identifier: GPL-2.0-or-later
// NoeMixerr: modified LMMS-derived source; original copyrights retained.
// Copyright (c) 2023-2023 Johannes Lorenz <jlsf2013$users.sourceforge.net, $=@>
// See LICENSE.txt and doc/AUTHORS for original authors and license.


#ifndef NoeMixerr_NOCOPYNOMOVE_H
#define NoeMixerr_NOCOPYNOMOVE_H

namespace noemixerr
{

/**
 * Inherit this class to make your class non-copyable and non-movable
 */
class NoCopyNoMove
{
protected:
	NoCopyNoMove() = default;
	NoCopyNoMove(const NoCopyNoMove& other) = delete;
	NoCopyNoMove& operator=(const NoCopyNoMove& other) = delete;
	NoCopyNoMove(NoCopyNoMove&& other) = delete;
	NoCopyNoMove& operator=(NoCopyNoMove&& other) = delete;
};

} // namespace noemixerr

#endif // NoeMixerr_NOCOPYNOMOVE_H

