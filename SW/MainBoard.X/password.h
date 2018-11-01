
#ifndef PASSWORD_H
#define	PASSWORD_H
#include "GenericTypeDefs.h"

typedef struct __attribute__((packed))
{
    short localTechnician;
    short localAccountant;
    short httpTechnician;
    short httpAccountant;
}PASSWORDS;

 /**
 * \brief autorisations.
 */
BOOL boLocalAccountantEnable;

BOOL isHttpAccountantEnable;

#endif
