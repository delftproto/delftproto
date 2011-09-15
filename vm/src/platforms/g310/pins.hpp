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
