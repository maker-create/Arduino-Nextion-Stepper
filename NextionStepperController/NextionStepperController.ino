#include <AccelStepper.h>

// Pines específicos para CNC Shield v4 con Arduino Nano
#define EN_PIN 8     // Pin de habilitación para todos los motores

//En CNC Shields clones pueden estar invertidos step y dir
#define STEP_X 5
#define DIR_X  2

#define STEP_Y 6
#define DIR_Y  3

// Definición de motores
AccelStepper stepperX(1, STEP_X, DIR_X);
AccelStepper stepperY(1, STEP_Y, DIR_Y);

const float pasosPorVuelta = 200.0; // Cambia a 3200 si usas microstepping 1/16
const float pasosPorGrado = pasosPorVuelta / 360.0;

void setup() {
  Serial.begin(9600);
  
  // CONFIGURACIÓN CLAVE PARA CNC SHIELD V4
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // En la mayoría de las placas, LOW activa los drivers

  stepperX.setMaxSpeed(100);
  stepperX.setAcceleration(50);
  
  stepperY.setMaxSpeed(100);
  stepperY.setAcceleration(50);
}

void loop() {
  if (Serial.available() > 0) {
    char eje = Serial.read(); 
    if (eje == 'X' || eje == 'Y') {
      long grados = Serial.parseInt(); 
      long posicionObjetivo = grados * pasosPorGrado;

      if (eje == 'X') {
        stepperX.moveTo(posicionObjetivo);
        Serial.println(posicionObjetivo);
      } 
      else if (eje == 'Y') {
        stepperY.moveTo(posicionObjetivo);
        Serial.println(posicionObjetivo);
      }
    }
  }
  Serial.println(stepperY.distanceToGo());
  stepperX.run();
  stepperY.run();
}
