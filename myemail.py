import serial
import time
import smtplib

#open the serial port
ser = serial.Serial('/dev/ttyACM0', 9600)

time.sleep(5)

read_serial = ser.readline()

smtpUser = 'alyssamshapiro@gmail.com'
smtpPass = 'dancechica'
gradstudent = 'sh62@rice.edu'

fromAdd = smtpUser

s = smtplib.SMTP('smtp.gmail.com',587)
s.ehlo()
s.starttls()
s.ehlo()

s.login(smtpUser,smtpPass)


if read_serial.find("kitten") > -1: 
	subject = 'Its your turn to change the waste container!'
	header = 'To: ' + gradstudent + '\n' + 'From: ' + fromAdd + '\n' + 'Subject: ' + subject
	body = 'Please empty the waste container! This is your FIRST warning.'  
	print header + '\n\n' + body
	s.sendmail(fromAdd, gradstudent, header + '\n\n' + body)
elif read_serial.find("cat") > -1:
	subject = 'Its your turn to change the waste container! SECOND WARNING!'
	header = 'To: ' + gradstudent + '\n' + 'From: ' + fromAdd + '\n' + 'Subject: ' + subject
	body = 'Please empty the waste container! This is your SECOND warning, Next, I will email your PI!' 
	print header + '\n\n' + body
	s.sendmail(fromAdd, gradstudent, header + '\n\n' + body) 
elif read_serial.find("tiger") > -1:
	subject = 'Your grad student has not emptied the waste flask!'
	header = 'To: ' + smtpUser + '\n' + 'From: ' + fromAdd + '\n' + 'Subject: ' + subject
	body = 'Sarah Hewes has neglected to empty the waste flask!' 
	print header + '\n\n' + body
	s.sendmail(fromAdd, smtpUser, header + '\n\n' + body) 
else:
	print "normal operation"

s.quit()
