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

#ifndef __SERIAL_HPP
#define __SERIAL_HPP

#include "pins.hpp"

class Serial {
	protected:
		Pin<3,4> serialOutput;
		Pin<3,5> serialInput;
	public:
		inline Serial() {
			serialOutput.peripheral();
			serialInput.peripheral();
			UCA0CTL1 = UCSSEL_2;
			UCA0BR0 = 27;
			UCA0MCTL = UCBRS_2;
			UCA0CTL1 &= ~UCSWRST;
		}
		inline void put(char c) {
			while (!(IFG2 & UCA0TXIFG));
			UCA0TXBUF = c;
		}
		inline void put(char const * s) {
			while(char c = *s++) put(c);
		}
};

#endif
