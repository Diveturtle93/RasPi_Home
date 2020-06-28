/*
 * isr.c:
 *	Wait for Interrupt test program - ISR method
 *
 *	How to test:
 *	  Use the SoC's pull-up and pull down resistors that are avalable
 *	on input pins. So compile & run this program (via sudo), then
 *	in another terminal:
 *		gpio mode 0 up
 *		gpio mode 0 down
 *	at which point it should trigger an interrupt. Toggle the pin
 *	up/down to generate more interrupts to test.
 *
 * Copyright (c) 2013 Gordon Henderson.
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>


// What GPIO input are we using?
//This is a wiringPi pin number

#define	Zaehler1	0		// Pin 11
#define	Zaehler2	1		// Pin 12
#define	Zaehler3	2		// Pin 13

// globalCounter:
//Global variable to count interrupts
//	Should be declared volatile to make sure the compiler doesn't cache it.

static volatile int globalCounter = 0 ;


/*
 * myInterrupt:
 *********************************************************************************
 */

void myInterrupt (void)
{
	++globalCounter ;
}


/*
 *********************************************************************************
 * main
 *********************************************************************************
 */

int main (void)
{
	FILE * datei;
	int myCounter = 0 ;
	time_t timenow;
	struct tm *myTime;
	char date[20];


	//printf("Start WiringPI\n");
	//fflush(stdout);
	if (wiringPiSetup() < 0)
	{
		fprintf (stderr, "Unable to setup wiringPi: %s\n", strerror (errno)) ;
		return 1 ;
	}

	//printf("Definiere Interrupt\n");
	//fflush(stdout);
	if (wiringPiISR(Zaehler3, INT_EDGE_FALLING, &myInterrupt) < 0)
	{
		fprintf (stderr, "Unable to setup ISR: %s\n", strerror (errno)) ;
		return 1 ;
	}

	//printf("For-Schleife startet\n");
	//fflush(stdout);
	for (;;)
	{
		//printf ("Waiting ... ") ; fflush (stdout) ;

		while (myCounter == globalCounter)
		{
			delay(100);
		}

		//printf ("Done. counter: %5d\n", globalCounter);
		//fflush(stdout);
		time(&timenow);
		myTime = localtime(&timenow);
		strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

		datei = fopen ("Strom.txt","a") ;
		fprintf (datei, "%d ; %s\n", globalCounter, date) ;
		fclose (datei) ;
		myCounter = globalCounter ;
	}

	return 0;
}
