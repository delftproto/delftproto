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
/// Provides the Neighbour class.

#ifndef __NEIGHBOUR_HPP
#define __NEIGHBOUR_HPP

#include <array.hpp>
#include <data.hpp>
#include <machineid.hpp>

class BasicNeighbour {
	
	public:
		/// The unique ID of the machine.
		/** \memberof Neighbour */
		MachineId const id;
		
		/// The imports from this machine.
		/** \memberof Neighbour */
		Array<Data> imports;
		
		BasicNeighbour(MachineId const & id, Size imports) : id(id), imports(imports) {}
		
};

/** \cond */
#define Neighbour BasicNeighbour
#include <extensions.hpp>
typedef Neighbour ExtendedNeighbour;
#undef Neighbour
/** \endcond */

/// A node in the neighbourhood.
/**
 * \note This class is \ref extending "extensible".
 * 
 * \note A machine is also a neighbour of itself.
 * \see Machine::thisMachine()
 */
class Neighbour : public ExtendedNeighbour {
	
	public:
		/// The constructor.
		Neighbour(MachineId const & id, Size imports) : ExtendedNeighbour(id, imports) {}
		
};

//asdf
#endif
