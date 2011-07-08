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
/// Provides the IEEE754binary32 class.

#ifndef __IEEE754_HPP
#define __IEEE754_HPP

#include <types.hpp>

/// An IEEE 754 binary32 floating point number representation.
/**
 * Used to convert between the platform specific floating point representation and an IEEE 754 binary32 representation.
 * 
 * This implementation assumes that on the used platform \c float is already an IEEE 754 binary32 floating point number.
 * Platforms can \ref fileoverloading "overload this file" if any conversion is needed.
 */
class IEEE754binary32 {
		
	private:
		float value;
		
	public:
		
		/// Convert from a Number.
		IEEE754binary32(Number number) : value(number) {}
		
		/// Convert to a Number.
		operator Number() { return value; }
		
		/// Convert from the IEEE 754 binary32 4 byte representation.
		IEEE754binary32(Int8 data[4]) : value(*reinterpret_cast<float *>(data)) {}
		
		/// Convert to the IEEE 754 binary32 4 byte representation.
		operator Int8 * () { return reinterpret_cast<Int8 *>(&value); }
		
};

#endif

