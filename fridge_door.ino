#define SPK_PIN    (2)
#define SENSOR_PIN (3)
#define LED_PIN    (13)

#define SCALE (1)

int sensor_state = 0;
int bip_duration = 0;
unsigned long last_closed_millis;
unsigned long open_duration;

void setup() {
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  pinMode(SPK_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  Serial.begin(57600);
  Serial.println("-------START-------");
  last_closed_millis = millis();
}

void loop() {
  sensor_state = digitalRead(SENSOR_PIN);

  if (sensor_state == HIGH) {
    open_duration = (millis() - last_closed_millis) / 1000;

    Serial.println(open_duration);
    digitalWrite(LED_PIN, HIGH);

    if (open_duration < 40) {
      digitalWrite(SPK_PIN, HIGH);
      delay(8);
      digitalWrite(SPK_PIN, LOW);
      delay(300 / SCALE);      
    } else if (open_duration < 240) {
      bip_duration = (open_duration-40+6)/6 * 8;
      for (int i=0; i<3; ++i) {
        digitalWrite(SPK_PIN, HIGH);
        delay(bip_duration);
        digitalWrite(SPK_PIN, LOW);
        delay(300 / SCALE);
      }
      digitalWrite(LED_PIN, LOW);
    } else {
        digitalWrite(SPK_PIN, HIGH);
    }
    delay(1500 / SCALE);
  } else {
    last_closed_millis = millis();
    digitalWrite(LED_PIN, LOW);

    digitalWrite(SPK_PIN, LOW);
    delay(500);
  }
}
