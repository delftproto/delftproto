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

#include <csignal>
#include <cstdlib>

#include <machine.hpp>

namespace {
	Machine * machine = 0;
	
	void ctrl_c_handler(int x) {
		if (!machine) std::abort();
		for(Size i = 0; i < machine->threads.size(); i++){
			if (machine->threads[i].ctrl_c_triggered) machine->threads[i].trigger();
		}
		machine = 0; // To make sure hitting Ctrl+C twice will abort the program.
	}
}

namespace Instructions {
	
	void CTRL_C_TRIGGER(Machine & machine){
		Thread::Id thread = machine.nextInt();
		::machine = &machine;
		signal(SIGINT, ctrl_c_handler);
		machine.threads[thread].ctrl_c_triggered = true;
	}
	
	void CTRL_C_NO_TRIGGER(Machine & machine){
		Thread::Id thread = machine.nextInt();
		machine.threads[thread].ctrl_c_triggered = false;
	}
	
}
