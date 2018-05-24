# -*- coding: utf-8 -*-
"""
Autor: Julio Angulo
"""
import numpy as np
import cv2

#cap = cv2.VideoCapture('vtest.avi')
#
#fgbg = cv2.createBackgroundSubtractorMOG2()
#
#while(1):
#    ret, frame = cap.read()
#
#    fgmask = fgbg.apply(frame)
#
#    cv2.imshow('frame',fgmask)
#    k = cv2.waitKey(30) & 0xff
#    if k == 27:
#        break
#
#cap.release()
#cv2.destroyAllWindows()

cap = cv2.VideoCapture(0)

while(True):
    # Capture frame-by-frame
    ret, frame = cap.read()

    # Our operations on the frame come here
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # Display the resulting frame
    cv2.imshow('frame',gray)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
