/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <msp430x22x4.h>

#include <instructions.hpp>
#include <machine.hpp>
#include <types.hpp>
#include <data.hpp>

#include "serial.hpp"
#include "watchdog.hpp"

Watchdog watchdog;

namespace Pins {
	OutputPin<2,1> led0;
	OutputPin<2,0> led1;
	OutputPin<1,7> led2;
	InputPin<2,6> button;
}

bool red, yellow, green, button;

namespace {
	using namespace Instructions;
	Int8 script[] = { DEF_VM_OP, 0, 0, 0, 1, 0, 0, 3, 1, DEF_FUN_OP, 10, BUTTON_OP, IF_OP, 4, LIT_1_OP, GREEN_OP, JMP_OP, 2, LIT_1_OP, RED_OP, RET_OP, EXIT_OP }; //(if (button) (red 1) (green 1))
}

int main() {
	
	Machine machine;
	
	machine.install(Script(script, sizeof(script)));
	while(!machine.finished()) machine.step();
	
	while(true){
		
		red = yellow = green = false;
		button = Pins::button.check();
		
		machine.run();
		while(!machine.finished()) machine.step();
		
		red    ? Pins::led0.high() : Pins::led0.low();
		yellow ? Pins::led1.high() : Pins::led1.low();
		green  ? Pins::led2.high() : Pins::led2.low();
		
	}
	
}
