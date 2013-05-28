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

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

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
  ac_tlm_port DM_port;

    // Constructor
  mc723_router ( sc_module_name module_name , int k = 5242880 );

    // Destructor
  ~mc723_router();
    
  ac_tlm_rsp transport( const ac_tlm_req &request ) {
    // ac_tlm_rsp response
    return DM_port->transport(request);
  }
};

};

#endif
