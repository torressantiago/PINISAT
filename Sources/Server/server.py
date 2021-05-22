# Import modules
import socket
import sys
import sqlalchemy as db

# Variable initialization
indexIMU = 0
indexGPS = 0
IMUFlag = 0
GPSFlag = 0
IMU = [1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
#IMU.append()
#print(IMU)
IMU_rec = IMU
GPS = [1.0,1.0,1.0,1.0,1.0,1.0,1.0]
#GPS.append([1.0,1.0,1.0,1.0,1.0,1.0,1.0])
GPS_rec = GPS
tb = 'acc'

# specify database configurations
config = {
    'host': 'localhost',
    'port': 3306,
    'user': 'pinisat',
    'password': 'pinisat',
    'database': 'pinisat'
}

db_user = config.get('user')
db_pwd = config.get('password')
db_host = config.get('host')
db_port = config.get('port')
db_name = config.get('database')

# specify connection string
connection_str = f'mysql+pymysql://{db_user}:{db_pwd}@{db_host}:{db_port}/{db_name}'
# connect to database
engine = db.create_engine(connection_str)
connection = engine.connect()

#create the server socket
server_socket = socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

Host = sys.argv[1] # local IP address 
print(Host)
Port = 8080          # port
 
#binding the socket with the server address
try:
    server_socket.bind((Host,Port))
except:
    print("no need to rebind")
print("Server listening")

#listen to incoming datagrams and decode received data
while(True):
    #print("Entered while...")
    data, addr = server_socket.recvfrom(1024)
    message = data.decode("utf-8")
    #print(message)
    num = message;
    index = num[1]
    numtag = int(num[0])
    if index == 'I' and IMUFlag == 0:
        #print("Entered IMU...")
        #IMU.append(float(num[1:-1]))
        #indexIMU = indexIMU+1
        #print(numtag)
        IMU[numtag-1] = float(num[2:-1])
        if numtag == 9:
            IMU_rec = IMU
            IMU = [1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
            indexIMU = 0
            IMUFlag = 1
            #print("IMU ready")
    elif index == 'G' and GPSFlag == 0:
        #print("Entered IMU...")
        #GPS.append(float(num[1:-1]))
        #indexGPS = indexGPS+1
        GPS[numtag-1] = float(num[2:-1])
        if numtag == 7:
            GPS_rec = GPS
            GPS = [1.0,1.0,1.0,1.0,1.0,1.0,1.0]
            indexGPS = 0
            GPSFlag = 1
            #print("GPS ready")
    elif index == 'T':
        #print("Entered temp...")
        Temp = str(float(num[2:-1]))
        tb = 'temp'
        #print("Temp ready")
        print(Temp)
        strCommand = "INSERT INTO "+tb+" VALUES ("+Temp+");"
        engine.execute(strCommand)
    

    # Record received data
    if IMUFlag == 1:
        IMUFlag = 0
        accx = str(float(IMU_rec[0])) # m/s^2
        accy = str(float(IMU_rec[1]))
        accz = str(float(IMU_rec[2]))
        tb = 'acc'
        strCommand = "INSERT INTO "+tb+" VALUES ("+accx+","+accy+","+accz+");"
        engine.execute(strCommand)

        gyrx = str(float(IMU_rec[3])) # 
        gyry = str(float(IMU_rec[4]))
        gyrz = str(float(IMU_rec[5]))
        tb = 'gyr'
        strCommand = "INSERT INTO "+tb+" VALUES ("+gyrx+","+gyry+","+gyrz+");"
        engine.execute(strCommand)

        magx = str(float(IMU_rec[6])) #
        magy = str(float(IMU_rec[7]))
        magz = str(float(IMU_rec[8]))
        tb = 'mag'
        strCommand = "INSERT INTO "+tb+" VALUES ("+magx+","+magy+","+magz+");"
        engine.execute(strCommand)

        #print("------Accelerometer------")
        #print("ax = ",accx," accy = ", accy, " accz = ", accz, "\n")
        #print("------Gyroscope------")
        #print("gyrx = ",gyrx," gyry = ", gyry, " gyrz = ", gyrz, "\n")
        #print("------Magnetometer------")
        #print("magx = ",magx,"  magy = ", magy, " magz = ", magz, "\n")
        #for i in range(len(IMU_rec)):
        #    print("IMU: ",IMU_rec[i])
    if GPSFlag == 1:
        GPSFlag = 0
        GPS_mill_T_week = str(float(GPS_rec[0])/1000) # GPS Millisecond time of the week (s)
        Longitude = str(float(GPS_rec[1])/10000000)
        Latitude = str(float(GPS_rec[2])/10000000)
        H_above_ell = str(float(GPS_rec[3])/1000) # Height above Ellipsoid (m)
        H_above_sea = str(float(GPS_rec[4])/1000) # Height above sea level (m)
        Hor_acc_est = str(float(GPS_rec[5])/1000) # Horizontal accuracy estimate (m)
        Ver_acc_est = str(float(GPS_rec[6])/1000) # Vertical accuracy estimate (m)
        tb = 'gps'
        strCommand = "INSERT INTO "+tb+" VALUES ("+GPS_mill_T_week+","+Longitude+","+Latitude+","+H_above_ell+","+H_above_sea+","+Hor_acc_est+","+Ver_acc_est+");"
        engine.execute(strCommand)
        #for i in range(len(GPS_rec)):
        #    print("GPS: ",GPS_rec[i])
        #print("------GPS------")
        #print("Latitude: ", Latitude, " Longitude: ", Longitude, "\n")
        #print("------Temperature------")
        #print(Temp,"\n")
    # print("Temp: ",Temp)