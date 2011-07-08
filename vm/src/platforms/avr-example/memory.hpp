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

