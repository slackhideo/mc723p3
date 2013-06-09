/**
 * @file      mc723_func_unit.cpp
 * @author    Grupo 40 - MC723 - 1s2013
 *
 * @version   0.1
 *
 * @brief     Implements a function calculator unit.
 *
 *
 *   How to calculate log10(n):
 *      write n to the address 5242888
 *      wait till the value on the address 5242884 become 1
 *      read the result at the address 5242896
 *
 *
 *   This library is free software; you can redistribute it and/or
 *   modify it under the terms of the GNU Lesser General Public
 *   License as published by the Free Software Foundation; either
 *   version 2.1 of the License, or (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *   Lesser General Public License for more details.
 *
 *
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
#include <math.h>
// SystemC includes
// ArchC includes

#include "mc723_func_unit.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate locker from ArchC
using user::mc723_func_unit;

/// Constructor
mc723_func_unit::mc723_func_unit( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

}

/// Destructor
mc723_func_unit::~mc723_func_unit() {
}

/// Calculates the log10 of a given argument
void mc723_func_unit::calculateLog10(float &d) {
    result = (float) log10 ((double) d);
}

void mc723_func_unit::write( const float &d ) {
    argument_value.i = d;
    exchange_endian (argument_value.c);
    calculateLog10(argument_value.i);
}

void mc723_func_unit::read( float &d ) {
    argument_value.i = result;
    exchange_endian (argument_value.c);
    d = argument_value.i;
}


