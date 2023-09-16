import socket
from time import sleep

#socket params
port = 8383
host = '192.168.137.139' 

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #create socket
s.bind((host, port)) #connect to socket
s.listen(5) #start listening for connections from the client

#debug
print("Socket initialized")
print(host)

while True:
    clientsocket, address = s.accept() #yield for client conenction and set vars to client data
    print(f"Connection from {address} has been established.")

    v = clientsocket.recv(8).decode('utf-8') #yield until data is recieved from client and set data
    #do stuff with your data

    #you could leave it here. The below code allows the loop to exit if the client sends an "end" message
    #so you can get connections from other clients rather than waiting for one that is gone. 
    
    while v != "end":
        v = clientsocket.recv(8).decode('utf-8')
        #do stuff with your data

    print("Client disconnected")
