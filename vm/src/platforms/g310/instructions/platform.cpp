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

