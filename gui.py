#import
from Tkinter import *
import RPi.GPIO as GPIO

#variables
x=11
y=12
xs=0
ys=90
yss=40

#setup
GPIO.setmode(GPIO.BOARD)
GPIO.setup(x,GPIO.OUT)
GPIO.setup(y,GPIO.OUT)
pwmx=GPIO.PWM(x,50)
pwmy=GPIO.PWM(y,50)
pwmx.start(5)
pwmy.start(2)

#events
def UP():
	global ys
	ys=9.0/180.*(yss+20)+2
        pwmy.ChangeDutyCycle(ys)
def DOWN():
	global ys
	ys=9.0/180.0*(yss-20)+2
        pwmy.ChangeDutyCycle(ys)

#GUI
window = Tk()
window.title("Control")
window.geometry('210x260')


up = Button(window, text = u"\u2191", command=UP)
up.config(height=5,width=5)
up.grid(column=2,row=0)

down = Button(window, text = u"\u2193", command=DOWN)
down.config(height=5,width=5)
down.grid(column=2,row=5)

right = Button(window, text = u"\u2192")
right.config(height=5,width=5)
right.grid(column=3,row=4)

left = Button(window, text = u"\u2190")
left.config(height=5,width=5)
left.grid(column=1,row=4)

window.mainloop()
pwmx.stop()
pwmy.stop()
GPIO.cleanup()
