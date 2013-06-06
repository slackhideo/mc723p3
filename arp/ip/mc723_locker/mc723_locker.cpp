/**
 * @file      mc723_locker.cpp
 * @author    Grupo 40 - MC723 - 1s2013
 *
 * @version   0.1
 *
 * @brief     Implements a locker.
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
 */

//////////////////////////////////////////////////////////////////////////////
// Standard includes
// SystemC includes
// ArchC includes

#include "mc723_locker.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate locker from ArchC
using user::mc723_locker;

/// Constructor
mc723_locker::mc723_locker( sc_module_name module_name ) :
  sc_module( module_name ),
  target_export("iport")
{
    /// Binds target_export to the memory
    target_export( *this );

    /// Initialize mutex
    mutex = 0;
}

/// Destructor
mc723_locker::~mc723_locker() {
}
