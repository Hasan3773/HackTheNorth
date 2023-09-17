''' Demonstrates how to subscribe to and handle data from gaze and event streams '''


import time

import adhawkapi
import adhawkapi.frontend
from pyquaternion import Quaternion
import numpy
import math
import turtle
import socket

lastx = None
lasty = None    
BLINK_TIME = 2
x1 = None
y1 = None
x2 = None
y2 = None
twoPoint = False
LastBlink = 0

""" #socket setup
port = 8833 #just some random number
host = '192.168.137.139' #server port

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM) #create socket
s.bind((host, port)) #connect to socket
s.listen(5) #start listening for connections from the client

#debug
print("Socket initialized")
print(host)

while True:
    clientsocket, address = s.accept() #yield for client conenction and set vars to client data
    print(f"Connection from {address} has been established.") """


class FrontendData:
    ''' BLE Frontend ''' 
    

    def __init__(self):
        # Instantiate an API object
        # TODO: Update the device name to match your device\
        self._api = adhawkapi.frontend.FrontendApi(ble_device_name='ADHAWK MINDLINK-304')


        # Tell the api that we wish to receive eye tracking data stream
        # with self._handle_et_data as the handler
        self._api.register_stream_handler(adhawkapi.PacketType.EYETRACKING_STREAM, self._handle_et_data)


        # Tell the api that we wish to tap into the EVENTS stream
        # with self._handle_events as the handler
        self._api.register_stream_handler(adhawkapi.PacketType.EVENTS, self._handle_events)


        # Start the api and set its connection callback to self._handle_tracker_connect/disconnect.
        # When the api detects a connection to a MindLink, this function will be run.
        self._api.start(tracker_connect_cb=self._handle_tracker_connect,
                        tracker_disconnect_cb=self._handle_tracker_disconnect)
        
        global LastBlink
        LastBlink = 0
        


    def shutdown(self):
        '''Shutdown the api and terminate the bluetooth connection'''
        self._api.shutdown()


    @staticmethod
    def _handle_et_data(et_data: adhawkapi.EyeTrackingStreamData):
        ''' Handles the latest et data '''
        uvec = None
        mag = None
        global lastx
        global lasty

        if et_data.gaze is not None:
            xvec, yvec, zvec, vergence = et_data.gaze
            mag = math.sqrt(xvec**2 + yvec**2 + zvec**2)
            uvec = numpy.array([xvec/mag, yvec/mag, zvec/mag])
            #print(f'Gaze={xvec:.2f},y={yvec:.2f},z={zvec:.2f},vergence={vergence:.2f}')


        if et_data.eye_center is not None:
            if et_data.eye_mask == adhawkapi.EyeMask.BINOCULAR:
                rxvec, ryvec, rzvec, lxvec, lyvec, lzvec = et_data.eye_center
               # print(f'Eye center: Left=(x={lxvec:.2f},y={lyvec:.2f},z={lzvec:.2f}) '
                    #  f'Right=(x={rxvec:.2f},y={ryvec:.2f},z={rzvec:.2f})')


        if et_data.pupil_diameter is not None:
            if et_data.eye_mask == adhawkapi.EyeMask.BINOCULAR:
                rdiameter, ldiameter = et_data.pupil_diameter
                #print(f'Pupil diameter: Left={ldiameter:.2f} Right={rdiameter:.2f}')

        rotator = None
        if et_data.imu_quaternion is not None:
            if et_data.eye_mask == adhawkapi.EyeMask.BINOCULAR:
                x, y, z, w = et_data.imu_quaternion
                rotator = Quaternion(axis=[x, y, z], angle=w)
                #print(f'IMU: x={x:.2f},y={y:.2f},z={z:.2f},w={w:.2f}')


        #print("--------------------")
        #print(str(rotator))
        #print(str(uvec))
        #print(str(mag))
        
        if rotator is not None and uvec is not None and mag is not None:
            rvec = rotator.rotate(uvec)
            absvec = numpy.array([rvec[0] * mag, rvec[1] * mag, rvec[2] * mag])

            if absvec[0] is not None:
                lastx = absvec[0]
            if absvec[2] is not None:
                lasty = absvec[2]

     #   print("--------------------")

    @staticmethod
    def _handle_events(event_type, timestamp, *args):
        global LastBlink
        global twoPoint
        global lastx
        global lasty
        global x1
        global y1
        global x2
        global y2

        if event_type == adhawkapi.Events.BLINK:
            duration = args[0]
            #print(duration)

            if timestamp - LastBlink < 0.8:
                print("Double blink")
                if twoPoint:
                    x2 = lastx
                    y2 = lasty
                    print(str(x2)+","+str(y2))
                    # do the calc and send to robot

                    #distance
                    dist = math.sqrt((max(y1, y2) - min(y1, y2))**2 + (max(x1,x2) - min(x1, x2))**2)

                    #angle
                    Clength = math.sqrt(abs(x2-x1)**2 + (abs(y2-y1)+1)**2)
                    print("------")
                    print((1+dist**2-Clength**2)/(2*dist*1))
                    print(dist)
                    print(Clength)
                    print("------")
                    Cangle = math.acos((1+dist**2-Clength**2)/(2*dist*1))
                    if (x2 < x1):
                        Cangle = -Cangle

                    #network logic
                    print("Dist: " + str(dist))
                    print("Angle: " + str(Cangle))

                else: 
                    x1 = lastx
                    y1 = lasty
                    print(str(x1)+","+str(y1))

                twoPoint = not twoPoint

            LastBlink = timestamp
            print(f'Got blink: {timestamp} {duration}')
        if event_type == adhawkapi.Events.EYE_CLOSED:
            eye_idx = args[0]
            #print(f'Eye Close: {timestamp} {eye_idx}')
        if event_type == adhawkapi.Events.EYE_OPENED:
            eye_idx = args[0]
            #print(f'Eye Open: {timestamp} {eye_idx}')
   

        

    def _handle_tracker_connect(self):
        print("Tracker connected")
        self._api.set_et_stream_rate(60, callback=lambda *args: None)


        self._api.set_et_stream_control([
            adhawkapi.EyeTrackingStreamTypes.GAZE,   
            adhawkapi.EyeTrackingStreamTypes.EYE_CENTER,
            adhawkapi.EyeTrackingStreamTypes.PUPIL_DIAMETER,
            adhawkapi.EyeTrackingStreamTypes.IMU_QUATERNION,
        ], True, callback=lambda *args: None)


        self._api.set_event_control(adhawkapi.EventControlBit.BLINK, 1, callback=lambda *args: None)
        self._api.set_event_control(adhawkapi.EventControlBit.EYE_CLOSE_OPEN, 1, callback=lambda *args: None)


    def _handle_tracker_disconnect(self):
        print("Tracker disconnected")

def main():
    print("hi")
    ''' App entrypoint '''
    frontend = FrontendData()
    try:
        while True:
            time.sleep(1)
    except (KeyboardInterrupt, SystemExit):
        frontend.shutdown()

        
if __name__ == '__main__':
    main()
