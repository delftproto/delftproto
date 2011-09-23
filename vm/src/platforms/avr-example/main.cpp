/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <instructions.hpp>
#include <machine.hpp>
#include <types.hpp>
#include <data.hpp>

namespace {
	using namespace Instructions;
//	Int8 script[] = { DEF_VM_OP, 0, 0, 0, 1, 0, 0, 3, 1, DEF_FUN_OP, 10, BUTTON_OP, IF_OP, 4, LIT_1_OP, GREEN_OP, JMP_OP, 2, LIT_1_OP, RED_OP, RET_OP, EXIT_OP }; //(if (button) (red 1) (green 1))
	Int8 script[] = { EXIT_OP };
}

int main() {
	Time t = 0;
	Machine machine;
	machine.install(Script(script, sizeof(script)));
	while(!machine.finished()) machine.step();
	while(true){
		machine.run(t += 1);
		while(!machine.finished()) machine.step();
	}
}
