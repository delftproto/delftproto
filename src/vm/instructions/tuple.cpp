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
/// Provides the Tuple instructions.

#include <machine.hpp>
#include <instructions.hpp>

namespace {
	inline int compareVectors(Tuple const & a, Tuple const & b){
		Size size = a.size() > b.size() ? a.size() : b.size();
		for(Index i = 0; i < size; i++){
			Number a_element = i < a.size() ? a[i].asNumber() : 0;
			Number b_element = i < b.size() ? b[i].asNumber() : 0;
			if      (a_element < b_element) return -1;
			else if (a_element > b_element) return  1;
		}
		return 0;
	}
	int compareVectors(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		return compareVectors(a,b);
	}
}

namespace Instructions {
	
	/// \name Tuple instructions
	/// \{
	
	/// Get an element from a Tuple.
	/**
	 * \param Tuple The tuple to pick the element from.
	 * \param Number The index of the element.
	 * \return Data The element.
	 */
	void ELT(Machine & machine){
		Index element = machine.stack.popNumber();
		Tuple  tuple  = machine.stack.popTuple ();
		machine.stack.push(tuple[element]);
	}
	
	/// An empty tuple.
	/**
	 * \return Tuple An empty tuple.
	 */
	void NUL_TUP(Machine & machine){
		machine.stack.push(Tuple());
	}
	
#if MIT_COMPATIBILITY != NO_MIT
	/// \deprecated_mitproto{FAB_TUP}
	void TUP(Machine & machine){
		Index index = machine.nextInt8();
		Size elements = machine.nextInt8();
		for(Index i = 0; i < elements; i++) machine.globals[index].asTuple()[i] = machine.stack.peek(elements-1-i);
		machine.stack.pop(elements);
		machine.stack.push(machine.globals[index]);
	}
#endif
	
	/// Create a tuple from one or more elements.
	/**
	 * \param Int8 The number of elements.
	 * \param Data <tt>[n]</tt> The elements.
	 * \return Tuple A tuple containing the elements.
	 */
	void FAB_TUP(Machine & machine){
		Size elements = machine.nextInt8();
		Tuple tuple(elements);
		for(Index i = 0; i < elements; i++) tuple.push(machine.stack.peek(elements-i-1));
		machine.stack.pop(elements);
		machine.stack.push(tuple);
	}
	
	/// Create a tuple filled with one element.
	/**
	 * \param Int8 The number of elements in the resulting tuple.
	 * \param Data The element to fill the tuple with.
	 * \return Tuple A tuple filled with the specified element.
	 */
	void FAB_VEC(Machine & machine){
		Size elements = machine.nextInt8();
		Tuple tuple(elements);
		Data element = machine.stack.pop();
		for(Index i = 0; i < elements; i++) tuple.push(element);
		machine.stack.push(tuple);
	}
	
	/// Create a tuple filled with zero's.
	/**
	 * \param Int8 The number of zero's to put in the tuple.
	 * \return Tuple A tuple filled with zero's.
	 */
	void FAB_NUM_VEC(Machine & machine){
		Size elements = machine.nextInt8();
		Tuple tuple(elements);
		for(Index i = 0; i < elements; i++) tuple.push(0);
		machine.stack.push(tuple);
	}
	
	/// Get the number of elements in a tuple.
	/**
	 * \param Tuple The tuple.
	 * \return Number The number of elements in the tuple.
	 */
	void LEN(Machine & machine){
		machine.stack.push(machine.stack.popTuple().size());
	}
	
#if MIT_COMPATIBILITY != NO_MIT
	/// \deprecated_mitproto{VEC_ADD}
	void VADD(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size = a.size() < b.size() ? a.size() : b.size();
		Size max_size = a.size() < b.size() ? b.size() : a.size();
		Tuple & largest = a.size() < b.size() ? b : a;
		Tuple & result = machine.globals[machine.nextInt8()].asTuple() = Tuple(max_size);
		for(Index i = 0       ; i < min_size; i++) result.push(a[i].asNumber() + b[i].asNumber());
		for(Index i = min_size; i < max_size; i++) result.push(largest[i].asNumber());
		machine.stack.push(result);
	}
	
	/// \deprecated_mitproto{VEC_SUB}
	void VSUB(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size     = a.size() < b.size() ? a.size() : b.size();
		Size max_size     = a.size() < b.size() ? b.size() : a.size();
		Tuple & largest     = a.size() < b.size() ? b        : a       ;
		Number padding_sign = a.size() < b.size() ? -1       : 1       ;
		Tuple & result = machine.globals[machine.nextInt8()].asTuple() = Tuple(max_size);
		for(Index i = 0       ; i < min_size; i++) result.push(a[i].asNumber() - b[i].asNumber());
		for(Index i = min_size; i < max_size; i++) result.push(padding_sign * largest[i].asNumber());
		machine.stack.push(result);
	}
	
	/// \deprecated_mitproto{VEC_DOT}
	void VDOT(Machine & machine){
		Number result = 0;
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size = a.size() < b.size() ? a.size() : b.size();
		for(Index i = 0; i < min_size; i++) result += a[i].asNumber() * b[i].asNumber();
		machine.stack.push(result);
	}
	
	/// \deprecated_mitproto{VEC_MUL}
	void VMUL(Machine & machine){
		Tuple & result = machine.globals[machine.nextInt8()].asTuple() = Tuple();
		Tuple  b = machine.stack.popTuple ();
		Number a = machine.stack.popNumber();
		for(Index i = 0; i < b.size(); i++) result.push(a * b[i].asNumber());
		machine.stack.push(result);
	}
	
	/// \deprecated_mitproto
	void VSLICE(Machine & machine){
		Tuple & result = machine.globals[machine.nextInt8()].asTuple() = Tuple();
		Tuple source = machine.stack.popTuple();
		Index start = machine.stack.popNumber();
		Index stop  = machine.stack.popNumber();
		start = start >= 0 ? start : source.size() + start;
		stop  = stop  >= 0 ? stop  : source.size() + stop ;
		for(Index i = start; i < stop; i++) result.push(source[i].asNumber());
		machine.stack.push(result);
	}
#endif
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Element wise addition of two numeric tuples.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Tuple The result of an element wise addition.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VEC_ADD(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size = a.size() < b.size() ? a.size() : b.size();
		Size max_size = a.size() < b.size() ? b.size() : a.size();
		Tuple & largest = a.size() < b.size() ? b : a;
		Tuple result(max_size);
		for(Index i = 0       ; i < min_size; i++) result.push(a[i].asNumber() + b[i].asNumber());
		for(Index i = min_size; i < max_size; i++) result.push(largest[i].asNumber());
		machine.stack.push(result);
	}
	
	/// Element wise subtraction of two numeric tuples.
	/**
	 * \param Tuple The numeric tuple to substract from.
	 * \param Tuple The numeric tuple to substract.
	 * 
	 * \return Tuple The result of an element wise subtraction.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VEC_SUB(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size     = a.size() < b.size() ? a.size() : b.size();
		Size max_size     = a.size() < b.size() ? b.size() : a.size();
		Tuple & largest     = a.size() < b.size() ? b        : a       ;
		Number padding_sign = a.size() < b.size() ? -1       : 1       ;
		Tuple result(max_size);
		for(Index i = 0       ; i < min_size; i++) result.push(a[i].asNumber() - b[i].asNumber());
		for(Index i = min_size; i < max_size; i++) result.push(padding_sign * largest[i].asNumber());
		machine.stack.push(result);
	}
	
	/// Dot product of two numeric tuples.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number The result of the dot product.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VEC_DOT(Machine & machine){
		Number result = 0;
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		Size min_size = a.size() < b.size() ? a.size() : b.size();
		for(Index i = 0; i < min_size; i++) result += a[i].asNumber() * b[i].asNumber();
		machine.stack.push(result);
	}
	
	/// Element wise multiplication of two numeric tuples.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Tuple The result of an element wise multiplication.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VEC_MUL(Machine & machine){
		Tuple & result = machine.globals[machine.nextInt8()].asTuple() = Tuple();
		Tuple  b = machine.stack.popTuple ();
		Number a = machine.stack.popNumber();
		for(Index i = 0; i < b.size(); i++) result.push(a * b[i].asNumber());
		machine.stack.push(result);
	}
#endif
	
	/// Check if two numeric tuples are equal.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 1 when the elements in the tuples are equal, 0 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VEQ(Machine & machine){
		machine.stack.push(compareVectors(machine) == 0 ? 1 : 0);
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Check if two numeric vectors are unequal.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 0 when the elements in the tuples are equal, 1 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VNEQ(Machine & machine){
		machine.stack.push(compareVectors(machine) != 0 ? 1 : 0);
	}
#endif
	
	/// Check if a numeric tuple is (lexicographical) less than another.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 1 when when the first tuple is lexicographical less than the second, 0 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VLT(Machine & machine){
		machine.stack.push(compareVectors(machine) < 0 ? 1 : 0);
	}
	
	/// Check if a numeric tuple is (lexicographical) less than or equal to another.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 1 when when the first tuple is lexicographical less than or equal to the second, 0 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VLTE(Machine & machine){
		machine.stack.push(compareVectors(machine) <= 0 ? 1 : 0);
	}
	
	/// Check if a numeric tuple is (lexicographical) greater than another.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 1 when when the first tuple is lexicographical greater than the second, 0 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VGT(Machine & machine){
		machine.stack.push(compareVectors(machine) > 0 ? 1 : 0);
	}
	
	/// Check if a numeric tuple is (lexicographical) greater than or equal to another.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Number 1 when when the first tuple is lexicographical greater than or equal to the second, 0 otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VGTE(Machine & machine){
		machine.stack.push(compareVectors(machine) >= 0 ? 1 : 0);
	}
	
	/// Pick the (lexicographical) smallest numeric tuple.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Tuple The first tuple when when that tuple is lexicographical less than or equal to the other, the second one otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VMIN(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		machine.stack.push(compareVectors(a,b) <= 0 ? a : b);
	}
	
	/// Pick the (lexicographical) biggest numeric tuple.
	/**
	 * \param Tuple The first numeric tuple.
	 * \param Tuple The second numeric tuple.
	 * 
	 * \return Tuple The first tuple when when that tuple is lexicographical greater than or equal to the other, the second one otherwise.
	 * 
	 * If one of the tuples is shorter, the remaining of the elements will be interpreted as 0.
	 */
	void VMAX(Machine & machine){
		Tuple b = machine.stack.popTuple();
		Tuple a = machine.stack.popTuple();
		machine.stack.push(compareVectors(a,b) >= 0 ? a : b);
	}
	
	/// \}
	
}
