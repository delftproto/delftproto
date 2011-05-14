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

/// \file
/// Provides the Memory class.

#include <new>

#ifndef __MEMORY_HPP
#define __MEMORY_HPP

#include <types.hpp>

/// An interface to the memory (de)allocation functions.
/**
 * \tparam Element The type of the element(s) to (de)allocate.
 */
template<typename Element>
class Memory {
	public:
		
		/// Allocate memory.
		/**
		 * Allocate memory to hold a number of Elements.
		 * 
		 * \param capacity The number of Elements, or one when omitted.
		 * 
		 * \return A pointer to the allocated memory.
		 * 
		 * \warning This does not construct the element(s).
		 * Use the placement new operator to do it yourself:
		 * \code
		 * Thing * t = Memory<Thing>::allocate();
		 * new (t) Thing();
		 * \endcode
		 */
		static inline Element * allocate(Size capacity = 1) {
			return static_cast<Element *>(operator new [] (capacity * sizeof(Element)));
		}
		
		/// Deallocate memory.
		/**
		 * Deallocate memory previously allocated by Memory::allocate.
		 * 
		 * \param memory A pointer to the to be deallocated memory.
		 * \param capacity The number of elements that were allocated by Memory::allocate, or one when omitted.
		 *
		 * \warning This does not deconstruct the element(s).
		 * You have to call the deconstructor(s) yourself:
		 * \code
		 * t->~Thing();
		 * Memory<Thing>::deallocate(t);
		 * \endcode
		 */
		static inline void deallocate(Element * memory, Size capacity = 1) {
			operator delete [] (memory);
		}
		
};

#endif
