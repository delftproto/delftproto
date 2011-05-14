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
/// Provides the Address class

#ifndef __ADDRESS_HPP
#define __ADDRESS_HPP

#include <types.hpp>

/// An address of a constant series of bytes in memory.
/**
 * One of the types that can be stored in Data.
 * 
 * \note This is just a wrapper for an Int8 constant pointer, with an explicit constructor.
 *       This is useful, because \c 0 cannot be interpreted as an Address (unlike <tt>Int8 *</tt>),
 *       you have to explicitly say <tt>Address(0)</tt>.
 *       This makes something like \code Data d = 0; \endcode unambiguous.
 *       (It's interpreted as a Number, not an Address.)
 */
class Address {
	protected:
		Int8 const * address;
	public:
		inline explicit Address(Int8 const * const & address = 0) : address(address) {}
		inline operator Int8 const *       & ()       { return address; }
		inline operator Int8 const * const & () const { return address; }
};

#endif
