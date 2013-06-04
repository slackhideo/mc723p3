//////////////////////////////////////////////////////////////////////////////

#ifndef MC723_ROUTER_H_
#define MC723_ROUTER_H__

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "ac_tlm_port.H"
#include "../../ip/mc723_locker/mc723_locker.h"
//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate router from ArchC
namespace user
{

// A TLM router!
  class mc723_router :
  public sc_module,
  public ac_tlm_transport_if
{
public:
  
  // Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;
  ac_tlm_port mem_port;
  ac_tlm_port lock_port;
  
  // Constructor
  mc723_router ( sc_module_name module_name , unsigned int k = 5242880U ); /* k = 5M */
  
  // Destructor
  ~mc723_router();
  
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    // response mem
    if(request.addr < 5242884)
      return mem_port->transport(request);
    return lock_port->transport(request);
  }
};
  
};

#endif
