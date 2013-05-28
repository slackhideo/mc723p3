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

//#define DEBUG

namespace user
{

/// A TLM router
    class mc723_router :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;

  ac_tlm_port DM_port;
  
  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

      //ac_tlm_rsp response;


    return DM_port->transport(request);
  }


  /**
   * Default constructor.
   *
   * @param k Memory size in kilowords.
   *
   */
  mc723_router ( sc_module_name module_name , int k = 5242880 );

  /**
   * Default destructor.
   */
  ~mc723_router();
};

};

#endif //AC_TLM_MEM_H_
