#!/usr/bin/python
from email_notification import *
import sys
import time
import ConfigParser

config = ConfigParser.RawConfigParser()
config.read('/home/development/Email/config.ini')

EMAIL_SERVER = config.get('Server', 'Serveradresse')
EMAIL_USER = config.get('Server', 'User')
EMAIL_EMPFAENGER = config.get('Server', 'Empfaenger')
EMAIL_PASSWD = config.get('Server', 'Passwd')

notifier = EmailNotification(EMAIL_SERVER, EMAIL_USER, EMAIL_EMPFAENGER, EMAIL_PASSWD)

timeyear = time.strftime('%Y')
timestr = time.strftime('%Y%m')

if (sys.argv[1] == "-w"):
	notifier.send()
elif (sys.argv[1] == "-t"):
	notifier.send_text('/home/development/Temp/'+timeyear+'_Temp/'+timestr+'_Sensor_A-E.txt')
elif (sys.argv[1] == "-b"):
	notifier.send_image('abc.png')
elif (sys.argv[1] == "-m"):
	notifier.send_text('/home/development/Temp/'+timeyear+'_Temp/'+timeyear+sys.argv[2]+'_Sensor_A-E.txt')
else:
	fprintf("Falsche Argumente")
