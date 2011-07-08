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
	
	machine.install(script);
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
