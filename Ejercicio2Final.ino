#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SH1106G display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);


const int TOUCH_PIN_1 = 4;   
const int TOUCH_PIN_2 = 32;  

const int UMBRAL_TOUCH = 300; 

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  if (!display.begin(OLED_ADDRESS, true)) {
    Serial.println("Error al iniciar la pantalla OLED");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  // Lectura de ambos sensores táctiles
  int valorTouch1 = touchRead(TOUCH_PIN_1);
  int valorTouch2 = touchRead(TOUCH_PIN_2);

  bool touch1Activo = (valorTouch1 < UMBRAL_TOUCH);
  bool touch2Activo = (valorTouch2 < UMBRAL_TOUCH);

  display.clearDisplay();

  
  display.setTextSize(1);
  display.setCursor(26, 5);
  display.println("ESP32 TOUCH");

  
  if (touch1Activo && !touch2Activo) {
    
    display.setCursor(15, 28);
    display.println("Boton 1 Activado!");
    display.fillCircle(20, 52, 5, SH110X_WHITE); 
  } 
  else if (touch2Activo && !touch1Activo) {
    
    display.setCursor(15, 28);
    display.println("Boton 2 Activado!");
    display.fillCircle(108, 52, 5, SH110X_WHITE); 
  } 
  else if (touch1Activo && touch2Activo) {
    
    display.setCursor(10, 28);
    display.println("Ambos Activados!");
    display.fillCircle(20, 52, 5, SH110X_WHITE);
    display.fillCircle(108, 52, 5, SH110X_WHITE);
  } 
  else {
    
    display.setCursor(32, 28);
    display.println("Esperando...");
  }

  display.display();

  delay(100);
}