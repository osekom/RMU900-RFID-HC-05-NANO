#include <SoftwareSerial.h>

#define rxpin 2
#define txpin 3

byte lectura[20]; // Global
byte longitudValida = 0; // Contador que indica la longitud (sección "código") de la última lectura


SoftwareSerial RFID = SoftwareSerial(rxpin, txpin); // RX and TX

  void setup()
  {
    pinMode(rxpin, INPUT);
    pinMode(txpin, OUTPUT);
    RFID.begin(57600); // inicio base del lector
    Serial.begin(9600); // inicio de lectura hacia el arduino
  }
void loop(){
    leerCodigo();
    imprimirCodigo();
  }

void leerCodigo() {
  RFID.readBytesUntil(0x55, lectura, 20); // Descarta la cabecera inicial (inicio)
  RFID.read(); // Descarta el 0xAA inicial
  longitudValida = RFID.readBytesUntil(0x55, lectura, 20); // Lee el código que necesitas, sin el 0x55 final.
  RFID.flush(); // Descarta lo que sobre, que sería el "pie" de la trama (final)
}

void imprimirCodigo() {
  for (int i = 0; i < longitudValida - 1; i++) {
    Serial.print(lectura[i], HEX);
    Serial.write(' ');
  }
  Serial.println(lectura[longitudValida - 1], HEX);
}

