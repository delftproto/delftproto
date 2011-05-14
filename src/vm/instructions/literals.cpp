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
/// Provides the literal Number instructions.

#include <ieee754.hpp>
#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Literals
	/// \{
	
	/// Literal Number.
	/**
	 * \param Int8 The value.
	 * \return The value as a Number.
	 */
	void LIT8(Machine & machine){
		machine.stack.push(machine.nextInt8());
	}
	
	/// Literal Number.
	/**
	 * \param Int16 The value.
	 * \return The value as a Number.
	 */
	void LIT16(Machine & machine){
		machine.stack.push(machine.nextInt16());
	}
	
	/// Literal Number.
	/**
	 * \tparam value The value.
	 * \return The value as a Number.
	 */
	template<int value>
	void LIT_N(Machine & machine){
		machine.stack.push(value);
	}
	
	/// Literal Number.
	/**
	 * \param IEEE754binary32 The value.
	 * \return The value as a Number.
	 */
	void LIT_FLO(Machine & machine){
		Int8 float_data[4];
		float_data[0] = machine.nextInt8();
		float_data[1] = machine.nextInt8();
		float_data[2] = machine.nextInt8();
		float_data[3] = machine.nextInt8();
		machine.stack.push(Number(IEEE754binary32(float_data)));
	}
	
	/// Positive infinity.
	/**
	 * \return \m{+\infty}
	 */
	void INF(Machine & machine){
		machine.stack.push(Number_infinity);
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Negative infinity.
	/**
	 * \return \m{-\infty}
	 */
	void NEG_INF(Machine & machine){
		machine.stack.push(-Number_infinity);
	}
#endif
	
}
