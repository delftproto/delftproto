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
/// Provides the hood instructions

#include <machine.hpp>
#include <instructions.hpp>

class HoodInstructions {
	
	protected:
		
		static Index export_index;
		static Data * result;
		static Address filter;
		static Address fuse;
		
	public:
		
		static Data dummy_result;
		
		static void fold_hood(Machine & machine, Data & result) {
			Index export_index = machine.nextInt8();
			Data export_value = machine.stack.pop();
			result = machine.stack.pop();
			Address fuse = machine.stack.popAddress();
			
			HoodInstructions::export_index = export_index;
			HoodInstructions::result = &result;
			HoodInstructions::fuse = fuse;
			
			machine.thisMachine().imports[export_index] = export_value;
			
			machine.current_neighbour = machine.hood.begin();
			
			machine.environment.push(result);
			machine.environment.push(export_value);
			machine.call(fuse,fold_hood_step);
		}
		
		static void fold_hood_step(Machine & machine) {
			machine.environment.pop(2);
			*result = machine.stack.pop();
			if (++machine.current_neighbour != machine.hood.end()){
				machine.environment.push(*result);
				machine.environment.push(machine.current_neighbour->imports[export_index]);
				machine.call(fuse,fold_hood_step);
			} else {
				machine.stack.push(*result);
			}
		}
		
		static void fold_hood_plus(Machine & machine, Data & result) {
			Index export_index = machine.nextInt8();
			Data export_value = machine.stack.pop();
			Address filter = machine.stack.popAddress();
			Address fuse = machine.stack.popAddress();
			
			HoodInstructions::export_index = export_index;
			HoodInstructions::result = &result;
			HoodInstructions::filter = filter;
			HoodInstructions::fuse = fuse;
			
			machine.thisMachine().imports[export_index] = export_value;
			
			machine.current_neighbour = machine.hood.begin();
			
			machine.environment.push(export_value);
			machine.call(filter,fold_hood_plus_first_filter);
		}
		
		static void fold_hood_filter_next(Machine & machine){
			*result = machine.stack.pop();
			if (++machine.current_neighbour != machine.hood.end()){
				machine.environment.push(machine.current_neighbour->imports[export_index]);
				machine.call(filter,fold_hood_plus_step_filter);
			} else {
				machine.stack.push(*result);
			}
		}
		
		static void fold_hood_plus_first_filter(Machine & machine){
			machine.environment.pop(1);
			fold_hood_filter_next(machine);
		}
		
		static void fold_hood_plus_step_filter(Machine & machine){
			machine.environment.pop(1);
			Data import = machine.stack.pop();
			machine.environment.push(*result);
			machine.environment.push(import);
			machine.call(fuse,fold_hood_plus_step_fuse);
		}
		
		static void fold_hood_plus_step_fuse(Machine & machine){
			machine.environment.pop(2);
			fold_hood_filter_next(machine);
		}
		
};

Index   HoodInstructions::export_index;
Data *  HoodInstructions::result;
Address HoodInstructions::filter;
Address HoodInstructions::fuse;
Data    HoodInstructions::dummy_result;

namespace Instructions {
	
	/// \name Hood instructions
	/// \{
	
	/// Fold all imported values for a specific neighbourhood variable and update the corresponding export.
	/**
	 * The fuse function is used to consecutively fuse the previous fuse result with the import value of the next neighbour.
	 * The import value from the first neighbour (ie. this machine) will be fused with the given starting value.
	 * 
	 * The value of the neighbour hood variable (ie. export) of this machine is set before the folding process starts.
	 * 
	 * For example, a neighbourhood with three neighbours (including this machine) is folded like this:
	 * \dot
	 * digraph Folding {
	 *   node [fontsize=10,width=0,height=0];
	 *   start -> a -> b -> c -> result;
	 *   "new export value" -> "export of this machine" -> a;
	 *   "import of neighbour 1" -> b;
	 *   "import of neighbour 2" -> c;
	 *   a [shape=box,label=fuse];
	 *   b [shape=box,label=fuse];
	 *   c [shape=box,label=fuse];
	 * }
	 * \enddot
	 * 
	 * \deprecated Implemented for MIT Proto compatibility.
	 * \note There is currently no way of doing this without using deprecated instructions. (This will be fixed soon.)
	 * 
	 * \param Int8 The index of the neighbourhood (ie. import/export) variable.
	 * \param Address The (address of the) fuse function. (The fold function must take two parameters.)
	 * \param Data The value to start with.
	 * \param Data The new export value for this Machine.
	 * 
	 * \return Data the result of the folding process.
	 */
	void FOLD_HOOD(Machine & machine){
		HoodInstructions::fold_hood(machine,HoodInstructions::dummy_result);
	}
	
	/// \deprecated_mitproto
	void VFOLD_HOOD(Machine & machine){
		Data & result = machine.globals[machine.nextInt8()];
		HoodInstructions::fold_hood(machine,result);
	}
	
	/// Filter and fold all imported values for a specific neighbourhood variable and update the corresponding export.
	/**
	 * The fuse function is used to consecutively fuse the previous fuse result with result of the filter applied to the import value of the next neighbour.
	 * 
	 * The value of the neighbour hood variable (ie. export) of this machine is set before the folding process starts.
	 * 
	 * For example, a neighbourhood with three neighbours (including this machine) is folded like this:
	 * \dot
	 * digraph Folding {
	 *   node [fontsize=10,width=0,height=0];
	 *   "new export value" -> "export of this machine" -> x -> b -> c -> result;
	 *   "import of neighbour 1" -> y -> b;
	 *   "import of neighbour 2" -> z -> c;
	 *   b [shape=box,label=fuse];
	 *   c [shape=box,label=fuse];
	 *   x [shape=box,label=filter];
	 *   y [shape=box,label=filter];
	 *   z [shape=box,label=filter];
	 * }
	 * \enddot
	 * 
	 * \deprecated Implemented for MIT Proto compatibility.
	 * \note There is currently no way of doing this without using deprecated instructions. (This will be fixed soon.)
	 * 
	 * \param Int8 The index of the neighbourhood (ie. import/export) variable.
	 * \param Address The (address of the) fuse function. (The fold function must take two parameters.)
	 * \param Address The (address of the) filter function. (The filter function must take one parameter.)
	 * \param Data The new export value for this Machine.
	 * 
	 * \return Data the result of the folding process.
	 */
	void FOLD_HOOD_PLUS(Machine & machine){
		HoodInstructions::fold_hood_plus(machine,HoodInstructions::dummy_result);
	}
	
	/// \deprecated_mitproto
	void VFOLD_HOOD_PLUS(Machine & machine){
		Data & result = machine.globals[machine.nextInt8()];
		HoodInstructions::fold_hood_plus(machine,result);
	}
	
	/// \}
	
}
