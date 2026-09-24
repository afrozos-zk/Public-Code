// Definisi Pin Driver Motor L298N Sesuai Skema Wiring
const int pinEnA = 19; // IO19
const int pinIn1 = 23; // IO23
const int pinIn2 =  5; // IO5
const int pinIn3 = 13; // IO13
const int pinIn4 = 12; // IO12
const int pinEnB = 14; // IO14

char t;
int pwm = 200; // Kecepatan motor (0 - 255)

void setup() {
  // Menggunakan Serial utama yang terhubung ke pin TX0 dan RX0 untuk modul HC-05[cite: 5]
  Serial.begin(9600);
  
  // Set semua pin kontrol motor sebagai OUTPUT
  pinMode(pinEnA, OUTPUT);
  pinMode(pinEnB, OUTPUT);
  pinMode(pinIn1, OUTPUT);
  pinMode(pinIn2, OUTPUT);
  pinMode(pinIn3, OUTPUT);
  pinMode(pinIn4, OUTPUT);
  
  // Berhenti di awal
  Stop();
}

void loop() {
  // Membaca data dari aplikasi Android via HC-05
  if (Serial.available() > 0) {
    t = Serial.read();
    
    switch (t) {
      case 'F': forward(); break; // Maju
      case 'B': back();    break; // Mundur
      case 'L': left();    break; // Belok Kiri
      case 'R': right();   break; // Belok Kanan
      case 'S': Stop();    break; // Berhenti
      default:  break;
    }
  }
}

// Fungsi Gerakan Robot 2WD
void forward() {
  digitalWrite(pinIn1, HIGH);
  digitalWrite(pinIn2, LOW);
  analogWrite(pinEnA, pwm);
  
  digitalWrite(pinIn3, HIGH);
  digitalWrite(pinIn4, LOW);
  analogWrite(pinEnB, pwm);
}

void back() {
  digitalWrite(pinIn1, LOW);
  digitalWrite(pinIn2, HIGH);
  analogWrite(pinEnA, pwm);
  
  digitalWrite(pinIn3, LOW);
  digitalWrite(pinIn4, HIGH);
  analogWrite(pinEnB, pwm);
}

void left() {
  digitalWrite(pinIn1, LOW);
  digitalWrite(pinIn2, HIGH);
  analogWrite(pinEnA, pwm);
  
  digitalWrite(pinIn3, HIGH);
  digitalWrite(pinIn4, LOW);
  analogWrite(pinEnB, pwm);
}

void right() {
  digitalWrite(pinIn1, HIGH);
  digitalWrite(pinIn2, LOW);
  analogWrite(pinEnA, pwm);
  
  digitalWrite(pinIn3, LOW);
  digitalWrite(pinIn4, HIGH);
  analogWrite(pinEnB, pwm);
}

void Stop() {
  digitalWrite(pinIn1, LOW);
  digitalWrite(pinIn2, LOW);
  analogWrite(pinEnA, 0);
  
  digitalWrite(pinIn3, LOW);
  digitalWrite(pinIn4, LOW);
  analogWrite(pinEnB, 0);
}
