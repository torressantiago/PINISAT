#ifndef _INERTIAL_SENSOR_H
#define _INERTIAL_SENSOR_H

class InertialSensor {
public:
    virtual bool initialize() = 0;
    virtual bool probe() = 0;
    virtual void update() = 0;

    float read_temperature() {return temperature;};
    void read_accelerometer(float *ax, float *ay, float *az) {*ax = _ax; *ay = _ay; *az = _az;};
    void read_gyroscope(float *gx, float *gy, float *gz) {*gx = _gx; *gy = _gy; *gz = _gz;};
    void read_magnetometer(float *mx, float *my, float *mz) {*mx = _mx; *my = _my; *mz = _mz;};
    /*
    void readfromsens(float *tabaccel, float *tabgyr, float *tabmag){
        read_accelerometer(tabaccel,tabaccel+1,tabaccel+2);
        read_gyroscope(tabgyr,tabgyr+1,tabgyr+2);
        read_magnetometer(tabmag,tabmag+1,tabmag+2);
    };*/   

protected:
    float temperature;
    float _ax, _ay, _az;
    float _gx, _gy, _gz;
    float _mx, _my, _mz;
};

#endif //_INERTIAL_SENSOR_H
