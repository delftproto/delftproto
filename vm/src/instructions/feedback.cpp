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
/// Provides the feedback instructions.

#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Feedback
	/// \{
	
	namespace {
		Index INIT_FEEDBACK_state_index;
		
		void INIT_FEEDBACK_set_state(Machine & machine){
			machine.state[INIT_FEEDBACK_state_index].data = machine.stack.peek();
		}
	}
	
	/// Get and (if needed) initialize a state variable.
	/**
	 * \note A state variable will be reset when no feedback instruction is used on it in a single run.
	 *       It will be reinitialized by the next time INIT_FEEDBACK is executed.
	 * 
	 * \param Int8 The index of the state variable.
	 * \param Address The function to give the initial value, if not yet set.
	 * 
	 * \return Data The value of the state variable.
	 */
	void INIT_FEEDBACK(Machine & machine){
		Index state_index = machine.nextInt8();
		Address initialization_function = machine.stack.popAddress();
		machine.state[state_index].is_executed = true;
		machine.state[state_index].thread = machine.current_thread;
		if (machine.state[state_index].data.isSet()){
			machine.stack.push(machine.state[state_index].data);
		} else {
			INIT_FEEDBACK_state_index = state_index;
			machine.call(initialization_function, INIT_FEEDBACK_set_state);
		}
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Set a state variable.
	/**
	 * \param Int8 The index of the state variable.
	 * \param Data The new value for the state variable.
	 * 
	 * \return Data The new value of the state variable.
	 */
	void SET_FEEDBACK(Machine & machine){
		Index state_index = machine.nextInt8();
		machine.state[state_index].data = machine.stack.peek();
		machine.state[state_index].is_executed = true;
	}
#endif
	
	/// \deprecated_mitproto
	void FEEDBACK(Machine & machine){
		Index state_index = machine.nextInt8();
		Data value = machine.stack.pop();
		machine.state[state_index].data = value;
		machine.state[state_index].is_executed = true;
		machine.stack.pop(1);
		machine.stack.push(value);
	}
	
	/// \}
	
}
