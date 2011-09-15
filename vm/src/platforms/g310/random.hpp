/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <stdlib.h>

#ifndef __RANDOM_HPP
#define __RANDOM_HPP

#include <types.hpp>

class Random {
	public:
		static Number number(Number min, Number max) {
			return Number(rand()) / Number(RAND_MAX) * (max - min) + min;
		}
};

#endif
