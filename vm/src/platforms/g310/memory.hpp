/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

extern "C" {
#	include <stdlib.h>
}

#include <types.hpp>

#ifndef __MEMORY_HPP
#define __MEMORY_HPP

inline void * operator new (Size size, void * memory) { return memory; }

template<typename Element>
class Memory {
	public:
		
		static Element * allocate(Size capacity = 1) {
			return static_cast<Element *>(malloc(capacity * sizeof(Element)));
		}
		
		static void deallocate(Element * memory, Size capacity = 1) {
			free(static_cast<void *>(memory));
		}
		
};

#endif

