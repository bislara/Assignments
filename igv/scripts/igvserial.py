#!/usr/bin/env python

import time
import serial
import rospy
from igv.msg import drivedata

ch='t'
ser = serial.Serial('/dev/ttyUSB0', 9600)
def callback(data):
   ch=str(unichr(data.drive))
   print(ch)
   #time.sleep(0.3)
   ser.write(ch)

def main_fun():
   rospy.init_node('igvserial')
   rospy.Subscriber("drive_pub", drivedata, callback)
   rospy.spin()
  

if __name__ == '__main__':
  try:
   main_fun() 
  except rospy.ROSInterruptException:
   pass    

