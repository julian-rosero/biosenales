import serial
import time
from pyfirmata import Arduino, util

puerto_serie = serial.Serial('COM3', 9600)
time.sleep(2)

board = Arduino('/dev/ttyUSB0')
pin_led = board.get_pin('a:0:i')

def calcular_rms(datos):
    suma_cuadrados = sum(dato ** 2 for dato in datos)
    rms = (suma_cuadrados / len(datos)) ** 0.5
    return rms

def encender_led():
    pin_led.write(1)

def apagar_led():
    pin_led.write(0)

while True:
    if puerto_serie.in_waiting > 0:
        datos_str = puerto_serie.readline().decode().strip()
        if datos_str.startswith('RMS:'):
            rms = float(datos_str.split(': ')[1])
            if rms > 80:
                encender_led()
            else:
                apagar_led()

puerto_serie.close()