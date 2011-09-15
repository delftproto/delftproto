/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

/// \file
/// Provides the Script classs.

#ifndef __SCRIPT_HPP
#define __SCRIPT_HPP

#include <types.hpp>
#include <array.hpp>

/// A proto script (bytecode).
/**
 * /warning Currently not used, but will be used in the near future.
 */
class Script {
	
	public:
		Array<Int8> code;
		
};

#endif
