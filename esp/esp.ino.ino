#include <FirebaseArduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
//#include <ArduinoJson.h>
#define FIREBASE_HOST "floodert-ce8a3.firebaseio.com"
#define FIREBASE_AUTH "Wbqx2HuuPdfgKuw0oUWlQVmKgrgcrEBmtmRF9Sle"            // the secret key generated from firebase

#define WIFI_SSID "Rizwan" // Change the name of your WIFI
#define WIFI_PASSWORD "a1b2c3d4" // Change the password of your WIFI
#define DHTPIN 2    // Data Pin of DHT 11 , for NodeMCU D5 GPIO no. is 14
#define LEVELSEN A0  
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
void setup() {
 Serial.begin(9600);
 delay(1000);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting to "); 
   Serial.print(WIFI_SSID);
   while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
   //dht.begin();
  Serial.println ("");
  Serial.println ("WiFi Connected!");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST);     
  dht.begin();
}
void loop() {
if (Firebase.failed()){
      Serial.print("setting number failed:");
      Serial.println(Firebase.error());
}
  
 //int chk=dht.read11(DHTPIN);
 //Serial.println(chk);
  float lev= analogRead(LEVELSEN);
  float h = dht.readHumidity();
  float t = dht.readTemperature();  // Reading temperature as Celsius (the default)
  Serial.print("\nHumidity:");
  Serial.print(h);
  Serial.print("\nTemp:");
  Serial.print(t);
  Serial.print("\nWater Level::");
  Serial.print(lev);
  Firebase.setFloat ("Temp",t);
  Firebase.setFloat ("Humidity",h);
  Firebase.setFloat ("Water Level",lev);
  delay(200);
}
