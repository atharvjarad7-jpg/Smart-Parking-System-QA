
#define BLYNK_TEMPLATE_ID "TMPL3zxZSdmJ-"
#define BLYNK_TEMPLATE_NAME "SMART PARKING SYSTEM"
#define BLYNK_AUTH_TOKEN "qFrR_rtoqXc9DWtRw8Z4H6ttz9rKs1-i"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "vivo Y31";
char pass[] = "12345678";

#define TRIG1 5
#define ECHO1 19
#define TRIG2 18
#define ECHO2 21

#define DISTANCE_LIMIT 7.0


BlynkTimer timer;

String zone1 = "NO READING";
String zone2 = "NO READING";

bool occupied[2] = {false, false};
bool initialized[2] = {false, false};

int candidate[2] = {-1, -1};
int stableCount[2] = {0, 0};

float getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) return -1;

  return duration * 0.0343 / 2.0;
}

void sendParkingEvent(int slot, bool isOccupied) {
  Serial.print("EVENT,S");
  Serial.print(slot + 1);
  Serial.print(",");
  Serial.println(isOccupied ? "ENTER" : "EXIT");
}

void updateSensorState(int slot, float distance) {
  if (distance < 0) {
    candidate[slot] = -1;
    stableCount[slot] = 0;
    return;
  }

  int newState = (distance < DISTANCE_LIMIT) ? 1 : 0;

  if (candidate[slot] == newState) {
    stableCount[slot]++;
  } else {
    candidate[slot] = newState;
    stableCount[slot] = 1;
  }

  if (stableCount[slot] < 3) return;

  if (!initialized[slot]) {
    initialized[slot] = true;
    occupied[slot] = newState;

    if (newState) {
      sendParkingEvent(slot, true);
    }
    return;
  }

  if (occupied[slot] != (bool)newState) {
    occupied[slot] = newState;
    sendParkingEvent(slot, newState);
  }
}

void sendCurrentStatus() {

  int slot1LED = (zone1 == "AVAILABLE") ? 1 : 0;
  int slot2LED = (zone2 == "AVAILABLE") ? 1 : 0;

  Blynk.virtualWrite(V0, slot1LED);
  Blynk.virtualWrite(V1, slot2LED);

  int freeSlots = 0;

  if (zone1 == "AVAILABLE") freeSlots++;
  if (zone2 == "AVAILABLE") freeSlots++;

  Blynk.virtualWrite(V2, freeSlots);
}

BLYNK_CONNECTED() {
  Serial.println("BLYNK_CONNECTED");
  sendCurrentStatus();
}

void updateParking() {
  float d1 = getDistance(TRIG1, ECHO1);
  delay(60);
  float d2 = getDistance(TRIG2, ECHO2);

  updateSensorState(0, d1);
  updateSensorState(1, d2);

  zone1 = (d1 < 0 || !initialized[0]) ? "NO READING" :
          (occupied[0] ? "OCCUPIED" : "AVAILABLE");

  zone2 = (d2 < 0 || !initialized[1]) ? "NO READING" :
          (occupied[1] ? "OCCUPIED" : "AVAILABLE");

  Serial.print("STATUS,");
  Serial.print("S1,");
  Serial.print(zone1);
  Serial.print(",");
  Serial.print(d1, 1);
  Serial.print(",S2,");
  Serial.print(zone2);
  Serial.print(",");
  Serial.println(d2, 1);

  if (Blynk.connected()) {
    sendCurrentStatus();
  }
}

void maintainConnections() {
  if (WiFi.status() != WL_CONNECTED) {
    WiFi.reconnect();
    return;
  }

  if (!Blynk.connected()) {
    Blynk.connect(1000);
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(TRIG1, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(TRIG2, OUTPUT);
  pinMode(ECHO2, INPUT);

  digitalWrite(TRIG1, LOW);
  digitalWrite(TRIG2, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Blynk.config(BLYNK_AUTH_TOKEN);

  timer.setInterval(1000L, updateParking);
  timer.setInterval(10000L, maintainConnections);

  updateParking();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Blynk.run();
  }

  timer.run();
}
