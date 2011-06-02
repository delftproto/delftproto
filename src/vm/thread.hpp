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
/// Provides the Thread classs.

#ifndef __THREAD_HPP
#define __THREAD_HPP

#include <types.hpp>
#include <data.hpp>

/// A thread.
/**
 * The 'main function' of each thread is stored in the Machine::globals list of the machine.
 * The first thread corresponds to the last global, the second thread to the second last global, and so on.
 * 
 * A thread can be triggered and activated. It is called 'pending' when it is either triggered, activated or both.
 * The Machine::run() starts the execution of the next pending Thread, Round-robin style.
 */
class Thread {
	
	public:
		/// An index in the Machine::threads list.
		typedef Int8 Id;
		
	protected:
		bool is_triggered;
		bool is_active;
		
	public:
		/// Trigger this thread.
		/**
		 * The specified thread will be executed once.
		 * 
		 * There is no waiting line. Triggering an already triggered thread has no effect.
		 */
		void trigger() {
			is_triggered = true;
		}
		
		/// Activate this thread.
		/**
		 * The specified thread will be executed infinitely, until deactivation.
		 */
		void activate() {
			is_active = true;
		}
		
		/// Deactivate this thread.
		/*
		 * The selected thread will stop executing infinitely.
		 * 
		 * This has no effect for any pending triggers.
		 */
		void deactivate() {
			is_active = false;
		}
		
		/// Check whether this thread is pending (true) or not (false).
		bool pending() const {
			return is_active || is_triggered;
		}
		
		/// The result of the last execution of this thread.
		Data result;
		
	protected:
		/// Remove a pending trigger.
		void untrigger() {
			is_triggered = false;
		}
		
		friend class Machine;
		
};

#endif
