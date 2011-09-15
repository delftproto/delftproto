/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

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
