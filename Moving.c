/*
 * Moving.c
 *
 *  Created on: Nov 18, 2013
 *      Author: C15Linnea.Larson
 */
#include "Moving.h"
#include <msp430.h>

void InitRobot () {
    WDTCTL = WDTPW|WDTHOLD;       // stop the watchdog timer

    P1DIR |= BIT2|BIT1;                // TA0CCR1 on P1.2
    P1SEL |= BIT2|BIT1;                // TA0CCR1 on P1.2
    P2DIR |= BIT0|BIT1;                // TA0CCR1 on P1.2
    P2SEL |= BIT0|BIT1;                // TA0CCR1 on P1.2

    TA0CTL &= ~MC1|MC0;            // stop timer A0
    TA1CTL &= ~MC1|MC0;            // stop timer A0

    TA0CTL |= TACLR;               // clear timer A0
    TA1CTL |= TACLR;               // clear timer A0

    TA0CTL |= TASSEL1;             // configure for SMCLK
    TA1CTL |= TASSEL1;             // configure for SMCLK

    TA0CCR0 = 100;                 // set signal period to 100 clock cycles (~100 microseconds)
    TA0CCR1 = 25;                  // set duty cycle to 25/100 (25%)
    TA1CCR0 = 100;
    TA1CCR1 = 25;

    TA0CTL |= MC0;                 // count up
    TA1CTL |= MC0;                 // count up

    TA0CCR1 = 50;              // set duty cycle to 50/100 (50%)
    TA1CCR1 = 55;
}

void MoveRobotForward () {
	MoveRIGHTForward ();
	MoveLEFTForward ();
	__delay_cycles(1000000);
	StopRIGHT ();
	StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRobotBackwards () {
	MoveRIGHTBackwards ();
	MoveLEFTBackwards ();
    _delay_cycles (250000);
    StopRIGHT ();
    StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRobotLeftS () {
    MoveRIGHTForward ();
    MoveLEFTBackwards ();
    _delay_cycles (200000);
    StopRIGHT ();
    StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRobotRightS() {
	MoveRIGHTBackwards ();
    MoveLEFTForward ();
    _delay_cycles (200000);
    StopRIGHT ();
    StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRobotLeftL () {
    MoveRIGHTForward ();
    MoveLEFTBackwards ();
    _delay_cycles (400000);
    StopRIGHT ();
    StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRobotRightL () {
    MoveRIGHTBackwards ();
    MoveLEFTForward ();
    _delay_cycles (400000);
    StopRIGHT ();
    StopLEFT ();
	__delay_cycles(1000000);
}

void MoveRIGHTForward () {
    TA0CCR1 = 50;
    TA0CCTL1 |= OUTMOD_7;
    TA0CCTL0 &= ~OUTMOD1;
    TA0CCTL0 |= OUTMOD_5;
}

void MoveRIGHTBackwards () {
	TA0CCTL1 &= ~OUTMOD1;
	TA0CCTL1 |= OUTMOD_5;
	TA0CCTL0 |= OUTMOD_7;
}

void MoveLEFTForward () {
    TA1CCR1 = 55;
	TA1CCTL1 |= OUTMOD_7;
    TA1CCTL0 &= ~OUTMOD1;
    TA1CCTL0 |= OUTMOD_5;
}

void MoveLEFTBackwards () {
	TA1CCTL1 &= ~OUTMOD1;
	TA1CCTL1 |= OUTMOD_5;
	TA1CCTL0 |= OUTMOD_7;
}

void StopRIGHT () {
    TA0CCTL1 |= OUTMOD_7;
    TA0CCTL0 &= ~OUTMOD1;
    TA0CCTL0 |= OUTMOD_5;
    TA0CCR1 = 00;
}

void StopLEFT () {
    TA1CCTL1 |= OUTMOD_7;
    TA1CCTL0 &= ~OUTMOD1;
    TA1CCTL0 |= OUTMOD_5;
    TA1CCR1 = 00;
}
