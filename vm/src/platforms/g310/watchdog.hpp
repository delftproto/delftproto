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

#ifndef __WATCHDOG_HPP
#define __WATCHDOG_HPP

class Watchdog {
	public:
		inline Watchdog() {
			WDTCTL = WDTPW + WDTHOLD;
		}
};

#endif
