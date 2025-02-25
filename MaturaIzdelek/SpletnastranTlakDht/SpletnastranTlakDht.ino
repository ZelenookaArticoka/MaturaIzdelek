#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

// WiFi podatki
const char *ssid = "Dvorscak-net";
const char *password = "12345678";

// HTTP strežnik
WebServer server(80);

// Funkcija za streženje statičnih datotek
void serveStaticFile(const char *filePath, const char *contentType) {
  File file = SPIFFS.open(filePath, "r");
  if (!file) {
    server.send(404, "text/plain", "File not found");
    return;
  }
  server.streamFile(file, contentType);
  file.close();
}

// Funkcija za streženje podatkov v JSON formatu
void handleData() {
  // Simulirani podatki (nadomestite s pravimi meritvami)
  float temperature = 25.5;
  float humidity = 60.0;
  float pressure = 101325.0;

  // Simulirana povprečja
  float avgTemperature = 24.0;
  float avgHumidity = 58.0;
  float avgPressure = 101300.0;

  // Ustvari JSON odgovor
  DynamicJsonDocument doc(256);
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;
  doc["pressure"] = pressure;
  doc["avgTemperature"] = avgTemperature;
  doc["avgHumidity"] = avgHumidity;
  doc["avgPressure"] = avgPressure;

  String jsonResponse;
  serializeJson(doc, jsonResponse);

  server.send(200, "application/json", jsonResponse);
}

void setup() {
  // Serijska komunikacija
  Serial.begin(115200);

  // Inicializacija SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("Napaka pri inicializaciji SPIFFS!");
    return;
  }

  // Povezava na WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi povezan.");
  Serial.print("IP naslov: ");
  Serial.println(WiFi.localIP());

  // Nastavitve strežnika
  server.on("/", []() {
    serveStaticFile("/index.html", "text/html");
  });
  server.on("/style.css", []() {
    serveStaticFile("/style.css", "text/css");
  });
  server.on("/script.js", []() {
    serveStaticFile("/script.js", "application/javascript");
  });
  server.on("/data", handleData);  // API za podatke

  // Zaženi strežnik
  server.begin();
  Serial.println("HTTP strežnik zagnan.");
}

void loop() {
  server.handleClient();  // Obdelaj zahteve
}