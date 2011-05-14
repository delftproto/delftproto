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
/// Provides the global variables instructions.

#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Globals
	/// \{
	
	/// \deprecated_mitproto
	void DEF(Machine & machine){
		machine.globals.push(machine.stack.pop());
	}
	
	/// \deprecated_mitproto
	void DEF_TUP(Machine & machine){
		machine.execute(FAB_TUP);
		machine.globals.push(machine.stack.pop());
	}
	
	/// \deprecated_mitproto
	void DEF_VEC(Machine & machine){
		machine.execute(FAB_VEC);
		machine.globals.push(machine.stack.pop());
	}
	
	/// \deprecated_mitproto
	template<int elements>
	void DEF_NUM_VEC_N(Machine & machine){
		Tuple tuple(elements);
		for(Index i = 0; i < elements; i++) tuple.push(0);
		machine.globals.push(tuple);
	}
	
	/// \deprecated_mitproto
	void DEF_NUM_VEC(Machine & machine){
		machine.execute(FAB_NUM_VEC);
		machine.globals.push(machine.stack.pop());
	}
	
	/// Push a global variable on the execution stack.
	/**
	 * \tparam index The index of the global in the gobals list.
	 * \return The value of the global variable.
	 */
	template<int index>
	void GLO_REF_N(Machine & machine){
		machine.stack.push(machine.globals[index]);
	}
	
	/// Push a global variable on the execution stack.
	/**
	 * \param Int8 The index of the global in the gobals list.
	 * \return The value of the global variable.
	 */
	void GLO_REF(Machine & machine){
		Index index = machine.nextInt8();
		machine.stack.push(machine.globals[index]);
	}
	
	/// Push a global variable on the execution stack.
	/**
	 * \param Int16 The index of the global in the gobals list.
	 * \return The value of the global variable.
	 */
	void GLO_REF16(Machine & machine){
		Index index = machine.nextInt16();
		machine.stack.push(machine.globals[index]);
	}
	
	/// Define a function as a global.
	/**
	 * The address of the next instruction is pushed on the globals list
	 * and execution continues after the function definition.
	 * 
	 * \tparam size The number of (following) bytes that define the function.
	 */
	template<int size>
	void DEF_FUN_N(Machine & machine){
		machine.globals.push(machine.currentAddress());
		machine.skip(size);
	}
	
	/// Define a function as a global.
	/**
	 * The address of the next instruction is pushed on the globals list
	 * and execution continues after the function definition.
	 * 
	 * \param Int8 The number of (following) bytes that define the function.
	 */
	void DEF_FUN(Machine & machine){
		Size size = machine.nextInt8();
		machine.globals.push(machine.currentAddress());
		machine.skip(size);
	}
	
	/// Define a function as a global.
	/**
	 * The address of the next instruction is pushed on the globals list
	 * and execution continues after the function definition.
	 * 
	 * \param Inti16 The number of (following) bytes that define the function.
	 */
	void DEF_FUN16(Machine & machine){
		Size size = machine.nextInt16();
		machine.globals.push(machine.currentAddress());
		machine.skip(size);
	}
	
	/// \}
	
}
