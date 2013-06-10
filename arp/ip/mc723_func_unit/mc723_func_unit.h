//////////////////////////////////////////////////////////////////////////////

#ifndef MC723_FUNC_UNIT_H_
#define MC723_FUNC_UNIT_H_

//////////////////////////////////////////////////////////////////////////////

// Standard includes
// SystemC includes
#include <systemc>
// ArchC includes
#include "ac_tlm_protocol.H"
#include "../utility_belt/utility_belt.h"

//////////////////////////////////////////////////////////////////////////////

// using statements
using tlm::tlm_transport_if;

//////////////////////////////////////////////////////////////////////////////

#define UNIT_MUTEX_ADDR 5242884
#define UNIT_ARGUMENT_ADDR 5242888
#define UNIT_RESULT_ADDR 5242896

/// Namespace to isolate unit from ArchC
namespace user
{

/// A TLM function calculator unit
class mc723_func_unit :
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

    case READ: 
      response.status = SUCCESS;

      if (request.addr == UNIT_RESULT_ADDR) {
          read ((float &) response.data);
      }
      
      break;

    case WRITE:
      response.status = SUCCESS;
      // user is writing the argument to the memory to get the result
      if (request.addr == UNIT_ARGUMENT_ADDR) {
          write ((float &) request.data);
      } 
      break;

    default :
      response.status = ERROR;
      break;
    }

    return response;
  }


  
  // Default constructor.
  mc723_func_unit( sc_module_name module_name );

  // Default destructor.
  ~mc723_func_unit();

private:
  /* Handles argument value using different types */
    union argument_values {
        float i;
        unsigned char c[4];
    } argument_value;

    
  float result;

  // reads a double from the address UNIT_ARGUMENT_ADDR, calculates the log10 of the number and stores the value at UNIT_RESULT_ADDR
  void calculateLog10 (float &d);

  void write (const float &d);

  void read (float &d);
};
};

#endif //MC723_FUNC_UNIT_H_
