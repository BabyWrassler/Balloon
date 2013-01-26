#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# enable debugging
import cgitb
cgitb.enable()
import cgi
import serial
import time
import json

#-------Start the HTML document-------
print "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8' />" 
print "<title>JSON Display of Balloon Telemetry</title> "
print "<style type='text/css'><!--@import url('style.css');--></style></head> <body>"

#-------Open the serial port-------
try:
   ser = serial.Serial('/dev/ttyAMA0', 9600, timeout=1)
   #print "Serial port opened as: ",ser,"<br><br>\n"
except:
   print "Failed to open serial connection on /dev/ttyAMA0"

#-------Get the data from the Arduino----------
ser.write("10\n") # Request a number of data frames from the Arduino. I've tested up to 100, and the Arduino code is set to accept between 1 and 100.
# Other numbers like zero or 1000 could be used to issue commands for other functions like rebooting
time.sleep(1) # Wait for the data to arrive
rawdata = ser.readline() # Read the next line waiting in the buffer
#print "Raw data:",rawdata, "<br>\n"
ser.flushInput() # At least for testing purposes, clear any leftovers
data = json.loads(rawdata[:len(rawdata)-1]) # Convert the data to JSON after stripping the newline

#-------How many frames came-------
#if (data[0] != "1"):
#   print data[0], " data frames<br>"
#else:
#   print data[0], " data frame<br>"

#-------Display the data in an HTML table---------
# Print the header row
print "<table id='hor-zebra'><thead><tr><th>&nbsp;</th><th>Time</th><th>Lat</th><th>Lon</th><th>Alt</th><th>GX</th><th>GY</th><th>GZ</th><th>AX</th><th>AY</th><th>AZ</th><th>MX</th><th>MY</th><th>MZ</th><th>Pres</th><tr></thead><tbody>"
i = 1 # Skip data[0] because it just contains the total number of frames sent
while i < len(data):
   if (i%2)!=0:
      print "<tr class='odd'>"
   else:
      print "<tr>"
   print "<td>", i, "</td>"
   print "<td>", data[i]['timestamp'], "</td>"
   print "<td>", data[i]['latitude'], "</td>"
   print "<td>", data[i]['longitude'], "</td>"
   print "<td>", data[i]['altitude'], "</td>"
   print "<td>", data[i]['gxaxis'], "</td>"
   print "<td>", data[i]['gyaxis'], "</td>"
   print "<td>", data[i]['gzaxis'], "</td>"
   print "<td>", data[i]['axaxis'], "</td>"
   print "<td>", data[i]['ayaxis'], "</td>"
   print "<td>", data[i]['azaxis'], "</td>"
   print "<td>", data[i]['mxaxis'], "</td>"
   print "<td>", data[i]['myaxis'], "</td>"
   print "<td>", data[i]['mzaxis'], "</td>"
   print "<td>", data[i]['pressure'], "</td>"
   i = i+1
   print "</tr>"
print "</tbody></table>"

#------Close the HTML Document
print "</body></html>"
