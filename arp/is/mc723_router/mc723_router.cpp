/**
 * @file      mc723_router.cpp
 * @author    Grupo 40 - MC723 - 1s2013
 *
 * @version   0.2
 *
 * @brief     Implements a router.
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

#include "mc723_router.h"

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate router from ArchC
using user::mc723_router;

/// Constructor
mc723_router::mc723_router( sc_module_name module_name , unsigned int k ) :
  sc_module( module_name ),
  target_export("iport"),
  mem_port("mem", k),
  lock_port("lock", 1)
{
    /// Binds target_export to the router
    target_export( *this );
}

/// Destructor
mc723_router::~mc723_router() {
}
