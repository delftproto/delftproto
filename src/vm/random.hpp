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
/// Provides the Random class.

#include <cstdlib>

#ifndef __RANDOM_HPP
#define __RANDOM_HPP

#include <types.hpp>

/// Pseudo random Number generator.
class Random {
	
	public:
		
		/// Get a random Number.
		/**
		 * The random Number is picked from an uniform distribution.
		 *
		 * \param min The minimum value.
		 * \param max The maximum value.
		 *
		 * \return A random Number between min and max.
		 */
		static Number number(Number min, Number max) {
			return Number(std::rand()) / Number(RAND_MAX) * (max - min) + min;
		}
		
};

#endif
