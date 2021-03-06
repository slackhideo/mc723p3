/******************************************************
 * This is the main file for the mips1 ArchC model    *
 * This file is automatically generated by ArchC      *
 * WITHOUT WARRANTY OF ANY KIND, either express       *
 * or implied.                                        *
 * For more information on ArchC, please visit:       *
 * http://www.archc.org                               *
 *                                                    *
 * The ArchC Team                                     *
 * Computer Systems Laboratory (LSC)                  *
 * IC-UNICAMP                                         *
 * http://www.lsc.ic.unicamp.br                       *
 ******************************************************/

// Grupo 40
 
const char *project_name="mips1";
const char *project_file="mips1.ac";
const char *archc_version="2.0beta1";
const char *archc_options="-abi -dy ";

#include <systemc.h>
#include <string.h>
#include "mips1.H"
#include "ac_tlm_mem.h"
#include "mc723_router.h"
#include "mc723_locker.h"
#include "mc723_func_unit.h"

using user::ac_tlm_mem;
using user::mc723_router;
using user::mc723_locker;
using user::mc723_func_unit;

int sc_main(int ac, char *av[])
{
  int exit_status = 0;

  //!  ISA simulator
  mips1 mips1_proc1("mips1");
  
  ac_tlm_mem mem("mem");

  mc723_router router("router");
  mc723_locker locker("locker");
  mc723_func_unit unit("unit");

#ifdef AC_DEBUG
  ac_trace("mips1_proc1.trace");
#endif 

  /* Connection between processors and router */
  mips1_proc1.DM_port(router.target_export);

  /* Connection between router and memory */
  router.mem_port (mem.target_export);

  /* Connection between router and lock device */
  router.lock_port (locker.target_export);

  /* Connection between router and function unit */
  router.func_unit_port (unit.target_export);

  /* Creates a copy of the av parameter */
  char **av_bkp = (char **)malloc(ac*sizeof(char *));
  for(int i = 0; i < ac; i++)
      av_bkp[i] = (char *)malloc(strlen(av[i])*sizeof(char));

  /* Processors initialisation */
  for(int i = 0; i < ac; i++) strcpy(av_bkp[i], av[i]);
  mips1_proc1.init(ac, av_bkp);

  cerr << endl;

  sc_start();

  cerr << "Processor 1:" << endl;
  mips1_proc1.PrintStat();
  cerr << endl;

#ifdef AC_STATS
  mips1_proc1.ac_sim_stats.time = sc_simulation_time();
  mips1_proc1.ac_sim_stats.print();
#endif 

#ifdef AC_DEBUG
  ac_close_trace();
#endif 

  return exit_status;
}
