#include "exception.h"

/*****************************************************************************/
#ifdef __L_DEBUG
void _general_exception_handler(void)
{
  asm volatile("mfc0 %0,$13": "=r" (_excep_code));
  asm volatile("mfc0 %0,$14": "=r" (_excep_addr));

  _excep_code = (_excep_code & 0x0000007C) >> 2;
  Nop();
  Nop();
  Nop();
  LCDClear();

  vDisplayLCD("Code %x :", _excep_code);
  switch(_excep_code)
  {
    case EXCEP_IRQ:
    {
      vDisplayLCD("%s", "interrupt");
      break;
    }
    case EXCEP_AdEL:
    {
      vDisplayLCD("%s", "address error exception (load or ifetch)");
      break;
    }
    case EXCEP_AdES:
    {
      vDisplayLCD("%s", "address error exception (store)");
      break;
    }
    case EXCEP_IBE:
    {
      vDisplayLCD("%s", "bus error (ifetch)");
      break;
    }
    case EXCEP_DBE:
    {
      vDisplayLCD("%s", "bus error (load/store)");
      break;
    }
    case EXCEP_Sys:
    {
      vDisplayLCD("%s", "syscall");
      break;
    }
    case EXCEP_Bp:
    {
      vDisplayLCD("%s", "breakpoint");
      break;
    }
    case EXCEP_RI:
    {
      vDisplayLCD("%s", "reserved instruction");
      break;
    }
    case EXCEP_CpU:
    {
      vDisplayLCD("%s", "coprocessor unusable");
      break;
    }
    case EXCEP_Overflow:
    {
      vDisplayLCD("%s", "arithmetic overflow");
      break;
    }
    case EXCEP_Trap:
    {
      vDisplayLCD("%s", "trap (possible divide by zero)");
      break;
    }
    case EXCEP_IS1:
    {
      vDisplayLCD("%s", "implementation specfic 1");
      break;
    }
    case EXCEP_CEU:
    {
      vDisplayLCD("%s", "CorExtend Unuseable");
      break;
    }
    case EXCEP_C2E:
    {
      vDisplayLCD("%s", "coprocessor 2");
      break;
    }
    default:
    {
      vDisplayLCD("%s", "inconnu");
    }
  }
  LCDGotoXY(1, 2);
  vDisplayLCD("Adresse %x", _excep_addr);
  while(TRUE);
}
#endif
/*	End of exception handler*/
/******************************************************************************/

