#include "I2CE2PROML.h"

/******************************************************************************/

void InitI2CE2promL(const I2C_MODULE module, const UINT32 ui32Frequence)
{
    I2CPort = module;
    I2CConfigure(I2CPort, I2C_ENABLE_SLAVE_CLOCK_STRETCHING | I2C_STOP_IN_IDLE | I2C_ENABLE_HIGH_SPEED);
    I2CSetFrequency(I2CPort, ui32Frequence, 100000);
    I2CEnable(I2CPort, TRUE);
}

/******************************************************************************/

BOOL isSendByteToE2promL(BYTE byData)
{
    BYTE byLoop = 0XFF;
    while(!I2CTransmitterIsReady(I2CPort))
    {
        if(!byLoop--)
        {
            return FALSE;
        }
    }
    if(I2CSendByte(I2CPort, byData) != I2C_SUCCESS)
    {
        return FALSE;
    }
    byLoop = 0xFF;
    while(!I2CTransmissionHasCompleted(I2CPort))
    {
        if(!byLoop--)
        {
            return FALSE;
        }
    }
    byLoop = 0xFF;
    while(!I2CByteWasAcknowledged(I2CPort))
    {
        if(!byLoop--)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/******************************************************************************/

BOOL SetE2promAddress(WORD wAddress)
{
    BYTE byLoop = 0xFF;
    BYTE byIndex;
    BYTE byBuffer[3] = {EE_ADDR, wAddress >> 8, wAddress};
    //Verifie que le bus I2C est disponible et envoi une condition de start.
    DelayMs(5);
    
    while(!I2CBusIsIdle(I2CPort));// && byLoop--);
    if((I2CStart(I2CPort) != I2C_SUCCESS))
    {
        return FALSE;
    }
    //Vérifie si le bus I2C est à l'état Start.
    while(!(I2CGetStatus(I2CPort) & I2C_START))
    {
        if(!byLoop--)
        {
            return FALSE;
        }
    }
    //Envoi le mode + l'adresse + l'octet
    for(byIndex = 0; byIndex < sizeof (byBuffer); byIndex++)
    {
        if(!isSendByteToE2promL(byBuffer[byIndex]))
        {
            return FALSE;
        }
    }
    return TRUE;
}

/******************************************************************************/

BOOL I2CE2promLWriteBuffer(const WORD wAddress, void *data, const size_t size)
{
    BYTE *byData;
    byData = data;
    if(!size || (size > 128))
    {
        return FALSE;
    }
    
    if(SetE2promAddress(wAddress))
    {
        BYTE byLoop = 0XFF, byIndex;
        for(byIndex = 0; byIndex < size; byIndex++)
        {
            if(!isSendByteToE2promL(byData[byIndex]))
            {
                return FALSE;
            }
        }
        I2CStop(I2CPort);
        while(!(I2CGetStatus(I2CPort) & I2C_STOP))
        {
            if(!byLoop--)
            {
                return FALSE;
            }
        }
        return TRUE;
    }
    return FALSE;
}

/******************************************************************************/

BOOL I2CE2promLWriteByte(const WORD wAddress, BYTE byData)
{
    return I2CE2promLWriteBuffer(wAddress, &byData, sizeof (byData));
}

/******************************************************************************/

BOOL I2CE2promLReadBuffer(const WORD wAddress, void *data, const size_t size)
{
    BYTE *byData;
    byData = data;
    if(!size)
    {
        return FALSE;
    }
    if(!SetE2promAddress(wAddress))
    {
        return FALSE;
    }
    else
    {
        BYTE byLoop = 0xFF, byIndex;
        if(I2CStart(I2CPort) != I2C_SUCCESS)
        {
            return FALSE;
        }
        //Vérifie si le bus I2C est à l'état Start.
        while(!(I2CGetStatus(I2CPort) & I2C_START))
        {
            if(!byLoop--)
            {
                return FALSE;
            }
        }
        byLoop = 0xFF;
        if(isSendByteToE2promL(EE_ADDR | EEREAD))
        {
            while(!I2CTransmissionHasCompleted(I2CPort))
            {
                if(!byLoop--)
                {
                    return FALSE;
                }
            }
        }
        for(byIndex = 0; byIndex < size;)
        {
            byLoop = 0xFF;
            if(I2CReceiverEnable(I2CPort, TRUE) == I2C_SUCCESS)
            {
                while(!I2CReceivedDataIsAvailable(I2CPort))
                {
                    if(!byLoop--)
                    {
                        return FALSE;
                    }
                }
                byData[byIndex] = I2CGetByte(I2CPort);
                byLoop = 0xFF;                
                (++byIndex < size) ? I2CAcknowledgeByte(I2CPort, TRUE) : I2CAcknowledgeByte(I2CPort, FALSE);
                while(!I2CAcknowledgeHasCompleted(I2CPort))
                {
                    if(!byLoop--)
                    {
                        return FALSE;
                    }
                }
            }
        }
        byLoop = 0xFF;
        I2CStop(I2CPort);
        while(!(I2CGetStatus(I2CPort) & I2C_STOP))
        {
            if(!byLoop--)
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}

/******************************************************************************/

BOOL isI2CE2promLReadByte(const WORD wAddress, BYTE *byData)
{
    return I2CE2promLReadBuffer(wAddress, byData, 1);
}

/******************************************************************************/
