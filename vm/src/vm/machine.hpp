/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

/// \file
/// Provides the Machine class.

#ifndef __MACHINE_HPP
#define __MACHINE_HPP

#include <types.hpp>
#include <data.hpp>
#include <stack.hpp>
#include <state.hpp>
#include <script.hpp>
#include <thread.hpp>
#include <neighbour.hpp>
#include <neighbourhood.hpp>
#include <instructions.hpp>
#include <machineid.hpp>

class BasicMachine {
	
	public:
		
		/// The ID of this Machine.
		/** \memberof Machine */
		MachineId id;
		
		/// The standard stack.
		/** \memberof Machine */
		Stack<Data> stack;
		
		/// The environment stack.
		/** \memberof Machine */
		Stack<Data> environment;
		
		/// The globals.
		/** \memberof Machine */
		Stack<Data> globals;
		
		/// The threads.
		/**
		 * \see Thread
		 */
		/** \memberof Machine */
		Array<Thread> threads;
		
		/// The state variables.
		/** \memberof Machine */
		Array<State> state;
		
		/// The list of all the neighbours.
		/** \memberof Machine */
		NeighbourHood hood;
		
	protected:
		
		/// A pointer to the next instruction.
		/** \memberof Machine */
		Address instruction_pointer;
		
		/// Boolean indicating whether execution (installation or a single run) has finished.
		/** \memberof Machine */
		bool is_finished;
		
		/// The callback stack.
		/**
		 * \see call
		 * \see retn
		 */
		/** \memberof Machine */
		Stack<Instruction> callbacks;
		
		/// The (index of the) current thread when executing a run.
		/**
		 * When not running, this is the index of the thread that will be checked first for the next run.
		 */
		/** \memberof Machine */
		Thread::Id current_thread;
		
		/// The current neighbour, when iterating through them.
		/**
		 * Used by the hood instructions when iterating through the hood to let the neighbour-instructions know which neighbour is currently being processed.
		 */
		/** \memberof Machine */
		NeighbourHood::iterator current_neighbour;
		
		/// The (index of the) current import/export, when executing a hood instruction.
		/**
		 * Used by the hood folding instructions.
		 */
		/** \memberof Machine */
		Index current_import;
		
	public:
		
		/// The constructor.
		BasicMachine() : instruction_pointer(0), callbacks(1) {}
		
		/// \name Control flow
		/// \{
			
			/// Jump to another address.
			/**
			 * \param address The address to jump to.
			 */
			/** \memberof Machine */
			inline void jump(Address address) {
				instruction_pointer = address;
			}
			
			/// Advance the instruction pointer.
			/**
			 * \param distance The number of bytes to skip.
			 */
			/** \memberof Machine */
			inline void skip(Size distance) {
				instruction_pointer += distance;
			}
			
			/// Get the current address (instruction pointer).
			/** \memberof Machine */
			inline Address currentAddress() const {
				return instruction_pointer;
			}
			
			/// Get the callback depth.
			/**
			 * Usually 1, but higher inside instructions such as \ref Instructions::INIT_FEEDBACK "INIT_FEEDBACK" or \ref Instructions::TUP_MAP "TUP_MAP".
			 */
			/** \memberof Machine */
			inline Counter depth() const {
				return callbacks.size();
			}
			
			/// Get the (index of the) current thread when executing a run.
			/**
			 * When not running, this is the index of the thread that will be checked first for the next run.
			 */
			/** \memberof Machine */
			inline Thread::Id currentThread() const {
				return current_thread;
			}
			
		/// \}
		
		/// \name Low level
		/// \{
			
			/// Read the next byte(s) as an unsigned integer.
			/**
			 * Using the Variable Length Quantity (VLQ)
			 * format as used in the MIDI file format.
			 * 
			 * \see http://en.wikipedia.org/wiki/Variable-length_quantity
			 */
			/** \memberof Machine */
			inline Int nextInt() {
				Int value = 0;
				while(true){
					Int8 next = *instruction_pointer++;
					value |= next & 0x7F;
					if (next & 0x80) value <<= 7;
					else break;
				}
				return value;
			}
			
			/// Read the next byte as an unsigned 8-bit integer.
			/**
			 * \deprecated Use \ref Machine::nextInt() "nextInt()" instead.
			 */
			/** \memberof Machine */
			inline Int8 nextInt8() {
				return *instruction_pointer++;
			}
			
			/// Read the next two bytes as an unsigned 16-bit integer (big endian).
			/**
			 * \deprecated Use \ref Machine::nextInt() "nextInt()" instead.
			 */
			/** \memberof Machine */
			inline Int16 nextInt16() {
				Int16 data  = static_cast<Int16>(nextInt8()) << 8;
				      data += nextInt8();
				return data;
			}
			
		/// \}
		
		/// \name Neighbour methods
		/// \{
			
			/// Get the current neighbour, when iterating through them.
			/**
			 * Used by the hood instructions when iterating through the hood to let the neighbour-instructions know which neighbour is currently being processed.
			 */
			/** \memberof Machine */
			inline Neighbour & currentNeighbour() {
				return *current_neighbour;
			}
			
			/// Get the Neighbour representing this machine.
			/** \memberof Machine */
			inline Neighbour & thisMachine() {
				return *hood.begin();
			}
			
		/// \}
};

/** \cond */
#define Machine BasicMachine
#include <extensions.hpp>
typedef Machine ExtendedMachine;
#undef Machine
/** \endcond */

/// A virtual machine.
/**
 * \note This class is \ref extending "extensible".
 * 
 * \extends BasicMachine
 */
class Machine : public ExtendedMachine {
	
	public:
		/// \name Execution control
		/// \{
			
			/// Start an installation script.
			/**
			 * \note This does not execute the installation script, it only prepares it. Call step() while not finished() to execute it.
			 * 
			 * \param script A pointer to the installation script.
			 */
			inline void install(Int8 const * script) {
				is_finished = false;
				jump(Address(script));
				callbacks.push(0);
			}
			
			/// Start the next scheduled task.
			/**
			 * \note This does not execute Proto code, it only prepares the next run. Call step() while not finished() to execute it.
			 */
			inline void run() {
				is_finished = true;
				for(Size i = 0; i < threads.size(); i++){
					if (threads[current_thread].pending()){
						threads[current_thread].untrigger();
						jump(globals.peek(current_thread).asAddress());
						callbacks.push(run_callback);
						is_finished = false;
						return;
					}
					current_thread++;
					if (current_thread >= threads.size()) current_thread = 0;
				}
			}
			
			/** \cond */
		protected:
			static void run_callback(Machine & machine){
				machine.threads[machine.current_thread].result = machine.stack.pop();
				for(Size i = 0; i < machine.state.size(); i++){
					if (machine.state[i].thread == machine.current_thread){
						if (!machine.state[i].is_executed) machine.state[i].data.reset();
						machine.state[i].is_executed = false;
					}
				}
				machine.current_thread++;
				if (machine.current_thread >= machine.threads.size()) machine.current_thread = 0;
			}
			
			/** \endcond */
			
		public:
			/// Execute the next instruction.
			/**
			 * \note Do not use this function when already finished().
			 */
			inline void step() {
				execute(instructions[nextInt8()]);
			}
			
			/// Check whether the running script (installation or a single run) has finished (true) or not (false).
			inline bool finished() {
				return callbacks.empty();
			}
			
			/// Execute an instruction.
			/**
			 * \param instruction The Instruction to execute.
			 * 
			 * \see Instructions
			 */
			inline void execute(Instruction instruction) {
				instruction(*this);
			}
			
		/// \}
		
		/// \name Calling
		/// \{
			
			/// Call a function.
			/**
			 * \param address The address of the first instruction of the function.
			 * \param callback Called when the function returns.
			 */
			inline void call(Address address, Instruction callback = 0) {
				callbacks.push(callback);
				stack.push(instruction_pointer);
				jump(address);
			}
			
			/// Return from a function.
			/**
			 * If the corresponding call (if any) registered a callback, it will be called.
			 * 
			 * \see Instructions::RET
			 */
			inline void retn() {
				Instruction callback = callbacks.pop();
				Data result = stack.pop();
				if (!callbacks.empty()) jump(stack.popAddress());
				if (!(callbacks.empty() && !callback)) stack.push(result);
				if (callback) callback(*this);
			}
			
		/// \}
		
		friend void Instructions::DEF_VM(Machine &);
#if MIT_COMPATIBILITY != MIT_ONLY
		friend void Instructions::DEF_VM_EX(Machine &);
#endif
		friend void Instructions::EXIT(Machine &);
		friend class HoodInstructions;
		
};

#endif
