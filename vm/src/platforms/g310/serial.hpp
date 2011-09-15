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
