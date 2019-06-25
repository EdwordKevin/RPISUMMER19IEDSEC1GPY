import serial
import time
import os,sys

def read(t):
    a=""
    while(True):
        x=t.read().decode("utf-8") 
        if(x=='%'): break
    while(True):
        x=t.read().decode("utf-8") 
        if(x=='%'): break
        a+=x
    return a

def write(t,data):
    t.write(bytes("%"+data+"%", "utf-8"))


t=serial.Serial("com10",9600)
#t.open()


food='0'
water='0'
weight='0'
while(True):  
    v = read(t)
    if(v=="new connection"):
        write(t,"connecting request")
    if(v=="date"):
        write(t,'10%%10%%10')
    if(v=="weight"):
        write(t,"no data")
    if(v=="connection check"):
        write(t,"connecting")
    if(v=="cfg"):
        write(t,"old")
    if(v=="data"):
        water=read(t)
        food=read(t)
        weight=read(t)
    if(water!="0"):break
sys.stdout.write("{"+'"water":{},"food":{},"weight":{}'.format(water,food,weight)+"}")





    
