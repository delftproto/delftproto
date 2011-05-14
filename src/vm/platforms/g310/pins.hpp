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

#ifndef __PINS_HPP
#define __PINS_HPP

#define portregister(port,register) \
	((port) == 1 ? P1##register : \
	 (port) == 2 ? P2##register : \
	 (port) == 3 ? P3##register : \
	               P4##register )

template<unsigned int port, unsigned int pin> struct Pin {
	inline Pin<port,pin> &       high() { portregister(port,OUT) |=   1 << pin ; return *this; }
	inline Pin<port,pin> &        low() { portregister(port,OUT) &= ~(1 << pin); return *this; }
	inline Pin<port,pin> &     toggle() { portregister(port,OUT) ^=   1 << pin ; return *this; }
	
	inline Pin<port,pin> &     output() { portregister(port,DIR) |=   1 << pin ; return *this; }
	inline Pin<port,pin> &      input() { portregister(port,DIR) &= ~(1 << pin); return *this; }
	
	inline Pin<port,pin> & peripheral() { portregister(port,SEL) |=   1 << pin ; return *this; }
	inline Pin<port,pin> &       gpio() { portregister(port,SEL) &= ~(1 << pin); return *this; }
	
	inline Pin<port,pin> &       pull() { portregister(port,REN) |=   1 << pin ; return *this; }
	inline Pin<port,pin> &     nopull() { portregister(port,REN) &= ~(1 << pin); return *this; }
	
	inline bool check() { return portregister(port,IN) & (1 << pin); }
	
	inline Pin<port,pin> & reset() { return gpio().input().nopull().low(); }
};

template<unsigned int port, unsigned int pin> struct InputPin : public Pin<port,pin> {
	inline InputPin() { Pin<port,pin>::gpio().input(); }
};

template<unsigned int port, unsigned int pin> struct OutputPin : public Pin<port,pin> {
	inline OutputPin() { Pin<port,pin>::gpio().output(); }
};

#endif
