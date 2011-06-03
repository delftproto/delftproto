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
/// Provides the Array class.

#ifndef __ARRAY_HPP
#define __ARRAY_HPP

#include <types.hpp>
#include <memory.hpp>

/// A simple array.
/**
 * \tparam Element The type of elements stored in the array.
 */
template<typename Element> class Array {
	
	protected:
		
		/// The number of elements in the array.
		Size array_size;
		
		/// A pointer to the first element.
		Element * array;
		
	public:
		/// Allocate an array of the specified size, or an empty one when the size is omitted.
		/**
		 * All elements will be constructed with their default constructor.
		 */
		explicit Array(Size size = 0) : array(0) { reset(size); }
		
		/// Reset the array.
		/**
		 * All elements will be deconstructed and the array will be deallocated.
		 * If a new size is given, new elements will be allocated and constructed with their default constructor.
		 *
		 * \param new_size The new size of the array.
		 */
		inline void reset(Size new_size = 0) {
			if (array){
				for(Size i = 0; i < array_size; i++) array[i].~Element();
				Memory<Element>::deallocate(array,array_size);
			}
			array = new_size ? Memory<Element>::allocate(new_size) : 0;
			array_size = new_size;
			for(Size i = 0; i < array_size; i++) new (&array[i]) Element();
		}
		
		/// Clear the array.
		/**
		 * All elements will be reset to their default value.
		 */
		inline void clear() {
			for(Size i = 0; i < array_size; i++) array[i] = Element();
		}
		
		inline operator Element       * ()       { return array; } ///< Access the elements of the Array.
		inline operator Element const * () const { return array; } ///< Constant access to the elements of the Array. 
		
		/// The number of elements in the array.
		inline Size size() { return array_size; }
		
		/// Deconstruct the elements and deallocate the array.
		inline ~Array() { reset(); }
		
};

#endif
