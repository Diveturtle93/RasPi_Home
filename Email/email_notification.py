import smtplib
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

class EmailNotification:
	def __init__(self, server, user, empfaenger, passwd):
		self.server = server
		self.user = user
		self.pwd = passwd
		self.from_addr = user
		self.to_addr = empfaenger
		
	def __betreff(self, txtdata):
		msg = MIMEMultipart()
		self.subject = txtdata
		msg['Subject'] = self.subject
		msg['From'] = self.from_addr
		msg['To'] = self.to_addr
		return msg
		
	def send(self):
		msg = MIMEMultipart()
		msg = self.__betreff('[Raspi] Reboot')
		msg.preamble = self.subject
		msg.attach(MIMEText('System wurde erfolgreich neu gestartet.'))
		self.__send_email(msg)
		
	def send_text(self, txt_file):
		msg = MIMEMultipart()
		msg = self.__betreff('[Raspi] Temperatur')
		msg.preamble = self.subject
		msg.attach(MIMEText('Die woechentliche Email mit der Temperatur'))
		msg.attach(self.__read_txt(txt_file))
		self.__send_email(msg)

	def send_image(self, image_file):
		msg = MIMEMultipart()
		msg = self.__betreff('[Raspi] Alarmanlage')
		msg.preamble = self.subject
		msg.attach(MIMEText('Alarm, Alarm'))
		msg.attach(self.__read_image(image_file))
		self.__send_email(msg)

	def __read_image(self, image_file):
		datei = MIMEImage(open(image_file, 'rb').read())
		datei["Content-Type"] = 'application/octet-stream'
		datei["Content-Disposition"] = 'attachment; filename=' + image_file
		return datei
		
	def __read_txt(self, txt_file):
		datei = MIMEText(open(txt_file, 'rb').read(), 'base64', 'utf-8')
		datei["Content-Type"] = 'application/octet-stream'
		datei["Content-Disposition"] = 'attachment; filename=' + txt_file
		return datei

	def __send_email(self, massage):
		try:
			server = smtplib.SMTP(self.server)
			server.ehlo()
			server.starttls()
			server.login(self.user, self.pwd)
			server.sendmail(self.from_addr, self.to_addr.split(','), massage.as_string())
			server.quit()
		except smtplib.SMTPException:
			print("SMTP-Fehler")
