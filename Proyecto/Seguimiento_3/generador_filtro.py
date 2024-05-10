import numpy as np
from scipy.signal import butter, sosfreqz, sos2tf

def butter_lowpass(cutoff, fs, order=5):
    nyquist = 0.5 * fs
    normal_cutoff = cutoff / nyquist
    sos = butter(order, normal_cutoff, btype='low', analog=False, output='sos')
    numerator, denominator = sos2tf(sos)
    return numerator, denominator

# Frecuencia de corte y frecuencia de muestreo
sampling_freq = 1/0.003  # Hz
nyquist=sampling_freq/2
cutoff_freq = 10  # Hz

# Orden del filtro
filter_order = 5

# Obtener los coeficientes del filtro
numerator, denominator = butter_lowpass(cutoff_freq, sampling_freq, order=filter_order)
print("Coeficientes del filtro IIR pasabajas Butterworth de orden 5 (numerador):")
print(numerator)
print("Coeficientes del filtro IIR pasabajas Butterworth de orden 5 (denominador):")
print(denominator)
