/******************************************************************
*******************************************************************
*        File:                                OV7670_control.c
*        Version:                        V1.0 for ATXmega
*
*******************************************************************
******************************************************************/

#include "twi_master_driver.c"
#include "ov7670config.h"

#define OV7670WrAddr 0x42                // Slave adress (I2C) for writeing
#define OV7670ReAddr 0x43                // Slave adress (I2C) for reading


// CPU speed 32MHz, Baudrate 200KHz, Baudrate register Settings
#define CPU_SPEED 32000000
#define BAUDRATE 200000                 // max 400kHz
#define TWI_BAUDSETTING TWI_BAUD(CPU_SPEED, BAUDRATE)


void SCCBInit(void);
void OV7670Init(void);
void OV7670WrReg(unsigned char RegID,
                                 unsigned char RegDat);
unsigned char OV7670ReReg(unsigned char RegID);

// Global variable
TWI_Master_t twiMaster;                        // TWI master modul

// Init OV7670
void OV7670Init(void)
{
        SCCBInit();                        // init SCCB
        
        // RegID 0x12, RegDat 0x80 -> set all register to defualt value
        OV7670WrReg(0x12,0x80);
        _delay_ms(10);

        for(uint8_t n=0;n<RegNum;n=n+2)
        {
                OV7670WrReg(InitBuffer[n],InitBuffer[n+1]);         
        }
        
}

                                                        
// Read register  RegID, return(recive value)
unsigned char OV7670ReReg(unsigned char RegID)
{
        uint8_t SendBuffer[2] = {RegID,OV7670ReAddr},
                                                        pom = 0;

        TWI_MasterWriteRead(&twiMaster,
                        OV7670WrAddr,                // slave adress
                        SendBuffer,                  // data to send
                        2,                           // number of data to send
                        1);                          // number of data to recive

        // wait until sending end
        while (twiMaster.status != TWIM_STATUS_READY)

        pom = ~twiMaster.readData[0];
        return(pom);
}



// Write to register (RegId, RegDat)
void OV7670WrReg(unsigned char RegID,
                                 unsigned char RegDat)
{
        
        uint8_t SendBuffer[2] = {RegID,RegDat};

        TWI_MasterWriteRead(&twiMaster,
                        OV7670WrAddr,
                        SendBuffer,
                        2,
                        0);


        while (twiMaster.status != TWIM_STATUS_READY)
        {}
}



// Init TWI/SCCB
void SCCBInit(void)
{
    TWI_MasterInit(&twiMaster,
                   &TWIF,
                   TWI_MASTER_INTLVL_LO_gc,
                   TWI_BAUDSETTING);
        // Enable LO interrupt level
    PMIC.CTRL |= PMIC_LOLVLEN_bm;
    sei();        
}


// TWIF Master Interrupt vector
ISR(TWIF_TWIM_vect)
{
        TWI_MasterInterruptHandler(&twiMaster);
}
