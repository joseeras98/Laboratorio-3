#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <SPI.h>

const uint8_t n = 64;
volatile uint16_t s0[n], s1[n], s2[n], s3[n];
volatile uint8_t s;
volatile uint16_t os0, os1, os2, os3;
volatile uint8_t d0, d1, d2, d3;

Adafruit_PCD8544 display = Adafruit_PCD8544(13, 12, 11, 10, 9);

ISR(TIMER1_COMPA_vect) {
  if (s < n) {
    if (!d0) {
      s0[s] = analogRead(A0);
      os0 += s0[s];
    } else if (!d1) {
      s1[s] = analogRead(A1);
      os1 += s1[s];
    } else if (!d2) {
      s2[s] = analogRead(A2);
      os2 += s2[s];
    } else if (!d3) {
      s3[s] = analogRead(A3);
      os3 += s3[s];
    }
    s++;
  }
}

void setup() {
  // put your setup code here, to run once:
  analogReference(DEFAULT);
  Serial.begin(9600);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.println("V1,V2,V3,V4");

  display.begin();
  display.clearDisplay();

  TCCR1A = 0x00;
  TCCR1B = 0 | (1 << WGM12) | (1 << CS10);
  TCCR1C = 0x00;
  OCR1A = 0x1458;
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  float v0 = 0, v1 = 0, v2 = 0, v3 = 0;
  uint8_t m0, m1, m2, m3;
  float dc_os0, dc_os1, dc_os2, dc_os3;
  s = 0;
  d0 = 0, d1 = 0, d2 = 0, d3 = 0;
  os0 = 0, os1 = 0, os2 = 0, os3 = 0;
  m0 = digitalRead(A4);
  m1 = digitalRead(A5);
  m2 = digitalRead(2);
  m3 = digitalRead(3);
  display.clearDisplay();
  if (m0) {
    TCNT1 = 0;
    TIMSK1 |= (1 << OCIE1A);
    while (s < n);
    d0 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    dc_os0 = os0/n;
    for (uint8_t i = 0; i < n; i++) {
      float a0 = s0[i] * 5.0000/1023;
      a0 -= (dc_os0 * 5.0000/1023);
      v0 += a0 * a0;
    }
    v0 /= n;
    v0 = sqrt(v0) * 48/5;
    if ((v0*sqrt(2)) >= 20.0) {
      digitalWrite(4, HIGH);
    } else {
      digitalWrite(4, LOW);
    }
    Serial.print(String(v0, 2) + "Vac,");
    display.setCursor(0, 0);
    display.print("V1: ");
    display.print(String(v0, 2));
    display.print(" Vac");
  } else {
    d0 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    v0 = analogRead(A0) * 5.0000/1023;
    v0 = v0 * 48/5 - 24;
    if ((v0 >= 20.0) | (v0 <= -20.0)) {
      digitalWrite(4, HIGH);
    } else {
      digitalWrite(4, LOW);
    }
    Serial.print(String(v0, 2) + "Vdc,");
    display.setCursor(0, 0);
    display.print("V1: ");
    display.print(String(v0, 2));
    display.print(" Vdc");
  }
  if (m1) {
    TCNT1 = 0;
    TIMSK1 |= (1 << OCIE1A);
    while (s < n);
    d1 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    dc_os1 = os1/n;
    for (uint8_t i = 0; i < n; i++) {
      float a1 = s1[i] * 5.0000/1023;
      a1 -= (dc_os1 * 5.0000/1023);
      v1 += a1 * a1;
    }
    v1 /= n;
    v1 = sqrt(v1) * 48/5;
    if ((v1*sqrt(2)) >= 20.0) {
      digitalWrite(5, HIGH);
    } else {
      digitalWrite(5, LOW);
    }
    Serial.print(String(v1, 2) + "Vac,");
    display.setCursor(0, 12);
    display.print("V2: ");
    display.print(String(v1, 2));
    display.print(" Vac");
  } else {
    d1 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    v1 = analogRead(A1) * 5.0000/1023;
    v1 = v1 * 48/5 - 24;
    if ((v1 >= 20.0) | (v1 <= -20.0)) {
      digitalWrite(5, HIGH);
    } else {
      digitalWrite(5, LOW);
    }
    Serial.print(String(v1, 2) + "Vdc,");
    display.setCursor(0, 12);
    display.print("V2: ");
    display.print(String(v1, 2));
    display.print(" Vdc");
  }
  if (m2) {
    TCNT1 = 0;
    TIMSK1 |= (1 << OCIE1A);
    while (s < n);
    d2 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    dc_os2 = os2/n;
    for (uint8_t i = 0; i < n; i++) {
      float a2 = s2[i] * 5.0000/1023;
      a2 -= (dc_os2 * 5.0000/1023);
      v2 += a2 * a2;
    }
    v2 /= n;
    v2 = sqrt(v2) * 48/5;
    if ((v2*sqrt(2)) >= 20.0) {
      digitalWrite(6, HIGH);
    } else {
      digitalWrite(6, LOW);
    }
    Serial.print(String(v2, 2) + "Vac,");
    display.setCursor(0, 24);
    display.print("V3: ");
    display.print(String(v2, 2));
    display.print(" Vac");
  } else {
    d2 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    v2 = analogRead(A2) * 5.0000/1023;
    v2 = v2 * 48/5 - 24;
    if ((v2 >= 20.0) | (v2 <= -20.0)) {
      digitalWrite(6, HIGH);
    } else {
      digitalWrite(6, LOW);
    }
    Serial.print(String(v2, 2) + "Vdc,");
    display.setCursor(0, 24);
    display.print("V3: ");
    display.print(String(v2, 2));
    display.print(" Vdc");
  }
  if (m3) {
    TCNT1 = 0;
    TIMSK1 |= (1 << OCIE1A);
    while (s < n);
    d3 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    dc_os3 = os3/n;
    for (uint8_t i = 0; i < n; i++) {
      float a3 = s3[i] * 5.0000/1023;
      a3 -= (dc_os3 * 5.0000/1023);
      v3 += a3 * a3;
    }
    v3 /= n;
    v3 = sqrt(v3) * 48/5;
    if ((v3*sqrt(2)) >= 20.0) {
      digitalWrite(7, HIGH);
    } else {
      digitalWrite(7, LOW);
    }
    Serial.println(String(v3, 2) + "Vac");
    display.setCursor(0, 36);
    display.print("V4: ");
    display.print(String(v3, 2));
    display.print(" Vac");
  } else {
    d3 = 1, s = 0;
    TIMSK1 &= ~(1 << OCIE1A);
    v3 = analogRead(A3) * 5.0000/1023;
    v3 = v3 * 48/5 - 24;
    if ((v3 >= 20.0) | (v3 <= -20.0)) {
      digitalWrite(7, HIGH);
    } else {
      digitalWrite(7, LOW);
    }
    Serial.println(String(v3, 2) + "Vdc");
    display.setCursor(0, 36);
    display.print("V4: ");
    display.print(String(v3, 2));
    display.print(" Vdc");
  }
  display.display();
}