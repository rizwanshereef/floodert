#include <ESP8266WiFi.h>                                                    // esp8266 library
#include <FirebaseArduino.h>                                                // firebase library
//#include <DHT.h>                                                            // dht11 temperature and humidity sensor library

#define FIREBASE_HOST "floodert-7f560.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "Wbqx2HuuPdfgKuw0oUWlQVmKgrgcrEBmtmRF9Sle"            // the secret key generated from firebase

#define WIFI_SSID "Rizwan"                                             // input your home or public wifi name 
#define WIFI_PASSWORD "a1b2c3d4"                                    //password of wifi ssid

#define RELAY D4
#define LEVELSEN A0                                                           //  Analog pin connected to water level sensor 
#define DHTPIN D4                                                           // digital pin connected to DHT sensor
#define DHTTYPE DHT11                                                       // select dht type as DHT 11 or DHT22
//DHT dht(DHTPIN, DHTTYPE);                                                     

void setup() {
 
  Serial.begin(9600);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to "); 
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              // connect to firebase
 // dht.begin();                                                               //Start reading dht sensor
 pinMode(RELAY,OUTPUT);
}

void loop() { 
  digitalWrite(RELAY,HIGH);
  delay(1000);
  digitalWrite(RELAY,LOW);
  int l = analogRead(LEVELSEN);
  int a;
   String FireStatus = ""; 
  
 // float h = dht.readHumidity();                                              // Reading temperature or humidity takes about 250 milliseconds!
 // float t = dht.readTemperature();                                           // Read temperature as Celsius (the default)
    
 // if (isnan(h) || isnan(t)) {                                                // Check if any reads failed and exit early (to try again).
  //  Serial.println(F("Failed to read from DHT sensor!"));
  //  return;
 // }
  Serial.print("Water Level: "); 
  Serial.print(l);
   Serial.print("\n");
  String fireLevel= String(l) + String("cm");
  //Serial.print("Humidity: ");  Serial.print(h);
 // String fireHumid = String(h) + String("%");                                         //convert integer humidity to string humidity 
 // Serial.print("%  Temperature: ");  Serial.print(t);  Serial.println("Â°C ");
 // String fireTemp = String(t) + String("Â°C");                                                     //convert integer temperature to string temperature
  delay(4000);

  if (Firebase.failed()) // Check for errors
  {

   Serial.println(Firebase.error());

  return;

  }

  Firebase.pushString("Water_level", fireLevel);                               // setup path and push water level value to database 
 // Firebase.pushString("/Sensor/Humidity", fireHumid);                                  //setup path and push Humidity value to database
  //Firebase.pushString("/Sensor/Temperature", fireTemp);                                //setup path and push Temperature value to database

String firebaseResult = Firebase.Get(); 
Serial.println(firebaseResult);
}
