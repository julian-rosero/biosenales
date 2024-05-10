const int N = 20;            // Número de muestras
int data[N];                 // Almacenace de datos
int PE = A0;                 // Pin al que está conectado el electrodo

// Coeficientes del filtro IIR
float numerador[7] = {5.56030910e-06, 2.78015455e-05, 5.56030910e-05, 5.56030910e-05, 2.78015455e-05, 5.56030910e-06, 0.0}; // Coeficientes del numerador
float denominador[7] = {1.0, -4.39027619, 7.74286954, -6.85434935, 3.04468531, -0.54275137, 0.0};       // Coeficientes del denominador

void setup() {
  Serial.begin(9600); // Inicializar comunicación serial
}

float RMS(int data[], int N) {
  float sumaCuadrados = 0.0;
  for (int i = 0; i < N; i++) {
    sumaCuadrados += data[i] * data[i]; // Añadir el cuadrado de cada dato al total
  }
  float rms = sqrt(sumaCuadrados / N); // Calcular el RMS
  return rms;
}

void filtrado(int data[], int N, float salida[]) {
  // Inicializar el array de salida con ceros
  for (int i = 0; i < N; i++) {
    salida[i] = 0.0;
  }

  // Aplicar el filtro IIR
  for (int n = 0; n < N; n++) {
    for (int k = 0; k < 7; k++) {
      if (n - k >= 0) {
        salida[n] += numerador[k] * data[n - k];
      }
      if (n - k > 0) {
        salida[n] -= denominador[k] * salida[n - k];
      }
    }
  }
}

void loop() {
  // Recopilar datos del electrodo
  for (int i = 0; i < N; i++) {
    data[i] = analogRead(PE); // Leer valor del electrodo y guardarlo en el array
    delay(100); // Esperar 100 ms antes de leer el siguiente dato
  }
  
  // Crear array para almacenar el resultado del filtrado
  float resultadoFiltro[N];

  // Aplicar filtro IIR
  filtrado(data, N, resultadoFiltro);

  // Convertir los valores de punto flotante a enteros para calcular el RMS
  int resultadoFiltroInt[N];
  for (int i = 0; i < N; i++) {
    resultadoFiltroInt[i] = (int)resultadoFiltro[i];
  }

  // Calcular RMS
  float rms = RMS(resultadoFiltroInt, N);

  // Mostrar los datos recopilados en el puerto serial
  for (int i = 0; i < N; i++) {
    Serial.print("Dato ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(data[i]);
  }

  // Mostrar el resultado del filtrado en el puerto serial
  for (int i = 0; i < N; i++) {
    Serial.print("Filtrado Dato ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(resultadoFiltro[i]);
  }

  // Mostrar el valor RMS en el puerto serial
  Serial.print("RMS: ");
  Serial.println(rms);

  // Esperar antes de volver a recopilar datos
  delay(10000); // Esperar 10 segundos antes de iniciar la próxima recopilación de datos
}