import socket
from time import sleep

port = 8833 #just some random number
host = '192.168.137.139' #server port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #create socket
s.connect((host, port)) #connect to the socket

print("Successfully connected to server")

#this sends the data
s.send(bytes(str(2).encode('utf-8'))) 
