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
/// Provides the NeighbourList class.

#ifndef __NEIGHBOURLIST_HPP
#define __NEIGHBOURLIST_HPP

#include <memory.hpp>
#include <types.hpp>
#include <neighbour.hpp>

/// A list of Neighbours.
/**
 * This implements a doubly linked list.
 * Though, it could be replaced by any other implementation (raw array, tree set, etc.), as long as it has the same public interface.
 * 
 * \todo Add documentation and some examples.
 */
class NeighbourList {
	
	protected:
		
		struct NeighbourListElement {
			Neighbour neighbour;
			NeighbourListElement * next;
			NeighbourListElement * previous;
			inline NeighbourListElement(MachineId const & id, Size imports) : neighbour(id,imports), next(0), previous(0) {}
		};
		
		NeighbourListElement * first;
		
		Size list_size;
		
		Size imports;
		
	public:
		
		class iterator {
			protected:
				NeighbourListElement * element;
				inline iterator(NeighbourListElement * element) : element(element) {}
				friend class const_iterator;
				friend class NeighbourList;
			public:
				inline iterator & operator ++ (     ) {                     element = element->next    ; return *this; }
				inline iterator   operator ++ (int x) { iterator i = *this; element = element->next    ; return  i   ; }
				inline iterator & operator -- (     ) {                     element = element->previous; return *this; }
				inline iterator   operator -- (int x) { iterator i = *this; element = element->previous; return  i   ; }
				inline Neighbour & operator *  () const { return   element->neighbour ; }
				inline Neighbour * operator -> () const { return &(element->neighbour); }
				inline bool operator == (iterator const & i) const { return element == i.element; }
				inline bool operator != (iterator const & i) const { return element != i.element; }
				inline operator Neighbour * () const { return &(element->neighbour); }
		};
		
		class const_iterator {
			protected:
				NeighbourListElement const * element;
				inline const_iterator(NeighbourListElement const * element) : element(element) {}
				inline const_iterator(iterator const & i) : element(i.element) {}
				friend class NeighbourList;
			public:
				inline const_iterator & operator ++ (     ) {                           element = element->next    ; return *this; }
				inline const_iterator   operator ++ (int x) { const_iterator i = *this; element = element->next    ; return  i   ; }
				inline const_iterator & operator -- (     ) {                           element = element->previous; return *this; }
				inline const_iterator   operator -- (int x) { const_iterator i = *this; element = element->previous; return  i   ; }
				inline Neighbour const & operator *  () const { return   element->neighbour ; }
				inline Neighbour const * operator -> () const { return &(element->neighbour); }
				inline bool operator == (const_iterator const & i) const { return element == i.element; }
				inline bool operator != (const_iterator const & i) const { return element != i.element; }
				inline operator Neighbour const * () const { return &(element->neighbour); }
		};
		
		explicit NeighbourList(Size imports = 0) : first(0), list_size(0), imports(0) { reset(imports); }
		
		void reset(Size imports){
			iterator i = first;
			while(i != end()) i = remove(i);
			this->imports = imports;
		}
		
		inline       iterator begin()       { return first; }
		inline const_iterator begin() const { return first; }
		inline       iterator end  ()       { return 0    ; }
		inline const_iterator end  () const { return 0    ; }
		
		inline Neighbour const & operator [] (MachineId const & id) const {
			return *find(id);
		}
		
		inline Neighbour & operator [] (MachineId const & id) {
			iterator i = find(id);
			return *(i == end() ? add(id) : i);
		}
		
		inline iterator find(MachineId const & id) {
			for(iterator i = begin(); i != end(); i++) if (i->id == id) return i;
			return end();
		}
		
		inline const_iterator find(MachineId const & id) const {
			for(const_iterator i = begin(); i != end(); i++) if (i->id == id) return i;
			return end();
		}
		
		inline iterator add(MachineId const & id) {
			NeighbourListElement * n = Memory<NeighbourListElement>::allocate();
			new (n) NeighbourListElement(id,imports);
			if (first) first->previous = n;
			n->next = first;
			first = n;
			list_size++;
			return first;
		}
		
		inline iterator remove(iterator neighbour) {
			NeighbourListElement * n = neighbour.element;
			if (n->previous) n->previous->next = n->next;
			if (n->next    ) n->next->previous = n->previous;
			if (n == first) first = n->next;
			iterator next = n->next;
			n->~NeighbourListElement();
			Memory<NeighbourListElement>::deallocate(n);
			list_size--;
			return next;
		}
		
		inline Size size () const { return  list_size; }
		inline bool empty() const { return !list_size; }
		
};

#endif
