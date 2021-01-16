#!/bin/bash
#Schleife/Wiederholung bei #while [1]; do UND bei #done #-entfernen
#while [1]; do 
#
#Temperatur auslesen:
#tempread=`cat /sys/bus/w1/devices/28-8000001f94ba/w1_slave`
#-------------------------------
tempread0=`cat /sys/bus/w1/devices/28-8000001f77cb/w1_slave` #S0 = A
tempread1=`cat /sys/bus/w1/devices/28-8000001f7884/w1_slave` #S1 = B
tempread2=`cat /sys/bus/w1/devices/28-8000001f942f/w1_slave` #S2 = C
tempread3=`cat /sys/bus/w1/devices/28-8000001f77c4/w1_slave` #S3 = D
tempread4=`cat /sys/bus/w1/devices/28-8000001f9369/w1_slave` #S4 = E
#tempread5=`cat /sys/bus/w1/devices/28-8000001f934d/w1_slave` #S5 = F
#tempread6=`cat /sys/bus/w1/devices/28-8000001f7752/w1_slave` #S6 = G
#tempread7=`cat /sys/bus/w1/devices/28-8000001f9453/w1_slave` #S7 = H
#tempread8=`cat /sys/bus/w1/devices/28-8000001f94ce/w1_slave` #S8 = I
#tempread9=`cat /sys/bus/w1/devices/28-8000001f94ba/w1_slave` #S9 = J
#
#Formatieren:
#temp=`echo "scale=2; "\`echo ${tempread##*=}\`" / 1000" | bc`
#-------------------------------
temp0=`echo "scale=2; "\`echo ${tempread0##*=}\`" / 1000" | bc`
temp1=`echo "scale=2; "\`echo ${tempread1##*=}\`" / 1000" | bc`
temp2=`echo "scale=2; "\`echo ${tempread2##*=}\`" / 1000" | bc`
temp3=`echo "scale=2; "\`echo ${tempread3##*=}\`" / 1000" | bc`
temp4=`echo "scale=2; "\`echo ${tempread4##*=}\`" / 1000" | bc`
#temp5=`echo "scale=2; "\`echo ${tempread5##*=}\`" / 1000" | bc`
#temp6=`echo "scale=2; "\`echo ${tempread6##*=}\`" / 1000" | bc`
#temp7=`echo "scale=2; "\`echo ${tempread7##*=}\`" / 1000" | bc`
#temp8=`echo "scale=2; "\`echo ${tempread8##*=}\`" / 1000" | bc`
#temp9=`echo "scale=2; "\`echo ${tempread9##*=}\`" / 1000" | bc`
#
#Ausgabe (>> bedeutet speicher in der Datei speicherTemp oder anderen Pfad)
#echo "gemessene Temperatur beträgt" $temp "°C" >> /home/pi/speicherTemp #HP# "c" oder "-n" (eintragen =verhindert das der nächste Wert in eine Neue Zeile geschrieben wird.
#
#------------
echo -n $temp0"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #A
echo -n $temp1"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #B
echo -n $temp2"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #C
echo -n $temp3"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #D
echo -n $temp4"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #E
#echo -n $temp5"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #F
#echo -n $temp6"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #G
#echo -n $temp7"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #H
#echo -n $temp8"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #I
#echo -n $temp9"; " >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt #J
#
#------------
date +"%Y/%m/%d %H:%M" >> /home/development/Temperatur/$(date +"%Y")_Temp/$(date +"%Y%m")_Sensor_A-E.txt
#Warteintervall z.b. 10s = 10 sekunden; 5m = 5 minuten
#sleep 30m
#
#done
#
#Adr. http://www.tippscout.de/bash-echo-zeilenumbruch_tipp_5937.html