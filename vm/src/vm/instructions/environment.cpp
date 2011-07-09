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
/// Provides the environment stack instructions.

#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Environment stack
	/// \{
	
	/// Push an element from the environment stack on the execution stack.
	/**
	 * \tparam index The index (relative to the top) of the element on the environment stack.
	 * \return The element.
	 */
	template<int index>
	void REF_N(Machine & machine){
		machine.stack.push(machine.environment.peek(index));
	}
	
	/// Push an element from the environment stack on the execution stack.
	/**
	 * \param Int8 The index (relative to the top) of the element on the environment stack.
	 * \return The element.
	 */
	void REF(Machine & machine){
		Index index = machine.nextInt8();
		machine.stack.push(machine.environment.peek(index));
	}
	
	/// Push one or more elements on the environment stack.
	/**
	 * The given number of elements will be moved from the top of the execution stack to the environment stack.
	 * 
	 * \tparam elements The number of elements.
	 * \param Data <tt>[n]</tt> The elements.
	 */
	template<int elements>
	void LET_N(Machine & machine){
		for(Index i = 1; i <= elements; i++) machine.environment.push(machine.stack.peek(elements-i));
		machine.stack.pop(elements);
	}
	
	/// Push one or more elements on the environment stack.
	/**
	 * The given number of elements will be moved from the top of the execution stack to the environment stack.
	 * 
	 * \param Int8 The number of elements.
	 * \param Data <tt>[n]</tt> The elements.
	 */
	void LET(Machine & machine){
		Size elements = machine.nextInt8();
		for(Index i = 1; i <= elements; i++) machine.environment.push(machine.stack.peek(elements-i));
		machine.stack.pop(elements);
	}
	
	/// Remove one or more elements from the environment stack.
	/**
	 * \tparam elements The number of elements.
	 */
	template<int elements>
	void POP_LET_N(Machine & machine){
		machine.environment.pop(elements);
	}
	
	/// Remove one or more elements from the environment stack.
	/**
	 * \param Int8 The number of elements.
	 */
	void POP_LET(Machine & machine){
		Size elements = machine.nextInt8();
		machine.environment.pop(elements);
	}
	
	/// \}
	
}
