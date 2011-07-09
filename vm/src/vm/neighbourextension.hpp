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
/// Provides the \ref extending "Extension" to the Neighbour class.

/// \cond

#ifndef __NEIGHBOUREXTENSION_HPP
#define __NEIGHBOUREXTENSION_HPP

class NeighbourExtension_base {};
#define Neighbour NeighbourExtension_base
#include <extensions.hpp>
typedef Neighbour NeighbourExtension;
#undef Neighbour

#endif

/// \endcond
