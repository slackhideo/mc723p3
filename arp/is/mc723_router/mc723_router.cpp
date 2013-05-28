/**
 * @file      mc723_router.cpp
 * @author    Grupo 45 - MC723 1s2013
 *
 * @version   0.1
 * @date      Sun, 02 Apr 2006 08:07:46 -0200
 *
 * @brief     Implements a ac_tlm memory.
 *
 * @attention Copyright (C) 2002-2005 --- The ArchC Team
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
// SystemC includes
// ArchC includes

#include "mc723_router.h"

//////////////////////////////////////////////////////////////////////////////

using user::mc723_router;

/// Constructor
mc723_router::mc723_router( sc_module_name module_name , int k ) :
  sc_module( module_name ),
  target_export("iport"),
  DM_port("DM_port", 5242880U)
{
    /// Binds target_export to the router
    target_export( *this );
}

/// Destructor
mc723_router::~mc723_router() {
}
