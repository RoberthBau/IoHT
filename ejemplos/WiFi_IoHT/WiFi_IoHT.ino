/*
 *Programa conexión WiFi IoHT - Conexión y despliegue de información en pantalla OLED 
 *Descripción: En este programa usaremos el ESP32 y una pantalla OLED, conectaremos el dispositivo a una red WiFi
 *con ello podremos visualizar información de la intensidad de señal que nuestro dispositivo estara obteniendo
 *
 *Programa realizado por Angel Isidro - 12 enero 2021 - Versión 1 
 */

#include <WiFi.h> 
#include <Adafruit_FeatherOLED.h>
const char* ssid = "TIGO-9635";
const char* password = "2NJ555301438";
Adafruit_FeatherOLED oled = Adafruit_FeatherOLED();

const unsigned char wfMax[] PROGMEM = {
  B11111110,B00000011,B00000000,
  B11111110,B00000011,B00000000,
  B10010010,B00000011,B00000000,
  B01010100,B00011011,B00000000,
  B00111000,B00011011,B00000000,
  B00010000,B11011011,B00000000,
  B00010000,B11011011,B00000000,
  B00010110,B11011011,B00000000,
  B00010110,B11011011,B00000000
};

const unsigned char wfMin[] PROGMEM = {
  B11111110,B00000000,B00000000,
  B11111110,B00000000,B00000000,
  B10010010,B00000000,B00000000,
  B01010100,B00000000,B00000000,
  B00111000,B00000000,B00000000,
  B00010000,B00000000,B00000000,
  B00010000,B00000000,B00000000,
  B00010110,B00000000,B00000000,
  B00010110,B00000000,B00000000
};



const unsigned char wfMed[] PROGMEM = {
  B11111110,B00000000,B00000000,
  B11111110,B00000000,B00000000,
  B10010010,B00000000,B00000000,
  B01010100,B00000000,B00000000,
  B00111000,B00000000,B00000000,
  B00010000,B11000000,B00000000,
  B00010000,B11000000,B00000000,
  B00010110,B11000000,B00000000,
  B00010110,B11000000,B00000000
};

const unsigned char wfOk[] PROGMEM = {
  B11111110,B00000000,B00000000,
  B11111110,B00000000,B00000000,
  B10010010,B00000000,B00000000,
  B01010100,B00011000,B00000000,
  B00111000,B00011000,B00000000,
  B00010000,B11011000,B00000000,
  B00010000,B11011000,B00000000,
  B00010110,B11011000,B00000000,
  B00010110,B11011000,B00000000
};


const unsigned char wfNo[] PROGMEM = {
  B11111110,B00000000,B00000000,
  B11111110,B00000000,B00000000,
  B10010010,B00000000,B00000000,
  B01010100,B00000000,B00000000,
  B00111000,B00000000,B00000000,
  B00010000,B11000000,B00000000,
  B00010000,B11000000,B00000000,
  B00010110,B11000000,B00000000,
  B00010110,B11000000,B00000000
};

const unsigned char TL[] PROGMEM = {
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0xFF,0xFF,0xFF,0xFF,0xFC,0x03,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x01,0xFF,0xFF,0xFF,0xF7,0xFC,0x07,0xFF,0xFC,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,
  0x03,0xFF,0xFF,0xFF,0xEF,0xFC,0x07,0xFF,0xFC,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,
  0x07,0xFF,0xFF,0xFF,0xCF,0xF8,0x07,0xFF,0xF8,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,
  0x0F,0xFF,0xFF,0xFF,0x8F,0xF8,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,
  0x1F,0xFF,0xFF,0xFF,0x9F,0xF8,0x00,0x1E,0x00,0x00,0x00,0x00,0x00,0xF0,0x00,0x00,
  0x3F,0xFF,0xFF,0xFF,0x1F,0xF0,0x00,0x1E,0x01,0xFF,0x00,0x7F,0x80,0xF0,0x07,0xF8,
  0x3F,0xFF,0xFF,0xFE,0x1F,0xF0,0x00,0x1E,0x03,0xFF,0xC1,0xFF,0xE0,0xF0,0x1F,0xFC,
  0x7F,0xFF,0xFF,0xFC,0x3F,0xF0,0x00,0x1E,0x07,0xFF,0xE3,0xFF,0xF0,0xF0,0x3F,0xFE,
  0x00,0x03,0xFE,0x00,0x3F,0xE0,0x00,0x1E,0x07,0xFF,0xE3,0xFF,0xF0,0xF0,0x3F,0xFE,
  0x00,0x03,0xFE,0x00,0x3F,0xE0,0x00,0x1E,0x0F,0x81,0xE3,0xC0,0xF0,0xF0,0x3F,0xFF,
  0x00,0x07,0xFE,0x00,0x7F,0xE0,0x00,0x1E,0x0F,0x81,0xE3,0xC0,0x00,0xF0,0x38,0x1F,
  0x00,0x07,0xFC,0x00,0x7F,0xC0,0x00,0x1E,0x0F,0x81,0xE3,0xF8,0x00,0xF0,0x00,0xFF,
  0x00,0x07,0xFC,0x00,0x7F,0xC0,0x00,0x1E,0x0F,0xFF,0xE3,0xFF,0x80,0xF0,0x1F,0xFF,
  0x00,0x0F,0xFC,0x3F,0xFF,0xFF,0xFE,0x1E,0x0F,0xFF,0xE1,0xFF,0xE0,0xF0,0x3F,0xFF,
  0x00,0x0F,0xF8,0x7F,0xFF,0xFF,0xFC,0x1E,0x0F,0xFF,0xE0,0x7F,0xF0,0xF0,0x7F,0xFF,
  0x00,0x0F,0xF8,0xFF,0xFF,0xFF,0xF8,0x1E,0x0F,0x80,0x03,0x8F,0xF0,0xF0,0x7C,0x1F,
  0x00,0x1F,0xF9,0xFF,0xFF,0xFF,0xF8,0x1E,0x0F,0x81,0xE3,0xC0,0xF0,0xF0,0x78,0x1F,
  0x00,0x1F,0xF3,0xFF,0xFF,0xFF,0xF0,0x1E,0x0F,0x81,0xE3,0xC0,0xF0,0xF0,0x78,0xFF,
  0x00,0x1F,0xF3,0xFF,0xFF,0xFF,0xE0,0x1E,0x07,0xFF,0xE3,0xFF,0xF0,0xFE,0x7F,0xFF,
  0x00,0x3F,0xF7,0xFF,0xFF,0xFF,0xC0,0x1E,0x07,0xFF,0xE3,0xFF,0xF0,0xFE,0x7F,0xFF,
  0x00,0x3F,0xEF,0xFF,0xFF,0xFF,0x80,0x1E,0x07,0xFF,0xC3,0xFF,0xF0,0x7E,0x7F,0xFF,
  0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0x00,0x1E,0x03,0xFF,0x81,0xFF,0xE0,0x3E,0x3F,0x06,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
  0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  oled.init();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   //Fin de la inicialización WiFi

  oled.clearDisplay();
  teslaInicio();
  oled.clearDisplay();
  oled.println("WiFi connected");
  delay(1500);
  oled.clearDisplay();
  wifiInfo();
  delay(3000);
}

void loop() {
  oled.clearDisplay();
  wfIntensidad();
  wifiInfo();
  delay(1000);
  

}

void wfIntensidad() {
  int intenWF = WiFi.RSSI();  
  Serial.println(intenWF);
  
  
  if(intenWF <= -71 ){
    oled.display();
    oled.drawBitmap(111 , -1 , wfMin , 17 , 9 , WHITE );
    oled.display();
    Serial.println("Intensidad Baja ");
  }else if((intenWF <= -61 ) && (intenWF >= -70 )){
    oled.display();
    oled.drawBitmap(111 , -1 , wfMed , 17 , 9 , WHITE );
    oled.display();
    Serial.println("Intensidad media");
  }
  
  if((intenWF <= -51 ) && (intenWF >= -60 )){
    oled.display();
    oled.drawBitmap(111 , -1 , wfOk , 17 , 9 , WHITE );
    oled.display();
    Serial.println("Intensidad buena");
  } 
  
  if(intenWF >= -50 ){
    oled.display();
    oled.drawBitmap(111 , -1 , wfMax , 17 , 9 , WHITE );
    oled.display();
    Serial.println("Intensidad Alta ");
  }
  if(intenWF == -100){
    oled.display();
    oled.drawBitmap(111 , -1 , wfNo , 17 , 9 , WHITE );
    oled.display();
    Serial.println("Sin conexion");
    }
}

void teslaInicio(){
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println("Inter. of Home Things");
  oled.display();
  oled.setTextSize(1);
  oled.drawBitmap(0 , 0 , TL , 128 , 64 , WHITE );
  oled.display();
  delay(5000);
}

void wifiInfo(){
  //oled.clearDisplay();
  oled.setCursor(0,9);
  oled.print("SSID: ");
  oled.println(ssid);
  oled.println("Direccion IP: ");
  oled.println(WiFi.localIP());
  oled.display();
  oled.setTextSize(1);
}