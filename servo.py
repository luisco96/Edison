import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
x=11
GPIO.setup(x,GPIO.OUT)
pwm=GPIO.PWM(11,50)
pwm.start(5)
for i in range(0,20):
	p1= input("Give me that angle bae: ")
	DC=9.0/180.0*p1+2
	pwm.ChangeDutyCycle(DC)
pwm.stop()
GPIO.cleanup()
