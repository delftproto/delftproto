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

/** \file
 * \brief Provides the \ref Instructions "Instruction" implementations.
 * 
 * This file includes the source files in the folder <tt>instructions/</tt>,
 * and then defines the \ref instructions lookup table,
 * to make sure the all the used template functions are instantiated.
 */

#include <instructions.hpp>

#include <instructions/flow.cpp>
#include <instructions/environment.cpp>
#include <instructions/globals.cpp>
#include <instructions/threads.cpp>
#include <instructions/literals.cpp>
#include <instructions/math.cpp>
#include <instructions/tuple.cpp>
#include <instructions/specialform.cpp>
#include <instructions/feedback.cpp>
#include <instructions/hood.cpp>
#include <instructions/platform.cpp>

/// \cond
Instruction instructions[256] = {
#	define INSTRUCTION(name) Instructions::name,
#	define INSTRUCTION_N(name,n) Instructions::name##_N<n>,
#	include <delftproto.instructions>
#	undef INSTRUCTION
#	undef INSTRUCTION_N
};
/// \endcond
