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
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// \name Threads
	/// \{
	
	/// Activate this or another Thread.
	/**
	 * \see Thread::activate()
	 * 
	 * \param Int The index of the Thread to activate.
	 */
	void ACTIVATE(Machine & machine){
		Thread::Id thread = machine.nextInt();
		machine.threads[thread].activate();
	}
	
	/// Deactivate this or another Thread.
	/**
	 * \see Thread::deactivate()
	 * 
	 * \param Int The index of the Thread to deactivate.
	 */
	void DEACTIVATE(Machine & machine){
		Thread::Id thread = machine.nextInt();
		machine.threads[thread].deactivate();
	}
	
	/// Trigger this or another Thread.
	/**
	 * \see Thread::trigger()
	 * 
	 * \param Int The index of the Thread to trigger.
	 */
	void TRIGGER(Machine & machine){
		Thread::Id thread = machine.nextInt();
		machine.threads[thread].trigger();
	}
	
	/// Get the result of the last execution of this or another Thread.
	/**
	 * \param Int The index of the Thread.
	 * \return Data The result of the last execution of the specified Thread.
	 */
	void RESULT(Machine & machine){
		Thread::Id thread = machine.nextInt();
		machine.stack.push(machine.threads[thread].result);
	}
	
	/// \}
#endif
	
}
