# -*- coding: utf-8 -*-
"""
Autor: Julio Angulo
"""
import cv2
import cvGui

MIN_AREA = 150

if __name__=="__main__":

    WIN_NAMES = ["background",
               "Morphologycal operation",
               "image raw",
               "blurred"]
    
    video = 0#"../videos/people_walking_test_video1.mp4"
    cap = cv2.VideoCapture(video)
    fgbg = cv2.bgsegm.createBackgroundSubtractorMOG()
    
    # creating window   
    window = cvGui.Window("Test",
                          cap.get(cv2.CAP_PROP_FRAME_HEIGHT),
                          cap.get(cv2.CAP_PROP_FRAME_WIDTH),
                          2,2)   
    window.create()
    
    key = 0;
    while(key != ord('q')):
        # Capture frame-by-frame
        ret, frame = cap.read()
        if ret == False:
            break #video ended or camera failed
            
        blur = cv2.GaussianBlur(frame, (5,5), 10)
        fgmask = fgbg.apply(blur)
        
        window.update(blur, (0,1))
        window.update(fgmask, (1,1), "binary")

        #dilate 
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))
        morph_op = cv2.morphologyEx(fgmask, 
                                    cv2.MORPH_CLOSE, 
                                    kernel, 
                                    iterations=5)
        
        window.update(morph_op, (1,0), "binary")
        
        # finding contours
        _, contours, hierarchy = cv2.findContours(fgmask, cv2.RETR_EXTERNAL, 
                                    cv2.CHAIN_APPROX_SIMPLE)
        
        #drawing bounding boxes
        for c in contours:
            if cv2.contourArea(c) > MIN_AREA:
                x,y,w,h = cv2.boundingRect(c)
                cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
        
        window.update(frame, (0,0))   
        window.show()
        
        #TODO: add ROi
        key = cv2.waitKey(1)
        
    
    # When everything done, release the capture
    cap.release()
    window.destroy()
