#include <stdio.h>
#include <stdlib.h>
#include <string.h>							// für strcmp zum vergleichen
#include <time.h>							// für die Uhrzeit
#include <wiringPi.h>

int main() {
	FILE * fp;
	int r;
 	time_t now;							// Variable now definieren
	struct tm *myTm;						// Kalender Struktur laden
	char month[12], zeit[12], date[12]="0:00:00:00";		// Puffer um das Datum zwischen zu speichern
	fp = fopen("log_file.txt","a");

	r = system("python /home/development/mail.py -w");		// Email senden nach reboot
	fprintf(fp, "Error Code %d", r);

	while (1)
	{
		time(&now);						// aktuelle Zeit laden
		myTm = localtime(&now);					// Kalender Struktur in myTm laden
		strftime(zeit, 12, "%w:%H:%M:%S", myTm);		// Zeit in String umwandeln
		strftime(month, 12, "%d:%H:%M:%S", myTm);		// Zeit in String umwandeln

		if (strcmp(month, "0:00:00:00") == 0)			// Damit nach einem Monat ein Reboot durchgeführt wird
		{
			r = system("/home/development/temp.sh");	// Temperatur messen
			fprintf(fp, "Monatswechsel erfasst %d", r);
			system("reboot");				// Reboot ausführen
		}

		if (strcmp(zeit, "0:00:00:00") == 0)			// Damit nach einer Woche das Programm weiterzählt wieder bei null
		{
			date[12] = zeit[12];				// Date gleich Buffer
			system("/home/development/temp.sh");		// Temperatur messen
			fprintf(fp, "Wochenwechsel erfasst");
			//system("hwclock -s");				// Einmal wöchentlich die Uhrzeit neu stellen
			r = system("python /home/development/mail.py -t");	// Email senden, txt-Datei schicken
			fprintf(fp, "Email senden %d", r);
		}

		if (strcmp(zeit, date) == 1)				// Abfrage ob Zeit von 30 Min überschritten wurden, Buffer > Date == 1, Buffer < Date == -1, gleich == 0
		{
			fprintf(fp, "Temperatur erfasst");
			myTm->tm_min = myTm->tm_min+30;			// Für die nächste Zeit auf die Min 30 draufrechnen
			strftime(date, 12, "%w:%H:%M:%S\0", myTm);	// umwandeln und in Date speichern
			system("/home/development/temp.sh");		// Temperatur messen
		}
	}
}