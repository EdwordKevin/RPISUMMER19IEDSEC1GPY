import serial
import time
import socket

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



'''
import hashlib
import base64
import struct

HOST="localhost"
PORT="5000"

def handshake(con):
    headers = {}
    shake = con.recv(1024)
 
    if not len(shake):
        return False
 
    header, data = shake.split(bytes('\r\n\r\n','utf-8'), 1)
    for line in header.split(bytes('\r\n',"utf-8"))[1:]:
        key, val = line.split(bytes(': ',"utf-8"), 1)
        headers[key.decode("utf-8")] = val.decode("utf-8")
    print(headers)
    if 'Sec-WebSocket-Key' not in headers:
        print ('This socket is not websocket, client close.')
        con.close()
        return False
 
    sec_key = headers['Sec-WebSocket-Key']
    res_key = base64.b64encode(hashlib.sha1((sec_key + MAGIC_STRING).encode("utf-8")).digest())
 
    str_handshake = HANDSHAKE_STRING.replace('{1}', res_key.decode("utf-8")).replace('{2}', HOST + ':' + str(PORT))
    print(str_handshake)
    con.send(bytes(str_handshake,"utf-8"))
    return True

def recv_data(con, num):
    try:
        all_data = con.recv(num)
        if not len(all_data):
            return False
    except:
        return False
    else:
        code_len = ord(all_data[1]) & 127
        if code_len == 126:
            masks = all_data[4:8]
            data = all_data[8:]
        elif code_len == 127:
            masks = all_data[10:14]
            data = all_data[14:]
        else:
            masks = all_data[2:6]
            data = all_data[6:]
        raw_str = ""
        i = 0
        for d in data:
            raw_str += chr(ord(d) ^ ord(masks[i % 4]))
            i += 1
        return raw_st

def send_data(con, data):
    if data:
        data = str(data)
    else:
        return False
    token = "\x81"
    length = len(data)
    if length < 126:
        token += struct.pack("B", length).decode("utf-8")
    elif length <= 0xFFFF:
        token += struct.pack("!BH", 126, length).decode("utf-8")
    else:
        token += struct.pack("!BQ", 127, length).decode("utf-8")
    data = '%s%s' % (token, data)
    con.send(bytes(data,"utf-8"))
    return True



MAGIC_STRING = '258EAFA5-E914-47DA-95CA-C5AB0DC85B11'
HANDSHAKE_STRING = "HTTP/1.1 101 Switching Protocols\r\n" \
    "Upgrade:websocket\r\n" \
      "Connection: Upgrade\r\n" \
      "Sec-WebSocket-Accept: {1}\r\n" \
      "WebSocket-Location: ws://{2}/chat\r\n" \
      "WebSocket-Protocol:chat\r\n\r\n"

'''

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
    print(water+":"+food+":"+weight)


    
