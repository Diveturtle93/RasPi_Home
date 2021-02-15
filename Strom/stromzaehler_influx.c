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
#include "./inc/influxdb.h"

// GPIOs definieren
//#define	Zaehler1	0		// Pin 11
//#define	Zaehler2	1		// Pin 12
//#define	Zaehler3	2		// Pin 13
//#define ThreeZaehler	3		// Pin 15

// Globale Variable initialisieren
static volatile int OneCounter1 = 0;
//static volatileint ThreeCounter = 0;


// Interrupt Routine fuer Stromzaehlerimpulse
void OnePhaseZahler1(void)
{
	++OneCounter1;
}

// Main Routine
int main(int argc, char *argv[2])
{
	// Systemvariablen
	influx_client_t c;
	c.host = strdup("127.0.0.1");
	c.port = 8086;
	c.db = strdup("vereinsheim");
	c.usr = strdup("admin");
	c.pwd = strdup("test");

	FILE * datei;
	int count1 = 0;
	int tmp1 = 0;
	time_t timenow;
	struct tm *myTime;
	char date[20];

	#define Zaehler1		(*argv[1] - 48)

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
		fprintf(datei, "Interrupt Einphasen-Zaehler%d konnte nicht initialisiert werden: %s!\n", argc, strerror(errno));
		fclose(datei);
		return 1;
	}

	char Sensor[6] = "Strom";
	Sensor[5] = *argv[1];
	printf("%d", Zaehler1);
	printf("%s\n", Sensor);

	// Endlosschleife
	/*for(;;)
	{
		// Warte bis ein Zaehler neuen Impuls hat
		while(count1 == OneCounter1)
		{
			delay(100);
		}

		// Berechne Anzahl Impulse
		tm1 = (OneCounter1 - count1)/1000;

		count1 = OneCounter1;

		// Schreibe Impulse in Datenbank
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", Sensor), INFLUX_F_FLT("Wert", tm1, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom2"), INFLUX_F_FLT("Wert", tm2, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom3"), INFLUX_F_FLT("Wert", tm3, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);
		//post_http(&c, INFLUX_MEAS("vereinsheim"), INFLUX_TAG("Sensor", "Strom4"), INFLUX_F_FLT("Wert", tm4, 3), INFLUX_F_STR("Einheit", "W"), INFLUX_END);

	}*/
	return 0;
}
