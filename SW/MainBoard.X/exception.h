/*
 * File:   exception.h
 * Author: Administrateur
 *
 * Created on 2 juin 2015, 14:54
 */

#ifndef EXCEPTION_H
  #define	EXCEPTION_H
  #include <plib.h>
  #include "lcd4u.h"

  #ifdef	__cplusplus
extern "C"
{
  #endif

  static enum
  {
    EXCEP_IRQ = 0, // interrupt
    EXCEP_AdEL = 4, // address error exception (load or ifetch)
    EXCEP_AdES, // address error exception (store)
    EXCEP_IBE, // bus error (ifetch)
    EXCEP_DBE, // bus error (load/store)
    EXCEP_Sys, // syscall
    EXCEP_Bp, // breakpoint
    EXCEP_RI, // reserved instruction
    EXCEP_CpU, // coprocessor unusable
    EXCEP_Overflow, // arithmetic overflow
    EXCEP_Trap, // trap (possible divide by zero)
    EXCEP_IS1 = 16, // implementation specfic 1
    EXCEP_CEU, // CorExtend Unuseable
    EXCEP_C2E // coprocessor 2
  } _excep_code;

//#ifdef __L_DEBUG
  static unsigned int _epc_code;
  static unsigned int _excep_addr;

  void _general_exception_handler(void);
//#endif
  #ifdef	__cplusplus
}
  #endif

#endif	/* EXCEPTION_H */

