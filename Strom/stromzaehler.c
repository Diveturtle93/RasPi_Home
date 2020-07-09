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
static volatile int Counter1 = 0;
static volatile int Counter2 = 0;
static volatile int Counter3 = 0;


// Interrupt Routine fuer Stromzaehlerimpulse
void ZahlerInt1(void)
{
	++Counter1;
}

// Interrupt Routine fuer Stromzaehlerimpulse
void ZahlerInt2(void)
{
	++Counter2;
}

// Interrupt Routine fuer Stromzaehlerimpulse
void ZahlerInt3(void)
{
	++Counter3;
}

// Main Routine
int main(void)
{
	// Systemvariablen
	FILE * datei;
	int count1 = 0, count2 = 0, count3 = 0;
	int tmp1 = 0, tmp2 = 0, tmp3 = 0;
	time_t timenow;
	struct tm *myTime;
	char date[20];

	// Start Programm
	datei = fopen("strom.txt","a");
	fprintf(datei, "Starte Programm\n");
	fclose(datei);

	// Zeit aufnehmen
	time(&timenow);
	myTime = localtime(&timenow);
	strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

	//printf("Start WiringPI\n");
	//fflush(stdout);
	if(wiringPiSetup() < 0)
	{
		datei = fopen("strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Die Bibliothek WiringPi konnte nicht gestartet werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}

	//printf("Definiere Interrupt 1\n");
	//fflush(stdout);
	if(wiringPiISR(Zaehler1, INT_EDGE_FALLING, &ZahlerInt1) < 0)
	{
		datei = fopen("strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Interrupt Zaehler1 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	//printf("Definiere Interrupt 2\n");
	//fflush(stdout);
	if(wiringPiISR(Zaehler2, INT_EDGE_FALLING, &ZahlerInt2) < 0)
	{
		datei = fopen("strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Interrupt Zaehler2 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	//printf("Definiere Interrupt 3\n");
	//fflush(stdout);
	if(wiringPiISR(Zaehler3, INT_EDGE_FALLING, &ZahlerInt3) < 0)
	{
		datei = fopen("Strom.txt","a");
		fprintf(datei, "%s\n", date);
		fprintf(datei, "Interrupt Zaehler3 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}

	//printf("For-Schleife startet\n");
	//fflush(stdout);
	for(;;)
	{
		//printf ("Waiting ... ");
		//fflush (stdout);

		while((count1 == Counter1) && (count2 == Counter2) && (count3 == Counter3))
		{
			delay(100);
		}

		//printf("Done. counter: %5d\n", globalCounter);
		//fflush(stdout);
		time(&timenow);
		myTime = localtime(&timenow);
		strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

		tm1 = Counter1 - count1;
		tm2 = Counter2 - count2;
		tm3 = Counter3 - count3;
		
		datei = fopen("strom.txt","a");
		fprintf(datei, "%d Wh, %d Wh, ", Counter1, tmp1);
		fprintf(datei, "%d Wh, %d Wh, ", Counter2, tmp2);
		fprintf(datei, "%d Wh, %d Wh; ", Counter3, tmp3);
		fprintf(datei, "%s\n", date);
		fclose(datei);
		
		count1 = Counter1;
		count2 = Counter2;
		count3 = Counter3;
	}
	return 0;
}
