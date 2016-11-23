#include <Wire.h>
#include <BH1750.h>

#define DHT11_PIN 2                                   //Humidity Sensor@ a2

#define extratemp 0
const short MOISTURE_THRESHOLD = 10;                  //Moisture Sensor threshold
const short DRY_SOIL   = 300 + MOISTURE_THRESHOLD;    //definition of soil moisture
const short HUMID_SOIL = 700 + MOISTURE_THRESHOLD;    //definition of soil moisture

BH1750 lightMeter;

#include <ESP8266WiFi.h>

const char* ssid = "Black";
const char* password = "";

const char* host = "google.com";

byte read_dht11_dat()
{
  byte i = 0;
  byte result = 0;
  for (i = 0; i < 8; i++)
  {
    while (!(PINC & _BV(DHT11_PIN))); // wait for 50us
    delayMicroseconds(30);
    if (PINC & _BV(DHT11_PIN))
      result |= (1 << (7 - i));
    while ((PINC & _BV(DHT11_PIN))); // wait '1' finish
  }
  return result;
}

void setup()
{
  DDRC |= _BV(DHT11_PIN);
  PORTC |= _BV(DHT11_PIN);
  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting...");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.println();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.printLn("");
  Serial.println("WiFi connected");
  Serial.println("IP address");
  Serial.println(WiFi.localIP());
  lightMeter.begin();
  //pinMode(extratemp,INPUT);
  Serial.println("Ready");
}

int value = 0

void loop(){
  byte dht11_dat[5];
  byte dht11_in;
  byte i;// start condition
  // 1. pull-down i/o pin from 18ms
  PORTC &= ~_BV(DHT11_PIN);
  delay(18);
  PORTC |= _BV(DHT11_PIN);
  delayMicroseconds(40);
  DDRC &= ~_BV(DHT11_PIN);
  delayMicroseconds(40);

  dht11_in = PINC & _BV(DHT11_PIN);
  if (dht11_in)
  {
    Serial.println("dht11 start condition 1 not met");
    return;
  }
  delayMicroseconds(80);
  dht11_in = PINC & _BV(DHT11_PIN);
  if (!dht11_in)
  {
    Serial.println("dht11 start condition 2 not met");
    return;
  }

  delayMicroseconds(80);// now ready for data reception
  for (i = 0; i < 5; i++)
    dht11_dat[i] = read_dht11_dat();
  DDRC |= _BV(DHT11_PIN);
  PORTC |= _BV(DHT11_PIN);
  byte dht11_check_sum = dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]; // check check_sum
  if (dht11_dat[4] != dht11_check_sum)
  {
    Serial.println("DHT11 checksum error");
  }

  int extratempreading = analogRead(extratemp);
  float voltage = extratempreading * 5.0;
  voltage /= 1024.0;
  float extratemperatureC = (voltage - 0.49) * 100;
  float extratemperatureF = (extratemperatureC * 9.0 / 5.0) + 32.0;

  int moisture = analogRead(A3);
  moisture     = map(moisture, 0, 1023, 1023, 0);

  uint16_t lux = lightMeter.readLightLevel();//name the value lux

  Serial.println("\n");

  Serial.print(voltage);
  Serial.println(" volts");

  Serial.print(extratemperatureC);
  Serial.println(" degrees C");

  Serial.print(extratemperatureF);
  Serial.println(" degrees F");


  Serial.print("Current humdity = ");
  Serial.print(dht11_dat[0], DEC);
  Serial.print(".");
  Serial.print(dht11_dat[1], DEC);
  Serial.println("%  ");

  Serial.print("Temperature = ");
  Serial.print(dht11_dat[2], DEC);
  Serial.print(".");
  Serial.print(dht11_dat[3], DEC);
  Serial.println("C  ");

  Serial.print("Moisture Sensor: ");
  Serial.print(moisture);
  Serial.println();

  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  Serial.println();
  ++value;
  Serial.print("connecting to ");
  Serial.println(host);

  WiFiClient client;
  const int httpPort = 8080;
  if (!client.connect(host, httpPort)) {
    Serial.println("Connectionfailed");
    return;
  }

  String url = "/input/";

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  delay(5000);
}
