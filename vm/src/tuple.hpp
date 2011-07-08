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
/// Provides the Tuple class.

#ifndef __TUPLE_HPP
#define __TUPLE_HPP

#include <sharedvector.hpp>

class Data;

/** \class Tuple
 * \brief A SharedVector of Data.
 * 
 * One of the types that can be stored in Data.
 */
typedef SharedVector<Data> Tuple;

#endif
