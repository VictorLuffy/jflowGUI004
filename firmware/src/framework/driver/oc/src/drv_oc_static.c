/*******************************************************************************
  OC Driver Functions for Static Single Instance Driver

  Company:
    Microchip Technology Inc.

  File Name:
    drv_oc_static.c

  Summary:
    OC driver implementation for the static single instance driver.

  Description:
    The OC device driver provides a simple interface to manage the OC
    modules on Microchip microcontrollers.
    
  Remarks:
    Static interfaces incorporate the driver instance number within the names
    of the routines, eliminating the need for an object ID or object handle.
    Static single-open interfaces also eliminate the need for the open handle.
*******************************************************************************/

//DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTOCULAR PURPOSE.
IN NO EVENT SHALL MOCROCHIP OR ITS LOCENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STROCT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVOCES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
//DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Header Includes
// *****************************************************************************
// *****************************************************************************
#include "peripheral/oc/plib_oc.h"

#include "peripheral/devcon/plib_devcon.h"
// *****************************************************************************
// *****************************************************************************
// Section: Instance 0 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_OC0_Initialize(void)
{
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_1, OC_DUAL_COMPARE_CONTINUOUS_PULSE_MODE);
    PLIB_OC_BufferSizeSelect(OC_ID_1, OC_BUFFER_SIZE_16BIT);
    PLIB_DEVCON_SystemUnlock (DEVCON_ID_0);
    PLIB_OC_AlternateClockEnable( OC_ID_1 );
    PLIB_DEVCON_SystemLock (DEVCON_ID_0);
    PLIB_OC_AlternateTimerSelect(OC_ID_1, OC_ALT_TIMER_TMR4);
    PLIB_OC_Buffer16BitSet(OC_ID_1, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_1, 1000);
}

void DRV_OC0_Enable(void)
{
   PLIB_OC_Enable(OC_ID_1);
}

void DRV_OC0_Disable(void)
{
   PLIB_OC_Disable(OC_ID_1);
}

void DRV_OC0_Start(void)
{
   PLIB_OC_Enable(OC_ID_1);
}

void DRV_OC0_Stop(void)
{
   PLIB_OC_Disable(OC_ID_1);
}

void DRV_OC0_CompareValuesDualSet(uint32_t priVal, uint32_t secVal)
{
    /* Updating primary compare value for 16 bit mode */
    PLIB_OC_Buffer16BitSet(OC_ID_1, (uint16_t)priVal);

    /* Updating secondary compare value for 16 bit mode */	
    PLIB_OC_PulseWidth16BitSet(OC_ID_1, (uint16_t)secVal);
}

bool DRV_OC0_FaultHasOccurred(void)
{
   return PLIB_OC_FaultHasOccurred(OC_ID_1);
}

#include "peripheral/devcon/plib_devcon.h"
// *****************************************************************************
// *****************************************************************************
// Section: Instance 1 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_OC1_Initialize(void)
{
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_2, OC_DUAL_COMPARE_CONTINUOUS_PULSE_MODE);
    PLIB_OC_BufferSizeSelect(OC_ID_2, OC_BUFFER_SIZE_16BIT);
    PLIB_DEVCON_SystemUnlock (DEVCON_ID_0);
    PLIB_OC_AlternateClockEnable( OC_ID_2 );
    PLIB_DEVCON_SystemLock (DEVCON_ID_0);
    PLIB_OC_AlternateTimerSelect(OC_ID_2, OC_ALT_TIMER_TMR4);
    PLIB_OC_Buffer16BitSet(OC_ID_2, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, 1000);
}

void DRV_OC1_Enable(void)
{
   PLIB_OC_Enable(OC_ID_2);
}

void DRV_OC1_Disable(void)
{
   PLIB_OC_Disable(OC_ID_2);
}

void DRV_OC1_Start(void)
{
   PLIB_OC_Enable(OC_ID_2);
}

void DRV_OC1_Stop(void)
{
   PLIB_OC_Disable(OC_ID_2);
}

void DRV_OC1_CompareValuesDualSet(uint32_t priVal, uint32_t secVal)
{
    /* Updating primary compare value for 16 bit mode */
    PLIB_OC_Buffer16BitSet(OC_ID_2, (uint16_t)priVal);

    /* Updating secondary compare value for 16 bit mode */	
    PLIB_OC_PulseWidth16BitSet(OC_ID_2, (uint16_t)secVal);
}

bool DRV_OC1_FaultHasOccurred(void)
{
   return PLIB_OC_FaultHasOccurred(OC_ID_2);
}

#include "peripheral/devcon/plib_devcon.h"
// *****************************************************************************
// *****************************************************************************
// Section: Instance 2 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_OC2_Initialize(void)
{
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_5, OC_COMPARE_PWM_EDGE_ALIGNED_MODE);
    PLIB_OC_BufferSizeSelect(OC_ID_5, OC_BUFFER_SIZE_16BIT);
    PLIB_DEVCON_SystemUnlock (DEVCON_ID_0);
    PLIB_OC_AlternateClockEnable( OC_ID_5 );
    PLIB_DEVCON_SystemLock (DEVCON_ID_0);
    PLIB_OC_AlternateTimerSelect(OC_ID_5, OC_ALT_TIMER_TMR2);
    PLIB_OC_Buffer16BitSet(OC_ID_5, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_5, 1000);
}

void DRV_OC2_Enable(void)
{
   PLIB_OC_Enable(OC_ID_5);
}

void DRV_OC2_Disable(void)
{
   PLIB_OC_Disable(OC_ID_5);
}

void DRV_OC2_Start(void)
{
   PLIB_OC_Enable(OC_ID_5);
}

void DRV_OC2_Stop(void)
{
   PLIB_OC_Disable(OC_ID_5);
}

void DRV_OC2_PulseWidthSet(uint32_t pulseWidth)
{
    /* Updating pulse width for 16 bit mode */
    PLIB_OC_PulseWidth16BitSet(OC_ID_5, (uint16_t)pulseWidth);
}

bool DRV_OC2_FaultHasOccurred(void)
{
   return PLIB_OC_FaultHasOccurred(OC_ID_5);
}

#include "peripheral/devcon/plib_devcon.h"
// *****************************************************************************
// *****************************************************************************
// Section: Instance 3 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_OC3_Initialize(void)
{
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_6, OC_COMPARE_PWM_EDGE_ALIGNED_MODE);
    PLIB_OC_BufferSizeSelect(OC_ID_6, OC_BUFFER_SIZE_16BIT);
    PLIB_DEVCON_SystemUnlock (DEVCON_ID_0);
    PLIB_OC_AlternateClockEnable( OC_ID_6 );
    PLIB_DEVCON_SystemLock (DEVCON_ID_0);
    PLIB_OC_AlternateTimerSelect(OC_ID_6, OC_ALT_TIMER_TMR3);
    PLIB_OC_Buffer16BitSet(OC_ID_6, 3125);
    PLIB_OC_PulseWidth16BitSet(OC_ID_6, 3125);
}

void DRV_OC3_Enable(void)
{
   PLIB_OC_Enable(OC_ID_6);
}

void DRV_OC3_Disable(void)
{
   PLIB_OC_Disable(OC_ID_6);
}

void DRV_OC3_Start(void)
{
   PLIB_OC_Enable(OC_ID_6);
}

void DRV_OC3_Stop(void)
{
   PLIB_OC_Disable(OC_ID_6);
}

void DRV_OC3_PulseWidthSet(uint32_t pulseWidth)
{
    /* Updating pulse width for 16 bit mode */
    PLIB_OC_PulseWidth16BitSet(OC_ID_6, (uint16_t)pulseWidth);
}

bool DRV_OC3_FaultHasOccurred(void)
{
   return PLIB_OC_FaultHasOccurred(OC_ID_6);
}

#include "peripheral/devcon/plib_devcon.h"
// *****************************************************************************
// *****************************************************************************
// Section: Instance 4 static driver functions
// *****************************************************************************
// *****************************************************************************
void DRV_OC4_Initialize(void)
{
    /* Setup OC0 Instance */
    PLIB_OC_ModeSelect(OC_ID_8, OC_COMPARE_PWM_EDGE_ALIGNED_MODE);
    PLIB_OC_BufferSizeSelect(OC_ID_8, OC_BUFFER_SIZE_16BIT);
    PLIB_DEVCON_SystemUnlock (DEVCON_ID_0);
    PLIB_OC_AlternateClockEnable( OC_ID_8 );
    PLIB_DEVCON_SystemLock (DEVCON_ID_0);
    PLIB_OC_AlternateTimerSelect(OC_ID_8, OC_ALT_TIMER_TMR7);
    PLIB_OC_Buffer16BitSet(OC_ID_8, 0);
    PLIB_OC_PulseWidth16BitSet(OC_ID_8, 1000);
}

void DRV_OC4_Enable(void)
{
   PLIB_OC_Enable(OC_ID_8);
}

void DRV_OC4_Disable(void)
{
   PLIB_OC_Disable(OC_ID_8);
}

void DRV_OC4_Start(void)
{
   PLIB_OC_Enable(OC_ID_8);
}

void DRV_OC4_Stop(void)
{
   PLIB_OC_Disable(OC_ID_8);
}

void DRV_OC4_PulseWidthSet(uint32_t pulseWidth)
{
    /* Updating pulse width for 16 bit mode */
    PLIB_OC_PulseWidth16BitSet(OC_ID_8, (uint16_t)pulseWidth);
}

bool DRV_OC4_FaultHasOccurred(void)
{
   return PLIB_OC_FaultHasOccurred(OC_ID_8);
}

/*******************************************************************************
 End of File
*/
