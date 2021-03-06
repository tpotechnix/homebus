/*
 * sysdef.h
 * 
 * Copyright 2013 Klaus Gusenleitner <klaus.gusenleitner@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */

#ifndef _SYSDEF_H
#define _SYSDEF_H

#include <time.h>

/*-----------------------------------------------------------------------------
*  Macros
*/                     

#ifndef max
#define max(x,y)            ((x) > (y) ? (x) : (y))
#endif
#ifndef min
#define min(x,y)            ((x) > (y) ? (y) : (x))
#endif

#define ARRAY_CNT(x)        (sizeof(x) / sizeof(x[0]))

#ifdef TIME_SIMULATION
extern uint16_t gTimeMs16;
#define GET_TIME_MS16(x) {                              \
	x = gTimeMs16;                                      \
}
extern uint16_t gTime10Ms16;
#define GET_TIME_10MS16(x) {                            \
	x = gTime10Ms16;                                    \
}
#else
/* 16 bit millisecond counter */
#define GET_TIME_MS16(x) {                              \
   struct timespec ts;                                  \
   clock_gettime(CLOCK_MONOTONIC, &ts);                 \
   x = (uint16_t)((unsigned long long)ts.tv_sec * 1000ULL + (unsigned long long)ts.tv_nsec / 1000000ULL); \
}
#endif
/*-----------------------------------------------------------------------------
*  typedefs
*/
typedef void (* TIdleStateFunc)(bool setIdle);

/*-----------------------------------------------------------------------------
*  Variables
*/                                

/*-----------------------------------------------------------------------------
*  Functions
*/
                            
#endif                            
