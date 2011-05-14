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
/// Provides the math instructions.

#include <math.hpp>
#include <random.hpp>
#include <machine.hpp>
#include <instructions.hpp>

namespace Instructions {
	
	/// \name Comparison instructions
	/// \{
	
	/// Check if a Number is equal to another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a=b\\0&a\neq b\end{array}\right.}
	 */
	void EQ(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a == b ? 1 : 0);
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Check if a Number is not equal to another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a\neq b\\0&a=b\end{array}\right.}
	 */
	void NEQ(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a != b ? 1 : 0);
	}
#endif
	
	/// Check if a Number is less than another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a<b\\0&a\geq b\end{array}\right.}
	 */
	void LT(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a < b ? 1 : 0);
	}
	
	/// Check if a Number is less than or equal to another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a\leq b\\0&a>b\end{array}\right.}
	 */
	void LTE(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a <= b ? 1 : 0);
	}
	
	/// Check if a Number is greater than another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a>b\\0&a\leq b\end{array}\right.}
	 */
	void GT(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a > b ? 1 : 0);
	}
	
	/// Check if a Number is greater than or equal to another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\left\lbrace\begin{array}{ll}1&a\geq b\\0&a<b\end{array}\right.}
	 */
	void GTE(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a >= b ? 1 : 0);
	}
	
	/// \}
	
	/// \name Standard math operator instructions
	/// \{
	
	/// Add a Number to another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{a + b}
	 */
	void ADD(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a + b);
	}
	
	/// Subtract a Number from another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{a - b}
	 */
	void SUB(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a - b);
	}
	
	/// Multiply a Number with another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{a \cdot b}
	 */
	void MUL(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a * b);
	}
	
	/// Divide a Number by another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\frac a b}
	 */
	void DIV(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a / b);
	}
	
	/// \}
	
	/// \name Math function instructions
	/// \{
	
	/// Get the absolute value of a Number.
	/**
	 * \param Number \m{a}
	 * \return \m{|a|}
	 */
	void ABS(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(a < 0 ? -a : a);
	}
	
	/// Get the maximum of two \ref Number "Numbers".
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\max\lbrace a\,b\rbrace}
	 */
	void MAX(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a > b ? a : b);
	}
	
	/// get the minimum of two \ref Number "Numbers".
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{\min\lbrace a\,b\rbrace}
	 */
	void MIN(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(a < b ? a : b);
	}
	
	/// Get a Number to the power of another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{a^b}
	 */
	void POW(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(pow(a,b));
	}
	
#if MIT_COMPATIBILITY != MIT_ONLY
	/// Get the remainder of a Number divided by another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{x \equiv a \pmod{|b|}\,\quad \left\lbrace\begin{array}{ll} -|b| < x \leq 0 & a < 0 \\ 0 \leq x < |b| & a \geq 0 \end{array}\right.}
	 */
	void REM(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		machine.stack.push(fmod(a,b));
	}
#endif
	
	/// Get the (positive) remainder of a Number divided by another.
	/**
	 * \param Number \m{a}
	 * \param Number \m{b}
	 * \return \m{x \equiv a \pmod{|b|}\,\quad 0 \leq x < |b|}
	 */
	void MOD(Machine & machine){
		Number b = machine.stack.popNumber();
		Number a = machine.stack.popNumber();
		Number x = fmod(a,b);
		if (x < 0) x += b; // fmod gives the remainder, not the modulus.
		machine.stack.push(x);
	}
	
	/// Get the floor of a Number.
	/**
	 * \param Number \m{a}
	 * \return \m{\left\lfloor a \right\rfloor}
	 */
	void FLOOR(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(floor(a));
	}
	
	/// Get the ceiling of a Number.
	/**
	 * \param Number \m{a}
	 * \return \m{\left\lceil a \right\rceil}
	 */
	void CEIL(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(ceil(a));
	}
	
	/// Calculate the natural logarithm of a Number.
	/**
	 * \param Number \m{a}
	 * \return \m{\log_e a}
	 */
	void LOG(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(log(a));
	}
	
	/// Calculate the square root of a Number.
	/**
	 * \param Number \m{a}
	 * \return \m{\sqrt a}
	 */
	void SQRT(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(sqrt(a));
	}
	
	/// Calculate the sine of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\sin a}
	 */
	void SIN(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(sin(a));
	}
	
	/// Calculate the cosine of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\cos a}
	 */
	void COS(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(cos(a));
	}
	
	/// Calculate the tangent of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\tan a}
	 */
	void TAN(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(tan(a));
	}
	
	/// Calculate the hyperbolic sine of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\sinh a}
	 */
	void SINH(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(sinh(a));
	}
	
	/// Calculate the hyperbolic cosine of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\cosh a}
	 */
	void COSH(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(cosh(a));
	}
	
	/// Calculate the hyperbolic tangent of an angle.
	/**
	 * \param Number \m{a}
	 * \return \m{\tanh a}
	 */
	void TANH(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(tanh(a));
	}
	
	/// Calculate the angle of a sine.
	/**
	 * \param Number \m{a}
	 * \return \m{\arcsin a}
	 */
	void ASIN(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(asin(a));
	}
	
	/// Calculate the angle of a cosine.
	/**
	 * \param Number \m{a}
	 * \return \m{\arccos a}
	 */
	void ACOS(Machine & machine){
		Number a = machine.stack.popNumber();
		machine.stack.push(acos(a));
	}
	
	/// Calculate the angle of a tangent.
	/**
	 * \param Number \m{y}
	 * \param Number \m{x}
	 * \return \m{\arctan \frac y x}
	 */
	void ATAN2(Machine & machine){
		Number x = machine.stack.popNumber();
		Number y = machine.stack.popNumber();
		machine.stack.push(atan2(y,x));
	}
	
	/// Generate a (pseudo) random number.
	/**
	 * \param Number \m{min}
	 * \param Number \m{max}
	 * \return \m{x \sim U(min\,max)}
	 */
	void RND(Machine & machine){
		Number max = machine.stack.popNumber();
		Number min = machine.stack.popNumber();
		machine.stack.push(Random::number(min,max));
	}
	
	/// \}
	
}
