# Raspberry Pi Projekt

### Hausüberwachung  
* Temperaturmessung 1-Wire Sensoren  
* Emailversand Temperaturdaten  
* Stromzähler auslesen  


#### Temperaturmessung  
Die Temperaturmessung wird mit 1-Wire Sensoren durchgeführt. Diese werden an unterschiedlichen
Stellen angebracht. Über das Softwarepaket Crontab wird die Temperaturmessung regelmäßig
zu definierten Zeiten gestartet.  

Zusätzlich wird einmal die Woche, eine Email mit den aktuellen Temperaturdaten versand.


#### Stromzähler
Eine weitere Aufgabe des Raspberry Pi's ist es, Stromzähler per S0-Bus einzulesen.
Die Messwerte werden ausgewertet und in einer entsprechenden Datei gespeichert.  

Abgespeichert wird ebenfalls neben den Impulsen des S0-Busses, eine zeitangabe für eine spätere
Auswertung.

#### Emailversand
Für den Emailversand muss die Datei config.txt in config.ini umbenant werden. Zusätzlich müssen
die Fehlenden Einträge unter der Kategorie Server ergänzt und vervollständigt werden.
Ansonsten ist ein korrekt arbeitender Emailversand nicht gewärleistet.