import cv2
import numpy as np


def nothing(x):
    pass
cv2.namedWindow('result')
cv2.namedWindow('rest')
#cv2.namedWindow('canny')

cv2.createTrackbar('hmin', 'result',0,180,nothing)
cv2.createTrackbar('hmax', 'result',0,180,nothing)
cv2.createTrackbar('smin', 'result',0,255,nothing)
cv2.createTrackbar('smax', 'result',0,255,nothing)
cv2.createTrackbar('vmin', 'result',0,255,nothing)
cv2.createTrackbar('vmax', 'result',0,255,nothing)

#cv2.createTrackbar('h', 'rest',0,180,nothing)
#cv2.createTrackbar('s', 'rest',0,255,nothing)
#cv2.createTrackbar('v', 'rest',0,255,nothing)
 
img=cv2.imread('image.png')

while(1):

    hsv = cv2.cvtColor(img,cv2.COLOR_BGR2HSV)

    hlo = cv2.getTrackbarPos('hmin','result')
    hup = cv2.getTrackbarPos('hmax','result')
    slo = cv2.getTrackbarPos('smin','result')
    sup = cv2.getTrackbarPos('smax','result')
    vlo = cv2.getTrackbarPos('vmin','result')
    vup = cv2.getTrackbarPos('vmax','result')

   # h = cv2.getTrackbarPos('h','rest')
   # s = cv2.getTrackbarPos('s','rest')
   # v = cv2.getTrackbarPos('v','rest')

    min = np.array([hlo,slo,vlo])
    max = np.array([hup,sup,vup])

    mask = cv2.inRange(hsv,min,max)

    result = cv2.bitwise_and(img,img,mask = mask)
    hello=cv2.medianBlur(result,15)
    #blur = cv2.GaussianBlur(result,(15,15),0)
    kernel = np.ones((5,5),np.uint8)
    erosion = cv2.erode(mask,kernel,iterations = 1)
   # dilation = cv2.dilate(mask,kernel,iterations = 1)
    #edges = cv2.Canny(frame,100,200)
 
   
    cv2.imshow('result',hello)
   
   # cv2.imshow('Gaussian Blurring',blur)
    #cv2.imshow('frame',frame)
    cv2.imshow('rest',img)
   #cv2.imshow('mask',mask)
   #cv2.imshow('hsv',hsv)
    #cv2.imshow('median',hello)
    #cv2.imshow('rest',result1)
    #cv2.imshow('erosion',erosion)
    #cv2.imshow('dilation',dilation)
    k = cv2.waitKey(1)
    if k == 27:
        break


cv2.destroyAllWindows()

