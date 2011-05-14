// This file is part of DelftProto.
// 
// DelftProto is free software: you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option) any
// later version.
// 
// DelftProto is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
// PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along
// with DelftProto.  If not, see <http://www.gnu.org/licenses/>.

#include <float.h>

#ifndef __TYPES_HPP
#define __TYPES_HPP

typedef unsigned int   Size;
typedef unsigned int   Index;
typedef unsigned int   Counter;
typedef unsigned char  Int8;
typedef unsigned short Int16;
typedef float          Number;
typedef unsigned short Alignment;

namespace {
	const Number Number_infinity = 1.0f / 0.0f;
}

#endif
