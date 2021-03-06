//*****************************************************************************
//
// Startup code for use with TI's Code Composer Studio.
//
// Copyright (c) 2011-2014 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern uint32_t __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************
// To be added by user
//--------------------------------------------------------------
// -- GPIO call backs
//--------------------------------------------------------------
extern void gpioCallBackPortAWr(void);
extern void gpioCallBackPortBWr(void);
extern void gpioCallBackPortCWr(void);
extern void gpioCallBackPortDWr(void);
extern void gpioCallBackPortEWr(void);
extern void gpioCallBackPortFWr(void);
extern void gpioCallBackPortGWr(void);
extern void gpioCallBackPortHWr(void);
extern void gpioCallBackPortJWr(void);
extern void gpioCallBackPortKWr(void);
extern void gpioCallBackPortLWr(void);
extern void gpioCallBackPortMWr(void);
extern void gpioCallBackPortNWr(void);
extern void gpioCallBackPortPWr(void);
extern void gpioCallBackPortQWr(void);
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- Timer call backs
extern void timer0ACallBackWr(void);
extern void timer0BCallBackWr(void);
extern void timer1ACallBackWr(void);
extern void timer1BCallBackWr(void);
extern void timer2ACallBackWr(void);
extern void timer2BCallBackWr(void);
extern void timer3ACallBackWr(void);
extern void timer3BCallBackWr(void);
extern void timer4ACallBackWr(void);
extern void timer4BCallBackWr(void);
extern void timer5ACallBackWr(void);
extern void timer5BCallBackWr(void);
extern void timer6ACallBackWr(void);
extern void timer6BCallBackWr(void);
extern void timer7ACallBackWr(void);
extern void timer7BCallBackWr(void);
//--------------------------------------------------------------


//--------------------------------------------------------------
// -- SSI call backs
//--------------------------------------------------------------
extern void ssi0CallBackWr(void);
extern void ssi1CallBackWr(void);
extern void ssi2CallBackWr(void);
extern void ssi3CallBackWr(void);
//--------------------------------------------------------------
//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((uint32_t)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    IntDefaultHandler,                      // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // SVCall handler
    IntDefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    IntDefaultHandler,                      // The PendSV handler
    IntDefaultHandler,                      // The SysTick handler
    gpioCallBackPortAWr,                    // GPIO Port A
    gpioCallBackPortBWr,                    // GPIO Port B
    gpioCallBackPortCWr,                    // GPIO Port C
    gpioCallBackPortDWr,                    // GPIO Port D
    gpioCallBackPortEWr,                    // GPIO Port E
    IntDefaultHandler,                      // UART0 Rx and Tx
    IntDefaultHandler,                      // UART1 Rx and Tx
    ssi0CallBackWr,                         // SSI0 Rx and Tx
    IntDefaultHandler,                      // I2C0 Master and Slave
    IntDefaultHandler,                      // PWM Fault
    IntDefaultHandler,                      // PWM Generator 0
    IntDefaultHandler,                      // PWM Generator 1
    IntDefaultHandler,                      // PWM Generator 2
    IntDefaultHandler,                      // Quadrature Encoder 0
    IntDefaultHandler,                      // ADC Sequence 0
    IntDefaultHandler,                      // ADC Sequence 1
    IntDefaultHandler,                      // ADC Sequence 2
    IntDefaultHandler,                      // ADC Sequence 3
    IntDefaultHandler,                      // Watchdog timer
    timer0ACallBackWr,                      // Timer 0 subtimer A
    timer0BCallBackWr,                      // Timer 0 subtimer B
    timer1ACallBackWr,                      // Timer 1 subtimer A
    timer1BCallBackWr,                      // Timer 1 subtimer B
    timer2ACallBackWr,                      // Timer 2 subtimer A
    timer2BCallBackWr,                      // Timer 2 subtimer B
    IntDefaultHandler,                      // Analog Comparator 0
    IntDefaultHandler,                      // Analog Comparator 1
    IntDefaultHandler,                      // Analog Comparator 2
    IntDefaultHandler,                      // System Control (PLL, OSC, BO)
    IntDefaultHandler,                      // FLASH Control
    gpioCallBackPortFWr,                    // GPIO Port F
    gpioCallBackPortGWr,                    // GPIO Port G
    gpioCallBackPortHWr,                    // GPIO Port H
    IntDefaultHandler,                      // UART2 Rx and Tx
    ssi1CallBackWr,                         // SSI1 Rx and Tx
    timer3ACallBackWr,                      // Timer 3 subtimer A
    timer3BCallBackWr,                      // Timer 3 subtimer B
    IntDefaultHandler,                      // I2C1 Master and Slave
    IntDefaultHandler,                      // CAN0
    IntDefaultHandler,                      // CAN1
    IntDefaultHandler,                      // Ethernet
    IntDefaultHandler,                      // Hibernate
    IntDefaultHandler,                      // USB0
    IntDefaultHandler,                      // PWM Generator 3
    IntDefaultHandler,                      // uDMA Software Transfer
    IntDefaultHandler,                      // uDMA Error
    IntDefaultHandler,                      // ADC1 Sequence 0
    IntDefaultHandler,                      // ADC1 Sequence 1
    IntDefaultHandler,                      // ADC1 Sequence 2
    IntDefaultHandler,                      // ADC1 Sequence 3
    IntDefaultHandler,                      // External Bus Interface 0
    gpioCallBackPortJWr,                    // GPIO Port J
    gpioCallBackPortKWr,                    // GPIO Port K
    gpioCallBackPortLWr,                    // GPIO Port L
    ssi2CallBackWr,                         // SSI2 Rx and Tx
    ssi3CallBackWr,                         // SSI3 Rx and Tx
    IntDefaultHandler,                      // UART3 Rx and Tx
    IntDefaultHandler,                      // UART4 Rx and Tx
    IntDefaultHandler,                      // UART5 Rx and Tx
    IntDefaultHandler,                      // UART6 Rx and Tx
    IntDefaultHandler,                      // UART7 Rx and Tx
    IntDefaultHandler,                      // I2C2 Master and Slave
    IntDefaultHandler,                      // I2C3 Master and Slave
    timer4ACallBackWr,                      // Timer 4 subtimer A
    timer4BCallBackWr,                      // Timer 4 subtimer B
    timer5ACallBackWr,                      // Timer 5 subtimer A
    timer5BCallBackWr,                      // Timer 5 subtimer B
    IntDefaultHandler,                      // FPU
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // I2C4 Master and Slave
    IntDefaultHandler,                      // I2C5 Master and Slave
    gpioCallBackPortMWr,                    // GPIO Port M
    gpioCallBackPortNWr,                    // GPIO Port N
    0,                                      // Reserved
    IntDefaultHandler,                      // Tamper
    gpioCallBackPortPWr,                    // GPIO Port P (Summary or P0)
    gpioCallBackPortPWr,                    // GPIO Port P1
    gpioCallBackPortPWr,                    // GPIO Port P2
    gpioCallBackPortPWr,                    // GPIO Port P3
    gpioCallBackPortPWr,                    // GPIO Port P4
    gpioCallBackPortPWr,                    // GPIO Port P5
    gpioCallBackPortPWr,                    // GPIO Port P6
    gpioCallBackPortPWr,                    // GPIO Port P7
    gpioCallBackPortQWr,                    // GPIO Port Q (Summary or Q0)
    gpioCallBackPortQWr,                    // GPIO Port Q1
    gpioCallBackPortQWr,                    // GPIO Port Q2
    gpioCallBackPortQWr,                    // GPIO Port Q3
    gpioCallBackPortQWr,                    // GPIO Port Q4
    gpioCallBackPortQWr,                    // GPIO Port Q5
    gpioCallBackPortQWr,                    // GPIO Port Q6
    gpioCallBackPortQWr,                    // GPIO Port Q7
    IntDefaultHandler,                      // GPIO Port R
    IntDefaultHandler,                      // GPIO Port S
    IntDefaultHandler,                      // SHA/MD5 0
    IntDefaultHandler,                      // AES 0
    IntDefaultHandler,                      // DES3DES 0
    IntDefaultHandler,                      // LCD Controller 0
    timer6ACallBackWr,                      // Timer 6 subtimer A
    timer6BCallBackWr,                      // Timer 6 subtimer B
    timer7ACallBackWr,                      // Timer 7 subtimer A
    timer7BCallBackWr,                      // Timer 7 subtimer B
    IntDefaultHandler,                      // I2C6 Master and Slave
    IntDefaultHandler,                      // I2C7 Master and Slave
    IntDefaultHandler,                      // HIM Scan Matrix Keyboard 0
    IntDefaultHandler,                      // One Wire 0
    IntDefaultHandler,                      // HIM PS/2 0
    IntDefaultHandler,                      // HIM LED Sequencer 0
    IntDefaultHandler,                      // HIM Consumer IR 0
    IntDefaultHandler,                      // I2C8 Master and Slave
    IntDefaultHandler,                      // I2C9 Master and Slave
    IntDefaultHandler,                      // GPIO Port T
    IntDefaultHandler,                      // Fan 1
    0,                                      // Reserved
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
    //
    // Jump to the CCS C initialization routine.  This will enable the
    // floating-point unit as well, so that does not need to be done here.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
