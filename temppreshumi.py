#!/usr/bin/env python
#coding: utf-8


from time import sleep
from datetime import datetime
from subprocess import check_output

i2cBus=0
i2cDevice=0x76
interval=10


logfile=open("temppreshumi.log","a")

logfile.write("{msg:'Start at "+datetime.now().isoformat()+"'}"+'\n')

def setup():    
  pass


def readData():

    lecture=check_output(["./getbme280json"])
    print(lecture)
    logfile.write("{time:'"+datetime.now().isoformat()+"',"+
        "data:"+lecture+"}"+'\n')
    logfile.flush()

def loop():
  global interval
  while True:
    sleep(interval)
    readData()

if __name__ == '__main__':     # Program start from here
  setup()
  try:
    loop()
  except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed.
    logfile.close()
    destroy()

