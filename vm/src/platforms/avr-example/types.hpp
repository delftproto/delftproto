/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <float.h>

#ifndef __TYPES_HPP
#define __TYPES_HPP

typedef unsigned int   Size;
typedef unsigned int   Index;
typedef unsigned int   Counter;
typedef unsigned char  Int8;
typedef unsigned int   Int16;
typedef unsigned int   Int;
typedef float          Number;
typedef unsigned char  Alignment;

namespace {
	const Number Number_infinity = 1.0f / 0.0f;
}

#endif
