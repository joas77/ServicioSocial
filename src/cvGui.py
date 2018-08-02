# -*- coding: utf-8 -*-
"""
Created on Wed Jul 25 22:19:26 2018

@author: Julio
"""
import numpy as np
import cv2

class Window:
    def __init__(self, win_name, h, w, rows=1, columns=1):
        self.h = int(h)
        self.w = int(w)
        self.name = win_name
        self._frame = np.zeros((self.h*rows, self.w *columns,3), dtype="uint8")
    
    def create(self):
        cv2.namedWindow(self.name, cv2.WINDOW_NORMAL)
    
    def destroy(self):
        cv2.destroyWindow(self.name)
        
    def update(self, frame, position=(0,0), imtype="bgr"):
        """ Update the images in frame
        arguments
        frame -- shall be an OpenCV BGR image
        position -- tuple (row, column) 
        """
        row, column = position
        #TODO: throw error if image is not supported
        # or correct format not provided in imtype
        if imtype != "bgr":
            frame = self._convert2BGR(frame, imtype)
        
        self._frame[row*self.h : (row+1)*self.h, 
                    column*self.w : (column+1)*self.w] = frame
    
    def _convert2BGR(self, frame, imtype):
        if imtype == "gray" or imtype == "binary":
            frame = cv2.cvtColor(frame, cv2.COLOR_GRAY2BGR)
        
        return frame
    
    def show(self):
        cv2.imshow(self.name, self._frame)
        
    
#tests 
if __name__=="__main__":
    cap = cv2.VideoCapture(0)
    
    key = 0
    
    win = Window("Test",
                 cap.get(cv2.CAP_PROP_FRAME_HEIGHT),
                 cap.get(cv2.CAP_PROP_FRAME_WIDTH),
                 3,2)
    win.create()
    
    while key!= ord('q'):
        ok, frame = cap.read()
        blur = cv2.GaussianBlur(frame, (13,13), 0)
        gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
        win.update(frame)
        win.update(blur, (0,1))
        win.update(frame,(1,0))
        win.update(gray,(1,1), "gray")
        win.show()
        
        key = cv2.waitKey(1)
        
    cap.release()
    win.destroy()