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

#listen to incoming datagrams and decode received data
while(True):
    data, addr = server_socket.recvfrom(1024)
    message = data.decode("utf-8")

    num = message;
    index = num[0]
    if index == 'I' and IMUFlag == 0:
        IMU.append(float(num[1:-1]))
        indexIMU = indexIMU+1
        if indexIMU == 9:
            IMU_rec = IMU
            IMU = []
            indexIMU = 0
            IMUFlag = 1
        #print("IMU: ",IMU[indexIMU])
    elif index == 'G' and GPSFlag == 0:
        GPS.append(float(num[1:-1]))
        indexGPS = indexGPS+1
        if indexGPS == 7:
            GPS_rec = GPS
            GPS = []
            indexGPS = 0
            GPSFlag = 1
        #print("GPS: ",GPS[indexGPS])
    elif index == 'T':
        Temp = float(num[1:-1])
        #print("Temp: ",Temp)
    

    # Record received data
    if IMUFlag == 1:
        IMUFlag = 0
        accx = float(IMU_rec[0]) # m/s^2
        accy = float(IMU_rec[1])
        accz = float(IMU_rec[2])
        
        gyrx = float(IMU_rec[3]) # 
        gyry = float(IMU_rec[4])
        gyrz = float(IMU_rec[5])
        
        magx = float(IMU_rec[6]) #
        magy = float(IMU_rec[7])
        magz = IMU_rec[8]

        print("------Accelerometer------")
        print("ax = ",accx," ay = accy = ", accy, " accz = ", accz, "\n")
        #for i in range(len(IMU_rec)):
        #    print("IMU: ",IMU_rec[i])
    if GPSFlag == 1:
        GPSFlag = 0
        GPS_mill_T_week = float(GPS_rec[0])/1000 # GPS Millisecond time of the week (s)
        Longitude = float(GPS_rec[1])/10000000
        Latitude = float(GPS_rec[2])/10000000
        H_above_ell = float(GPS_rec[3])/1000 # Height above Ellipsoid (m)
        H_above_sea = float(GPS_rec[4])/1000 # Height above sea level (m)
        Hor_acc_est = float(GPS_rec[5])/1000 # Horizontal accuracy estimate (m)
        Ver_acc_est = float(GPS_rec[6])/1000 # Vertical accuracy estimate (m)
        #for i in range(len(GPS_rec)):
        #    print("GPS: ",GPS_rec[i])
        print("------GPS------")
        print("Latitude: ", Latitude, " Longitude: ", Longitude, "\n")
        print("------Temperature------")
        print(Temp,"\n")
    # print("Temp: ",Temp)