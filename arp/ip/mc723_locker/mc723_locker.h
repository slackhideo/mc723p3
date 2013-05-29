//////////////////////////////////////////////////////////////////////////////

#ifndef MC723_LOCKER_H_
#define MC723_LOCKER_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

/// Namespace to isolate locker from ArchC
namespace user
{

/// A TLM locker
class mc723_locker :
  public sc_module,
  public ac_tlm_transport_if // Using ArchC TLM protocol
{
public:
  /// Exposed port with ArchC interface
  sc_export< ac_tlm_transport_if > target_export;

  /**
   * Implementation of TLM transport method that
   * handle packets of the protocol doing apropriate actions.
   * This method must be implemented (required by SystemC TLM).
   * @param request is a received request packet
   * @return A response packet to be send
  */
  ac_tlm_rsp transport( const ac_tlm_req &request ) {

    ac_tlm_rsp response;

    switch( request.type ) {

    /* Consulta (lê) e adquire (se possível) a trava */
    case READ: 
      response.status = SUCCESS;
      response.data = mutex;
      mutex = 1;
      break;

    /* Escreve na trava (libera ou trava) */
    case WRITE:
      response.status = SUCCESS;
      mutex = request.data;
      break;
    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  
  // Default constructor.
  mc723_locker( sc_module_name module_name );

  // Default destructor.
  ~mc723_locker();

private:
  uint8_t mutex; /* Variável para o mutex (trava) */
};
};

#endif //MC723_LOCKER_H_
