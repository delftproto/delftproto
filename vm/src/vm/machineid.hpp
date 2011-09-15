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
/// Provides the MachineId class.

#ifndef __MACHINEID_HPP
#define __MACHINEID_HPP

/// An unique Machine ID.
/**
 * This is just a dummy implementation for which every ID is equal.
 * Platform specific code should have the 'real' implementation of this class.
 * 
 * It should initialize itself to something unique, and have == and != operators.
 */
class MachineId {
	
	public:
		
		bool operator == (MachineId const & m) const {
			return true;
		}
		
		bool operator != (MachineId const & m) const {
			return false;
		}
		
};

#endif
