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

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>

#include <instructions.hpp>
#include <machine.hpp>
#include <types.hpp>
#include <data.hpp>
#include <stack.hpp>

using namespace std;

namespace {
	using namespace Instructions;
	
	Int8 script[] = { DEF_VM_OP, 0, 0, 0, 100, 1, 0, 100, 100,
	                  DEF_FUN_6_OP, REF_0_OP, GLO_REF_1_OP, INIT_FEEDBACK_OP, 0, ADD_OP, RET_OP,
	                  DEF_FUN_2_OP, LIT_2_OP, RET_OP,
	                  DEF_FUN_OP, 15, HELLOWORLD_OP, GLO_REF_0_OP, LIT_0_OP, LIT_1_OP, LIT_2_OP, FAB_TUP_OP, 3, TUP_MAP_OP, LIT_3_OP, LIT_1_OP, LIT_2_OP, FAB_TUP_OP, 3, VEC_ADD_OP, RET_OP,
	                  EXIT_OP };
}

namespace { // Formatted output operators for the Data types
	
	ostream & operator << (ostream & out, Data const & data);
	
	// An address is expressed as an at sign ('@') followed by three decimal digits.
	ostream & operator << (ostream & out, Address const & address) {
		if (address >= script) return out << '@' << setw(3) << setfill('0') << address - script;
		else return out << "@???";
	}
	
	// A tuple is expressed as a space seperated list between square brackets.
	ostream & operator << (ostream & out, Tuple const & tuple) {
		out << '[';
		for(size_t i = 0; i < tuple.size(); i++){
			if (i) out << ' ';
			out << tuple[i];
		}
		out << ']';
		return out;
	}
	
	// The way data is expressed depends on its type.
	ostream & operator << (ostream & out, Data const & data) {
		switch(data.type()){
			case Data::Type_number   : out << data.asNumber (); break;
			case Data::Type_address  : out << data.asAddress(); break;
			case Data::Type_tuple    : out << data.asTuple  (); break;
			case Data::Type_undefined: out << "undefined";
		}
		return out;
	}
	
	// A stack is expressed as a space seperated list.
	ostream & operator << (ostream & out, Stack<Data> const & stack) {
		stringstream s;
		for(size_t i = 0; i < stack.size(); i++){
			if (i) s << ' ';
			s << stack.peek(i);
		}
		out << setfill(' ') << setw(32) << right << s.str();
		return out;
	}

}

namespace {
	const char * instruction_names[256] = {
#		define INSTRUCTION(name) #name,
#		define INSTRUCTION_N(name,n) #name "_" #n,
#		include <delftproto.instructions>
#		undef INSTRUCTION
#		undef INSTRUCTION_N
	};
	
	// Show the name of the current instruction, along with the current state of the machine.
	// Waits for the user to press [enter] afterwards.
	void show_instruction(Machine & machine, string name){
		cout << machine.currentAddress();
		for(size_t i = 0; i < machine.depth(); i++) cout << " | ";
		cout << ' ' << setw(20 - machine.depth()*3) << setfill(' ') << left << name;
		cout << "  " << machine.stack << "  " << machine.environment << "  " << machine.globals;
		cout.flush();
		cin.ignore();
	}
	
	// Run the machine until the current script is finished executing.
	void debug_run(Machine & machine){
		while(!machine.finished()){
			show_instruction(machine,instruction_names[*machine.currentAddress()]);
			machine.step();
		}
	}
}

int main(){
	
	std::srand(time(0));
	
	cout << "<--------------------------------- Please make sure your terminal is at least 128 chars wide --------------------------------->" << endl << endl;
	cout << "@### INSTRUCTION           stack                             environment                       globals                         " << endl << endl;
	
	Machine machine;
	
	show_instruction(machine,"INSTALL");
	machine.install(script);
	debug_run(machine);
	
	while(true){
		show_instruction(machine,"RUN");
		machine.run();
		debug_run(machine);
	}
	
}
