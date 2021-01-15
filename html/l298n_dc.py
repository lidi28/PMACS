
#!/usr/bin/env python

import RPi.GPIO as GPIO          
from time import sleep

plantsNum = 8

in1 = 24
in2 = 23
en = 25

switch1 = 21
dest = 1

GPIO.setmode(GPIO.BCM)
GPIO.setup(in1,GPIO.OUT)
GPIO.setup(in2,GPIO.OUT)
GPIO.setup(en,GPIO.OUT)
GPIO.setup(switch1, GPIO.IN, pull_up_down=GPIO.PUD_UP)

GPIO.output(in1,GPIO.LOW)
GPIO.output(in2,GPIO.LOW)

p=GPIO.PWM(en,1000)

p.start(25)

def inspect():
    for i in range(plantsNum):
        print("Inspecting")
        sleep(3)
        
        moveToNext()
    GPIO.cleanup()

def moveToNext():
    global dest
    seconds = 60
    if (dest == 1):
        print("Moving Forward")
        GPIO.output(in1,GPIO.HIGH)
        GPIO.output(in2,GPIO.LOW)
    else:
        print("Moving Backwards")
        GPIO.output(in1,GPIO.LOW)
        GPIO.output(in2,GPIO.HIGH)

    while seconds > 0:
        if GPIO.input(switch1) == 0:    
            print("Aborted") 
            GPIO.output(in1,GPIO.LOW)
            GPIO.output(in2,GPIO.LOW)
            seconds = -1
            dest = 0
        seconds = seconds - 1
        sleep(0.05)
    print("Stopped")


def ledTest():
    GPIO.setup(17, GPIO.OUT)
    print "LED on"
    GPIO.output(17, GPIO.HIGH)
    sleep(10)
    print "LED off"
    GPIO.output(17, GPIO.LOW)
    GPIO.cleanup()
