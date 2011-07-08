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
/// Provides the State class.

#ifndef __STATE_HPP
#define __STATE_HPP

#include <data.hpp>
#include <thread.hpp>

/// A state variable.
/**
 * \see Instructions::INIT_FEEDBACK
 * \see Instructions::FEEDBACK
 */
class State {
	public:
		
		/// The data contained in this state variable.
		Data data;
		
		/// A boolean indicating wheter this state variable was used in the last round (true) or not (false).
		/**
		 * When a state variable is not used in a run of the thread this state variable belongs to, it is reset by the machine.
		 */
		bool is_executed;
		
		/// The thread that this state variable belongs to.
		Thread::Id thread;
		
		/// The default constructor.
		State() : is_executed(false) {}
		
};

#endif
