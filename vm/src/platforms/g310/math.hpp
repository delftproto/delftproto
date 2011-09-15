/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

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
