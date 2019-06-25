from flask import Flask,jsonify,render_template
import json
import serial
import time
import socket
global t
food='0'
water='0'
weight='0'


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



app = Flask(__name__)

data = {}

@app.route('/')
def hello_world():
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
        
    data["food"]=food
    data["water"]=water
    data["weight"]=weight
    return json.dumps(testInfo)



if __name__ == '__main__':
    t=serial.Serial("com10",9600)
    app.run(host='localhost',
            port=5000,
            debug=True)
    
    
    #t.open()
    
    
    

    

