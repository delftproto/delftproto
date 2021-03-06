/*   ____       _  __ _   ____            _
 *  |  _ \  ___| |/ _| |_|  _ \ _ __ ___ | |_ ___
 *  | | | |/ _ \ | |_| __| |_) | '__/ _ \| __/ _ \
 *  | |_| |  __/ |  _| |_|  __/| | ( (_) | |( (_) )
 *  |____/ \___|_|_|  \__|_|   |_|  \___/ \__\___/
 *
 * This file is part of DelftProto.
 * See COPYING for license details.
 */

#include <types.hpp>

class CtrlCTriggeredThread : public Thread {
	
	public:
		bool ctrl_c_triggered;
		CtrlCTriggeredThread() : ctrl_c_triggered(false) {}
		
};

#undef  Thread
#define Thread CtrlCTriggeredThread
