#include <ESP8266WiFi.h>  //A header file (.h) is a file that contains constants, variable declarations, or function prototypes that can be included in the main program
#include "config.h"


// const char* ssid = "JanTran ";
// const char* password = "christina";

WiFiServer server(80);        // server port: 80   443 → HTTPS (secure web traffic) //22 → SSH (secure shell access) //21 → FTP (file transfer)
int ledPin = LED_BUILTIN;  // In built arduino , so variable is at 2.



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);        //Serial begin baudrate
  delay(100);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);           // start with no light
  Serial.println();
  Serial.print("Connecting to!");
  Serial.println(Wifi_ssid);           // print out the wifi ssid from config.h created from tab or ctrl shift n
  WiFi.begin(Wifi_ssid, Wifi_password);  // Connect to Wifi

  while (WiFi.status() != WL_CONNECTED) {     // of wofu not connected
    Serial.println(WiFi.status());        // check the status, ctrl click or defintion on wifi type you can check the condition 1-7.
    delay(500);
    Serial.print(".");    // print .... (downloading or uploading)
  }

  Serial.println();
  Serial.println("Wifi-Connected");     // wifi is connected
  Serial.print("http://");           // print https

  Serial.print(WiFi.localIP());      // with the ip found

  Serial.println("/");          // so it will write out example http:://123.23.1424//
  server.begin();  // viktigt att skriva ut!!! SERVER check
}

void loop() {

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  Serial.println("min client");
  while (!client.available()) {
    delay(1);
  }      //mindre kluster med invert
  Serial.print("Client status: ");
  Serial.println(client.status());

  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();  // removes line from the buffer

  if (req.indexOf("/LED=OFF") != -1) {
    digitalWrite(LED_BUILTIN, HIGH);
    LED_VALUE = HIGH;  // has no hardware meaning except printing out the condition of on or off.
  }
  if (req.indexOf("/LED=ON") != -1) {
    digitalWrite(LED_BUILTIN, LOW);
    LED_VALUE = LOW;
  }

  // HTML HEADER info till browser  måste göra mer förfoskning
  client.println("HTTP/1.1 200 OK");   //You could change 200 OK to 404 Not Found or 500 Internal Server Error—the browser will show an error page instead of your content.
  client.println("Content-Type: text/html");   // You could change it to text/plain → browser will display HTML tags as text. You could use application/json → useful if sending JSON instead of HTML.
  client.println("");

  // HTML SIDA som ska visas   deklarera h'HTML 5
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  client.print("Led pin is now: ");

  if (LED_VALUE == HIGH) {
    client.println("ON");
  } else {
    client.println("OFF");
  }
  client.println("<br><br>");  // Line break <br>
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");  // link to website
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  // 
}
