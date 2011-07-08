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
/// Provides the special form instructions.

#include <machine.hpp>
#include <instructions.hpp>
#include <tuple.hpp>

namespace Instructions {
	
	/// \name Special form instructions
	/// \{
	
	namespace {
		void apply_end(Machine & machine){
			Data result = machine.stack.pop();
			Tuple arguments = machine.stack.popTuple();
			machine.stack.popAddress();
			machine.stack.push(result);
			machine.environment.pop(arguments.size());
		}
	}
	
	/// Call a function.
	/**
	 * \param Address The (address of the) function to call.
	 * \param Tuple The arguments to give to the function.
	 * \return Data The return value of the function.
	 */
	void APPLY(Machine & machine){
		Tuple arguments  = machine.stack.peek(0).asTuple();
		Address function = machine.stack.peek(1).asAddress();
		for(Index i = 0; i < arguments.size(); i++) machine.environment.push(arguments[i]);
		machine.call(function, apply_end);
	}
	
	namespace {
		Tuple map_values;
		Address map_function;
		Tuple * map_result;
		Index map_index;
		
		void map_step(Machine & machine){
			machine.environment.pop(1);
			if (map_result == &map_values) {
				(*map_result)[map_index] = machine.stack.pop();
			} else {
				map_result->push(machine.stack.pop());
			}
			if (++map_index < map_values.size()){
				machine.environment.push(map_values[map_index]);
				machine.call(map_function, map_step);
			}
		}
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Map all elements of a Tuple using a function.
	/**
	 * The given function will be called for every element in the tuple.
	 * The elements will be replaced by the corresponding return value of the function.
	 * 
	 * \param Address The (address of the) function to call.
	 * \param Tuple The tuple of which the elements wil be mapped.
	 * 
	 * \return Tuple The tuple with all the mapped elements.
	 */
	void TUP_MAP(Machine & machine){
		map_values = machine.stack.popTuple();
		map_function = machine.stack.popAddress();
		if (map_values.instances() == 1){
			map_result = &map_values;
			machine.stack.push(map_values);
		} else {
			machine.stack.push(Tuple(map_values.size()));
			map_result = &machine.stack.peek().asTuple();
		}
		map_index = 0;
		if (!map_values.empty()){
			machine.environment.push(map_values[0]);
			machine.call(map_function, map_step);
		}
	}
#endif
	
#if MIT_COMPATIBILITY != NO_MIT
	/// \deprecated_mitproto{TUP_MAP}
	void MAP(Machine & machine){
		map_result = &machine.globals[machine.nextInt8()].asTuple();
		map_values = machine.stack.popTuple();
		map_function = machine.stack.popAddress();
		*map_result = Tuple(map_values.size());
		machine.stack.push(*map_result);
		map_index = 0;
		if (!map_values.empty()){
			machine.environment.push(map_values[0]);
			machine.call(map_function, map_step);
		}
	}
#endif
	
	namespace {
		Tuple fold_values;
		Index fold_index;
		Data * fold_result;
		Address fold_fuse;
		Data fold_dummy_result;
		
		void fold_step(Machine & machine);
		
		void fold(Machine & machine, Data & result) {
			fold_values = machine.stack.popTuple();
			result = machine.stack.pop();
			Address fuse = machine.stack.popAddress();
			
			fold_index = 0;
			fold_result = &result;
			fold_fuse = fuse;
			
			if (fold_values.empty()){
				machine.stack.push(*fold_result);
			} else {
				machine.environment.push(*fold_result);
				machine.environment.push(fold_values[0]);
				machine.call(fold_fuse, fold_step);
			}
		}
		
		void fold_step(Machine & machine) {
			machine.environment.pop(2);
			*fold_result = machine.stack.pop().copy();
			if (++fold_index < fold_values.size()){
				machine.environment.push(*fold_result);
				machine.environment.push(fold_values[fold_index]);
				machine.call(fold_fuse, fold_step);
			} else {
				machine.stack.push(*fold_result);
			}
		}
	}
	
	/// Fold a Tuple to a single element with a given 'fuse function'.
	/**
	 * The fuse function is used to consecutively fuse the previous fuse result with the next element of the Tuple.
	 * The first element will be fused with the given starting value.
	 * 
	 * For example, a tuple with three elements is folded like this:
	 * \dot
	 * digraph Folding {
	 *   node [fontsize=10,width=0,height=0];
	 *   start -> a -> b -> c -> result;
	 *   "first element" -> a;
	 *   "second element" -> b;
	 *   "third element" -> c;
	 *   a [shape=box,label=fuse];
	 *   b [shape=box,label=fuse];
	 *   c [shape=box,label=fuse];
	 * }
	 * \enddot
	 * 
	 * If an empty Tuple is given, the starting value is returned.
	 * 
	 * \param Address The (address of the) fuse function. (The fold function must take two parameters.)
	 * \param Data The value to start with.
	 * \param Tuple The tuple to fold.
	 * 
	 * \return Data the result of the folding process.
	 */
	void FOLD(Machine & machine){
		fold(machine, fold_dummy_result);
	}
	
	/// \deprecated_mitproto{FOLD}
	void VFOLD(Machine & machine){
		fold(machine, machine.globals[machine.nextInt8()]);
	}
	
	/// \}
	
}
