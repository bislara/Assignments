import cv2
import numpy as np

img = cv2.imread('image.png')
cv2.namedWindow('red color')
cv2.namedWindow('blue color')
cv2.namedWindow('yellow color')
cv2.namedWindow('original')
while(1):

	hsv=cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
	
	#definig the range of red color
	red_lower=np.array([0,55,0])
	red_upper=np.array([18,255,255])

	#defining the Range of Blue color
	blue_lower=np.array([79,171,83])
	blue_upper=np.array([133,255,255])
	
	#defining the Range of yellow color
	yellow_lower=np.array([22,60,200])
	yellow_upper=np.array([60,255,255])

	#finding the range of red,blue and yellow color in the image
	red=cv2.inRange(hsv, red_lower, red_upper)
	blue=cv2.inRange(hsv,blue_lower,blue_upper)
	yellow=cv2.inRange(hsv,yellow_lower,yellow_upper)
	
	#Morphological transformation, Dilation  	
	kernal = np.ones((5 ,5),np.uint8)

        red=cv2.dilate(red, kernal)
	res=cv2.bitwise_and(img, img, mask = red)

	blue=cv2.dilate(blue,kernal)
	res1=cv2.bitwise_and(img, img, mask = blue)

	yellow=cv2.dilate(yellow,kernal)
	res2=cv2.bitwise_and(img, img, mask = yellow) 
	cv2.imshow('original',img)
	cv2.imshow('red color',res)
	cv2.imshow('blue color',res1)
	cv2.imshow('yellow color',res2)

        k = cv2.waitKey(0)
   	if k == 27:
       	     break


cv2.destroyAllWindows()
   
