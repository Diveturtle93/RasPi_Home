// Programm zur Ueberwachung von Stromzaehlern via S0-Bus
// Impulse werden ueber einen Interrupt gezaehlt
// Danach werden die Daten in einer Datei gespeichert
// 1-Phasenzaehler 1000 Impulse pro kWh
// 3-Phasenzaehler 800 Impulse pro kWh

// Include Files
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

// GPIOs definieren
#define	Zaehler1	0		// Pin 11
#define	Zaehler2	1		// Pin 12
#define	Zaehler3	2		// Pin 13

// Globale Variable initialisieren
static volatile int Counter = 0 ;


// Interrupt Routine fuer Stromzaehlerimpulse
void Zahler(void)
{
	++Counter ;
}

// Main Routine
int main(void)
{
	// Systemvariablen
	FILE * datei;
	int count = 0, tmp = 0;
	time_t timenow;
	struct tm *myTime;
	char date[20];

	// Start Programm
	datei = fopen("/home/development/Strom/strom.txt","a");
	fprintf(datei, "Starte Programm");
	fclose(datei);

	// Zeit aufnehmen
	time(&timenow);
	myTime = localtime(&timenow);
	strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

	//printf("Start WiringPI\n");
	//fflush(stdout);
	if(wiringPiSetup() < 0)
	{
		datei = fopen("/home/development/Strom/strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Die Bibliothek WiringPi konnte nicht gestartet werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1 ;
	}

	//printf("Definiere Interrupt\n");
	//fflush(stdout);
	if(wiringPiISR(Zaehler3, INT_EDGE_FALLING, &Zahler) < 0)
	{
		datei = fopen("/home/development/Strom/strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Interrupt konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1 ;
	}

	//printf("For-Schleife startet\n");
	//fflush(stdout);
	for(;;)
	{
		//printf ("Waiting ... ");
		//fflush (stdout);

		while(count == Counter)
		{
			delay(100);
		}

		//printf("Done. counter: %5d\n", globalCounter);
		//fflush(stdout);
		time(&timenow);
		myTime = localtime(&timenow);
		strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

		tmp = Counter - count;
		datei = fopen("/home/development/Strom/strom.txt","a");
		fprintf(datei, "%d Wh, %d Wh; %s\n", Counter, tmp, date);
		fclose(datei);
		count = Counter;
	}
	return 0;
}
