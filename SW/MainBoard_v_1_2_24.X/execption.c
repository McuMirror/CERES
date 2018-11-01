#include "execption.h"

void _general_exception_handler(void)
  {
      asm volatile("mfc0 %0,$13" : "=r" (_excep_code));
      asm volatile("mfc0 %0,$14" : "=r" (_excep_addr));

      _excep_code = (_excep_code & 0x0000007C) >> 2;


      ("\r\nGeneral Exception ");
      switch(_excep_code){
        case EXCEP_IRQ: Uart1TxStringPolled ("interrupt");break;
        case EXCEP_AdEL: Uart1TxStringPolled ("address error exception (load or ifetch)");break;
        case EXCEP_AdES: Uart1TxStringPolled ("address error exception (store)");break;
        case EXCEP_IBE: Uart1TxStringPolled ("bus error (ifetch)");break;
        case EXCEP_DBE: Uart1TxStringPolled ("bus error (load/store)");break;
        case EXCEP_Sys: Uart1TxStringPolled ("syscall");break;
        case EXCEP_Bp: Uart1TxStringPolled ("breakpoint");break;
        case EXCEP_RI: Uart1TxStringPolled ("reserved instruction");break;
        case EXCEP_CpU: Uart1TxStringPolled ("coprocessor unusable");break;
        case EXCEP_Overflow: Uart1TxStringPolled ("arithmetic overflow");break;
        case EXCEP_Trap: Uart1TxStringPolled ("trap (possible divide by zero)");break;
        case EXCEP_IS1: Uart1TxStringPolled ("implementation specfic 1");break;
        case EXCEP_CEU: Uart1TxStringPolled ("CorExtend Unuseable");break;
        case EXCEP_C2E: Uart1TxStringPolled ("coprocessor 2");break;
      }
      Uart1TxStringPolled(" at 0x");
      Uart1TxUint32HexPolled(_excep_addr);
      Uart1TxStringPolled("\r\n");
      while (1) {
          // Examine _excep_code to identify the type of exception
          // Examine _excep_addr to find the address that caused the exception
      }
  }

