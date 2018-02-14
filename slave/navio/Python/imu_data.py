"""
MS5611 driver code is placed under the BSD license.
Copyright (c) 2014, Emlid Limited, www.emlid.com
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.
	* Neither the name of the Emlid Limited nor the names of its contributors
	may be used to endorse or promote products derived from this software
	without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL EMLID LIMITED BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
"""

import spidev
import time
import sys
import navio.mpu9250
import navio.util

# usage: imu_data.py [frequency 1-1000 (in Hz)]
# defaults to 10 Hz

if len(sys.argv) == 1:
    freq = 10.0 # Hz
else:
    freq = float(sys.argv[1])

period = 1/freq;

navio.util.check_apm()

imu1 = navio.lsm9ds1.LSM9DS1()
imu2 = navio.mpu9250.MPU9250()

if not imu1.testConnection():
    sys.exit("Connection 1 established: False")

if not imu2.testConnection():
    sys.exit("Connection 2 established: False")

imu1.initialize()
imu2.initialize()
time.sleep(1)

# print csv header
print "time (us), m_acc_x, m_acc_y, m_acc_z, m_mag_x, m_gyr_y, m_gyr_z, m_mag_x, m_mag_y, m_mag_z, l_acc_x, l_acc_y, l_acc_z, l_gyr_x, l_gyr_y, l_gyr_z, l_mag_x, l_mag_y, l_mag_z"

start_time = time.time()
timestamp = 0
while timestamp <= 600000000:
    # imu.read_all()
    # imu.read_gyro()
    # imu.read_acc()
    # imu.read_temp()
    # imu.read_mag()

    # print "Accelerometer: ", imu.accelerometer_data
    # print "Gyroscope:     ", imu.gyroscope_data
    # print "Temperature:   ", imu.temperature
    # print "Magnetometer:  ", imu.magnetometer_data

    # time.sleep(0.1)

    m9a, m9g, m9m = imu2.getMotion9()
    l9a, l9g, l9m = imu1.getMotion9()
    now_time = time.time()
    timestamp = (now_time - start_time) * 1000000;
    print "{:d},".format(int(round(timestamp))),\
          "{:+f},".format(m9a[0]), "{:+f},".format(m9a[1]), "{:+f},".format(m9a[2]),\
          "{:+f},".format(m9g[0]), "{:+f},".format(m9g[1]), "{:+f},".format(m9g[2]),\
          "{:+f},".format(m9m[0]), "{:+f},".format(m9m[1]), "{:+f},".format(m9m[2]),\
          "{:+f},".format(l9a[0]), "{:+f},".format(l9a[1]), "{:+f},".format(l9a[2]),\
          "{:+f},".format(l9g[0]), "{:+f},".format(l9g[1]), "{:+f},".format(l9g[2]),\
          "{:+f},".format(l9m[0]), "{:+f},".format(l9m[1]), "{:+f},".format(l9m[2])

    time.sleep(period)
