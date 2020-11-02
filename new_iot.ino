#include <ESP8266WiFi.h>

const char* ssid = "raspberry"; //Wifi-Name
const char* password = "sumit17222@"; //Wifi-password
 
int ledPin = 16; //device1
int ledPin1 = 5;//device2
int ledPin2 = 4;// device3
WiFiServer server(80);//creating wifiserver
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
 
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  int value2=LOW;
  int value3=LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

if (request.indexOf("/LED1=ON") != -1)  {
    digitalWrite(ledPin1, HIGH);
    value2 = HIGH;
  }
  if (request.indexOf("/LED1=OFF") != -1)  {
    digitalWrite(ledPin1, LOW);
    value2 = LOW;
  }

if (request.indexOf("/LED2=ON") != -1)  {
    digitalWrite(ledPin2, HIGH);
    value3 = HIGH;
  }
  if (request.indexOf("/LED2=OFF") != -1)  {
    digitalWrite(ledPin2, LOW);
    value3 = LOW;
  }
  
if (request.indexOf("/allDevice=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    value = HIGH;
    value2 = HIGH;
    value3 = HIGH;
  }
  if (request.indexOf("/allDevice=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    value= LOW;
    value2 = LOW;
    value3 = LOW;
  }


 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Device1 pin is now: ");
 
  if(value == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />"); 


  client.println("<hr/><hr>");
  client.print("Device2 is now: ");

  if(value2 == HIGH) {
    
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn Off </button></a><br />"); 


   client.println("<hr/><hr>");
   client.print("Device3 is now: ");

  if(value3 == HIGH) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn Off </button></a><br />"); 









  
   
  client.println("</html>");
   client.println("</tbody> </table> <p style=\"text-align: center;\">Turn all: <a href=\"/allDevice=ON\">ON</a> <a href=\"/allDevice=OFF\">OFF</a> <br> </p> <form style= \"width:450px; margin-left: auto; margin-right: auto; text-align: center;\" method=\"GET\"></form> <br> <hr /> <h5 style=\"text-align: center;\"><a title=\"Made by Sumit Singh\" href=\"https://goo.gl/yP90fX\" target=\"_blank\">Made By Sumit Singh</a></h5> </html>");

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
