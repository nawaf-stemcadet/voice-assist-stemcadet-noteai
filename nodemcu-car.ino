#include <ESP8266WiFi.h>

const char* ssid = "YOUR_SSID";       // Your Wi-Fi SSID
const char* password = "YOUR_PASSWORD"; // Your Wi-Fi Password

WiFiServer server(80);

// Motor pins
const int motor1A = D1;
const int motor1B = D2;
const int motor2A = D3;
const int motor2B = D4;

void setup() {
  Serial.begin(115200);
  
  // Set motor pins as outputs
  pinMode(motor1A, OUTPUT);
  pinMode(motor1B, OUTPUT);
  pinMode(motor2A, OUTPUT);
  pinMode(motor2B, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    
    // Control motors based on HTTP request
    if (request.indexOf("/FORWARD") != -1) {
      forward();
    } else if (request.indexOf("/BACKWARD") != -1) {
      backward();
    } else if (request.indexOf("/LEFT") != -1) {
      left();
    } else if (request.indexOf("/RIGHT") != -1) {
      right();
    } else if (request.indexOf("/STOP") != -1) {
      stop();
    }
    
    // Send a simple HTML response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println();
    client.println("<html><body>");
    client.println("<h1>Control Car</h1>");
    client.println("<a href=\"/FORWARD\">Forward</a><br>");
    client.println("<a href=\"/BACKWARD\">Backward</a><br>");
    client.println("<a href=\"/LEFT\">Left</a><br>");
    client.println("<a href=\"/RIGHT\">Right</a><br>");
    client.println("<a href=\"/STOP\">Stop</a><br>");
    client.println("</body></html>");
    
    delay(1);
    client.stop();
  }
}

void forward() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void backward() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void left() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, HIGH);
  digitalWrite(motor2A, HIGH);
  digitalWrite(motor2B, LOW);
}

void right() {
  digitalWrite(motor1A, HIGH);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, HIGH);
}

void stop() {
  digitalWrite(motor1A, LOW);
  digitalWrite(motor1B, LOW);
  digitalWrite(motor2A, LOW);
  digitalWrite(motor2B, LOW);
}
