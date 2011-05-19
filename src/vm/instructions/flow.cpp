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
/// Provides the control flow instructions.

#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Control flow
	/// \{
	
	/// Define the VM requirements.
	/**
	 * This should be executed before any other instruction.
	 * 
	 * \param Int8 The export length. (This parameter is currently not used.)
	 * \param Int8 The number of exports.
	 * \param Int16 The number of globals.
	 * \param Int8 The number of state variables.
	 * \param Int16 The size of the execution stack.
	 * \param Int8 The size of the environment stack.
	 */
	void DEF_VM(Machine & machine){
		/*Size export_length    =*/ machine.nextInt8 (); //TODO: ...
		Size     exports_size = machine.nextInt8 ();
		Size     globals_size = machine.nextInt16();
		Size       state_size = machine.nextInt8 ();
		Size       stack_size = machine.nextInt16();
		Size environment_size = machine.nextInt8 ();
		
		machine.       hood.reset(    exports_size);
		machine.    globals.reset(    globals_size);
		machine.      state.reset(      state_size);
		machine.      stack.reset(    stack_size+1);
		machine.environment.reset(environment_size);
		
		machine.hood.add(machine.id);
		
		Instruction callback = machine.callbacks.pop();
		machine.callbacks.reset(3); //TODO: ...
		machine.callbacks.push(callback);
	}
	
	/// Exit the installation script.
	/**
	 * This must be the last instruction of an installation script.
	 */
	void EXIT(Machine & machine){
		machine.stack.push(machine.globals.peek());
		machine.stack.push(Data());
		machine.retn();
	}
	
	/// Return from a function.
	/**
	 * \param Data The return value.
	 * 
	 * \return Data The return value.
	 */
	void RET(Machine & machine){
		machine.retn();
	}
	
	/// Clean the stack.
	/**
	 * Preserve the top element while the rest of the given range is dropped.
	 * For example, after executing <tt>ALL_OP 3</tt> on the stack <tt>[1 2 3 4]</tt>, <tt>[1 4]</tt> is left.
	 * 
	 * \param Int8 The number of elements to clean up.
	 * \param Data <tt>[n]</tt> The elements on the stack.
	 * 
	 * \return Data The top element.
	 */
	void ALL(Machine & machine){
		Data data = machine.stack.peek();
		machine.stack.pop(machine.nextInt8());
		machine.stack.push(data);
	}
	
	/// Waste clockcycles.
	void NOP(Machine & machine){
		// No Operation
	}
	
	/// Pick one of two values, using a condition.
	/**
	 * \param Number The condition.
	 * \param Data The 'true' value.
	 * \param Data The 'false' value.
	 * 
	 * \return Data The 'false' value when the condition is 0, the 'true' value otherwise.
	 */
	void MUX(Machine & machine){
		Data false_value = machine.stack.pop();
		Data  true_value = machine.stack.pop();
		Number condition = machine.stack.popNumber();
		machine.stack.push(condition ? true_value : false_value);
	}
	
#if MIT_COMPATIBILITY != NO_MIT
	/// \deprecated_mitproto{MUX}
	void VMUX(Machine & machine){
		Data & result = machine.globals[machine.nextInt8()];
		Data false_value = machine.stack.pop();
		Data  true_value = machine.stack.pop();
		Number condition = machine.stack.popNumber();
		machine.stack.push(result = (condition ? true_value : false_value).copy());
	}
#endif
	
	/// A conditional jump.
	/**
	 * Skips the given number of bytes if the condition is not 0.
	 * 
	 * \param Int8 The number of bytes to skip when the condition is true.
	 * \param Number The condition.
	 */
	void IF(Machine & machine){
		Size skip = machine.nextInt8();
		if (machine.stack.popNumber()) machine.skip(skip);
	}
	
	/// A conditional jump.
	/**
	 * Skips the given number of bytes if the condition is not 0.
	 * 
	 * \param Int16 The number of bytes to skip when the condition is true.
	 * \param Number The condition.
	 */
	void IF16(Machine & machine){
		Size skip = machine.nextInt16();
		if (machine.stack.popNumber()) machine.skip(skip);
	}
	
	/// Jump to another address.
	/**
	 * \note You can only jump forward.
	 * 
	 * \param Int8 the number of bytes to jump (relative).
	 */
	void JMP(Machine & machine){
		machine.skip(machine.nextInt8());
	}
	
	/// Jump to another address.
	/**
	 * \note You can only jump forward.
	 * 
	 * \param Int16 The number of bytes to jump (relative).
	 */
	void JMP16(Machine & machine){
		machine.skip(machine.nextInt16());
	}
	
	/// \}
	
}
