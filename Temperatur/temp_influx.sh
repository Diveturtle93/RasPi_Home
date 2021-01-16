#!/bin/bash
#
#Temperatur auslesen:
#tempread=`cat /sys/bus/w1/devices/28-8000001f94ba/w1_slave`
#-------------------------------
#tempread0=`cat /sys/bus/w1/devices/28-8000001f77cb/w1_slave` #S0 = A
#tempread1=`cat /sys/bus/w1/devices/28-8000001f7884/w1_slave` #S1 = B
#tempread2=`cat /sys/bus/w1/devices/28-8000001f942f/w1_slave` #S2 = C
#tempread3=`cat /sys/bus/w1/devices/28-8000001f77c4/w1_slave` #S3 = D
#tempread4=`cat /sys/bus/w1/devices/28-8000001f9369/w1_slave` #S4 = E
#tempread5=`cat /sys/bus/w1/devices/28-8000001f934d/w1_slave` #S5 = F
#tempread6=`cat /sys/bus/w1/devices/28-8000001f7752/w1_slave` #S6 = G
#tempread7=`cat /sys/bus/w1/devices/28-8000001f9453/w1_slave` #S7 = H
#tempread8=`cat /sys/bus/w1/devices/28-8000001f94ce/w1_slave` #S8 = I
#tempread9=`cat /sys/bus/w1/devices/28-8000001f94ba/w1_slave` #S9 = J
#
#Formatieren:
#temp=`echo "scale=2; "\`echo ${tempread##*=}\`" / 1000" | bc`
#-------------------------------
temp0=20.156
temp1=29.382
#temp0=`echo "scale=2; "\`echo ${tempread0##*=}\`" / 1000" | bc`
#temp1=`echo "scale=2; "\`echo ${tempread1##*=}\`" / 1000" | bc`
#temp2=`echo "scale=2; "\`echo ${tempread2##*=}\`" / 1000" | bc`
#temp3=`echo "scale=2; "\`echo ${tempread3##*=}\`" / 1000" | bc`
#temp4=`echo "scale=2; "\`echo ${tempread4##*=}\`" / 1000" | bc`
#temp5=`echo "scale=2; "\`echo ${tempread5##*=}\`" / 1000" | bc`
#temp6=`echo "scale=2; "\`echo ${tempread6##*=}\`" / 1000" | bc`
#temp7=`echo "scale=2; "\`echo ${tempread7##*=}\`" / 1000" | bc`
#temp8=`echo "scale=2; "\`echo ${tempread8##*=}\`" / 1000" | bc`
#temp9=`echo "scale=2; "\`echo ${tempread9##*=}\`" / 1000" | bc`
#
#Schreiben in Datenbank
#-------------------------------
curl -i -XPOST 'http://localhost:8086/write?db=vereinsheim' --data 'vereinsheim,Sensor=Temp1 Wert='${temp0}',Einheit="°C"'
curl -i -XPOST 'http://localhost:8086/write?db=vereinsheim' --data 'vereinsheim,Sensor=Temp2 Wert='${temp1}',Einheit="°C"'
#curl -i -XPOST 'http://localhost:8086/write?db=vereinsheim' --data 'vereinsheim,Sensor=Temp3 Wert='${temp2}',Einheit="°C"';
#curl -i -XPOST 'http://localhost:8086/write?db=vereinsheim' --data 'vereinsheim,Sensor=Temp4 Wert='${temp3}',Einheit="°C"';
#curl -i -XPOST 'http://localhost:8086/write?db=vereinsheim' --data 'vereinsheim,Sensor=Temp5 Wert='${temp4}',Einheit="°C"';
#-------------------------------