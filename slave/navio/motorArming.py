import sys
import time

import navio.pwm
import navio.util
import datetime

navio.util.check_apm()

PWM_OUTPUT = 13
SERVO_MIN = 1.1 #ms
SERVO_NOM = 1.500 #ms
SERVO_MAX = 1.9
def loop_for(seconds, func, *arg):
    endtime = datetime.datetime.now() +datetime.timedelta(seconds = seconds)

    while True:
        if datetime.datetime.now() >= endtime:
            break
        func(*arg)

def main():
    pwm = navio.pwm.PWM(PWM_OUTPUT)
    pwm.initialize()
    pwm.set_period(50)
    pwm.enable()

    loop_for(2,pwm.set_duty_cycle, SERVO_MAX)
    loop_for(2,pwm.set_duty_cycle, SERVO_MIN)
    loop_for(2,pwm.set_duty_cycle, SERVO_NOM)
    
    while(True):
        loop_for(1, pwm.set_duty_cycle, 1.3)
main()
