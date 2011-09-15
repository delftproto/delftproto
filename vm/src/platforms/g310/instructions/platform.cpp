/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <machine.hpp>
#include <instructions.hpp>

#include "pins.hpp"

extern bool red, yellow, green, button;

namespace Instructions {
	
	using namespace std;
	
	void RED(Machine & machine){
		red = true;
	}
	
	void YELLOW(Machine & machine){
		yellow = true;
	}
	
	void GREEN(Machine & machine){
		green = true;
	}
	
	void BUTTON(Machine & machine){
		machine.stack.push(button ? 1 : 0);
	}
	
}

