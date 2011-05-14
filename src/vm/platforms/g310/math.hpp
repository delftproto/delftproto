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

extern "C" {
	float sin  (float x) asm("sinf");
	float cos  (float x) asm("cosf");
	float tan  (float x) asm("tanf");
	float sinh (float x) asm("__ieee754_sinhf");
	float cosh (float x) asm("__ieee754_coshf");
	float tanh (float x) asm("tanhf");
	float log  (float x) asm("logf");
	float sqrt (float x) asm("sqrtf");
	float asin (float x) asm("asinf");
	float acos (float x) asm("acosf");
	float atan (float x) asm("atanf");
	float atan2(float a, float b) asm("atan2f");
	float fmod (float a, float b) asm("fmodf");
	float pow  (float a, float b) asm("powf");
	float exp  (float x) asm("expf");
	float fabs (float x) asm("fabsf");
	float floor(float x) asm("floorf");
	float ceil (float x) asm("ceilf");
}
