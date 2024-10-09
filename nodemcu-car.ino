#include <ESP8266WiFi.h>

const char* ssid = "nawaf";     
const char* password = "nawaf123"; 

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
    client.println("<!DOCTYPE html>");
    client.println("<html lang=\"en\">");
    client.println("<head>");
    client.println("<meta charset=\"UTF-8\">");
    client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
    client.println("<title>Control Car</title>");
    client.println("<style>");
    client.println("body { font-family: Arial, sans-serif; background-color: #f4f4f4; text-align: center; }");
    client.println("h1 { color: #333; }");
    client.println("button { padding: 15px; margin: 10px; font-size: 16px; border: none; border-radius: 5px; cursor: pointer; }");
    client.println(".forward { background-color: #4CAF50; color: white; }");
    client.println(".backward { background-color: #f44336; color: white; }");
    client.println(".left { background-color: #2196F3; color: white; }");
    client.println(".right { background-color: #ff9800; color: white; }");
    client.println(".stop { background-color: #9e9e9e; color: white; }");
    client.println("</style>");
    client.println("</head>");
    client.println("<body>");
    client.println("<h1>Control Car</h1>");
    client.println("<button class='forward' onclick=\"sendCommand('/FORWARD')\">Forward</button><br>");
    client.println("<button class='backward' onclick=\"sendCommand('/BACKWARD')\">Backward</button><br>");
    client.println("<button class='left' onclick=\"sendCommand('/LEFT')\">Left</button><br>");
    client.println("<button class='right' onclick=\"sendCommand('/RIGHT')\">Right</button><br>");
    client.println("<button class='stop' onclick=\"sendCommand('/STOP')\">Stop</button><br>");
    client.println("<script>");
    client.println("function sendCommand(command) {");
    client.println("  var xhttp = new XMLHttpRequest();");
    client.println("  xhttp.open('GET', command, true);");
    client.println("  xhttp.send();");
    client.println("}");
    client.println("</script>");
    client.println("</body>");
    client.println("</html>");
    
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
