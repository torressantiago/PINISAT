#import the socket module
import socket
import sys

# Variable initialization
indexIMU = 0
indexGPS = 0
IMUFlag = 0
GPSFlag = 0
IMU = []
IMU_rec = []
GPS = []
GPS_rec = []

#create the server socket
server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

Host = sys.argv[1] # local IP address 
print(Host)
Port = 8080          # port
 
#binding the socket with the server address
server_socket.bind((Host,Port))
print("Server listening")

#listen to incoming datagrams
while(True):
    data, addr = server_socket.recvfrom(1024)
    message = data.decode("utf-8")

    num = message;
    index = num[0]
    if index == 'I' and IMUFlag == 0:
        IMU.append(float(num[1:-1]))
        indexIMU = indexIMU+1
        if indexIMU == 8:
            IMU_rec = IMU
            IMU = []
            indexIMU = 0
            IMUFlag = 1
        #print("IMU: ",IMU[indexIMU])
    elif index == 'G' and GPSFlag == 0:
        GPS.append(float(num[1:-1]))
        indexGPS = indexGPS+1
        if indexGPS == 6:
            GPS_rec = GPS
            GPS = []
            indexGPS = 0
            GPSFlag = 1
        #print("GPS: ",GPS[indexGPS])
    elif index == 'T':
        Temp = float(num[1:-1])
        #print("Temp: ",Temp)
    
    if IMUFlag == 1:
        IMUFlag = 0
        for i in range(len(IMU_rec)):
            print("IMU: ",IMU_rec[i])
    if GPSFlag == 1:
        GPSFlag = 0
        for i in range(len(GPS_rec)):
            print("GPS: ",GPS_rec[i])
    print("Temp: ",Temp)
    
