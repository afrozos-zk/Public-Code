// Definisi Pin Sensor Ultrasonik HC-SR04
const int trigPin = 16;
const int echoPin = 17;

// Definisi Pin Driver Motor L298N & Wemos D1 R32
const int enA = 19;
const int in1 = 23;
const int in2 = 5;
const int in3 = 13;
const int in4 = 12;
const int enB = 14;

char t;
int pwm = 200; // Kecepatan motor (0 - 255)
long duration;
int distance;

void setup() {
  // Inisialisasi Serial utama yang terhubung ke modul HC-05
  Serial.begin(9600);
  
  // Konfigurasi pin motor sebagai OUTPUT
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  // Konfigurasi pin sensor ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  Stop();
}

void loop() {
  // Membaca jarak dari sensor ultrasonik secara berkala
  distance = getDistance();

  // Sistem Keamanan Otomatis: Jika ada halangan < 20 cm di depan
  if (distance > 0 && distance < 20) {
    back();          // Robot mundur otomatis
    delay(500);      // Durasi mundur selama 0.5 detik (bisa diubah sesuai kebutuhan)
    Stop();          // Berhenti setelah mundur
  } 
  else {
    // Jika jalur aman, jalankan perintah dari remote Bluetooth
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
}

// Fungsi untuk membaca jarak dari HC-SR04
int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH, 30000); // Timeout 30ms
  int dist = duration * 0.034 / 2;
  return dist;
}

// Fungsi Gerakan Robot 2WD
void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, pwm);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, pwm);
}

void back() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, pwm);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, pwm);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(enA, pwm);
  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, pwm);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enA, pwm);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, pwm);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0);
  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enB, 0);
}
