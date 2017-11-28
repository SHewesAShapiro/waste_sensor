#Cell culture waste sensor (additional email functionality)
#Alyssa Shapiro and Sarah Hewes 2017
#When run approximately every 15 minutes on a chrontab, this code will allow the raspberry pi to obtain serial information from
#the circuit playground and send emails to the student and PI involved with cell culture maintance

import serial
import time
import smtplib

#open the serial port
ser = serial.Serial('/dev/ttyACM0', 9600)

#pause while the serial feed fills
time.sleep(10)

#read a line from the serial feed
read_serial = ser.readline()

#initialize email information
smtpUser = 'alyssamshapiro@gmail.com'
smtpPass = '********' #password redacted
gradstudent = 'sh62@rice.edu'
fromAdd = smtpUser

s = smtplib.SMTP('smtp.gmail.com',587)
s.ehlo()
s.starttls()
s.ehlo()

s.login(smtpUser,smtpPass)

#if the serial feed shows various keywords then send emails of increasing urgency
#first two emails go to the student. the last one goes to the PI
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
