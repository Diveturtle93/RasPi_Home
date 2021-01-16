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
#include "../inc/influxdb.h"

// GPIOs definieren
#define	Zaehler1	0		// Pin 11
#define	Zaehler2	1		// Pin 12
#define	Zaehler3	2		// Pin 13
//#define ThreeZaehler	3		// Pin 15

// Globale Variable initialisieren
static volatile int OneCounter1 = 0;
static volatile int OneCounter2 = 0;
static volatile int OneCounter3 = 0;
//static volatileint ThreeCounter = 0;


// Interrupt Routine fuer Stromzaehlerimpulse
void OnePhaseZahler1(void)
{
	++OneCounter1;
}

// Interrupt Routine fuer Stromzaehlerimpulse
void OnePhaseZahler2(void)
{
	++OneCounter2;
}

// Interrupt Routine fuer Stromzaehlerimpulse
void OnePhaseZahler3(void)
{
	++OneCounter3;
}

/*// Interrupt Routine fuer Stromzaehlerimpulse
void ThreePhaseZaehler(void)
{
	++ThreeCounter;
}*/

// Main Routine
int main(void)
{
	// Systemvariablen
	influx_client_t c;
	c.host = strdup("127.0.0.1");
	c.port = 8086;
	c.db = strdup("vereinsheim");
	c.usr = strdup("admin");
    c.pwd = strdup("test");
	
	FILE * datei;
	int count1 = 0, count2 = 0, count3 = 0; //, count4 = 0;
	int tmp1 = 0, tmp2 = 0, tmp3 = 0; //, tm4 = 0;
	time_t timenow;
	struct tm *myTime;
	char date[20];

	// Zeit aufnehmen
	time(&timenow);
	myTime = localtime(&timenow);
	strftime(date, 20, "%Y.%m.%d-%H:%M:%S", myTime);

	// Start Programm
	datei = fopen("/home/development/Strom/log.txt","a");
	fprintf(datei, "Starte Programm:\t%s\n", date);
	fclose(datei);
	
	// Starte WiringPi
	if(wiringPiSetup() < 0)
	{
		datei = fopen("/home/development/Strom/log.txt","a");
		fprintf(datei, "Die Bibliothek WiringPi konnte nicht gestartet werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	// Initialisiere ISR Zaehler1
	if(wiringPiISR(Zaehler1, INT_EDGE_FALLING, &OnePhaseZahler1) < 0)
	{
		datei = fopen("/home/development/Strom/log.txt","a");
		fprintf(datei, "Interrupt Einphasen-Zaehler1 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	// Initialisiere ISR Zaehler2
	if(wiringPiISR(Zaehler2, INT_EDGE_FALLING, &OnePhaseZahler2) < 0)
	{
		datei = fopen("/home/development/Strom/log.txt","a");
		fprintf(datei, "Interrupt Einphasen-Zaehler2 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	// Initialisiere ISR Zaehler3
	if(wiringPiISR(Zaehler3, INT_EDGE_FALLING, &OnePhaseZahler3) < 0)
	{
		datei = fopen("/home/development/Strom/log.txt","a");
		fprintf(datei, "Interrupt Einphasen-Zaehler3 konnte nicht initialisiert werden: %s!\n", strerror(errno));
		fclose(datei);
		return 1;
	}
	
	// Endlosschleife
	for(;;)
	{
		// Warte bis ein Zaehler neuen Impuls hat
		while((count1 == OneCounter1) && (count2 == OneCounter2) && (count3 == OneCounter3) && (count4 == ThreeCounter))
		{
			delay(100);
		}
		
		// Berechne Anzahl Impulse
		tm1 = (OneCounter1 - count1)/1000;
		tm2 = (OneCounter2 - count2)/1000;
		tm3 = (OneCounter3 - count3)/1000;
		//tm4 = (ThreeCounter - count4)/800;
		
		// Schreibe Impulse in Datenbank
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom1"), INFLUX_F_FLT("Wert", tm1, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom2"), INFLUX_F_FLT("Wert", tm2, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom3"), INFLUX_F_FLT("Wert", tm3, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		//post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom4"), INFLUX_F_FLT("Wert", tm4, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		
		
		count1 = OneCounter1;
		count2 = OneCounter2;
		count3 = OneCounter3;
		//count4 = ThreeCounter;
	}
	return 0;
}
