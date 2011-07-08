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

/// \file
/// Provides the basic numeric types.

#include <cstddef>
#include <limits>

#ifndef __TYPES_HPP
#define __TYPES_HPP

/// \class Size
/// Used to represent sizes/counts of things in memory.
typedef size_t Size;

/// \class Index
/// Used to represent positive offsets of memory arrays.
typedef size_t Index; 

/// \class Counter
/// Used to count things.
typedef unsigned int Counter;

/// \class Int8
/// An 8 bit unsigned integer (byte).
typedef unsigned char Int8;

/// \class Int16
/// A 16 bit unsigned integer (two bytes).
typedef unsigned short Int16;

/// \class Int
/// A unsigned integer.
typedef unsigned int Int;

/// \class Alignment
/// The memory is aligned by this type.
typedef unsigned char Alignment;

/** \class Number
 * \brief A floating point number.
 * 
 * One of the types that can be stored in Data.
 */
typedef float Number;

/// \var Number_infinity
/// A Number representing infinity.
namespace {
	const Number Number_infinity = std::numeric_limits<Number>::infinity();
}

#endif
