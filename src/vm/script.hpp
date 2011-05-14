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
