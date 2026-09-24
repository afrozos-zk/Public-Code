// Definisi Pin Sensor Ultrasonik HC-SR04
const int trigPin = D3;
const int echoPin = D2;

// Definisi Pin Driver Motor L298N & Wemos D1 R32
const int enA = D10;
const int in1 = D9;
const int in2 = D8;
const int in3 = D7;
const int in4 = D6;
const int enB = D5;

void setup() {
  // Inisialisasi Serial Monitor untuk debugging
  Serial.begin(9600);

  // Konfigurasi Pin Motor sebagai Output
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Konfigurasi Pin Ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Atur kecepatan motor (nilai PWM antara 0 - 255)
  // Sesuaikan nilai ini jika robot terlalu cepat atau lambat
  analogWrite(enA, 180);
  analogWrite(enB, 180);
}

void loop() {
  long duration;
  int distance;

  // Mengirim sinyal trigger ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Membaca waktu pantulan echo dalam mikrodetik
  duration = pulseIn(echoPin, HIGH);

  // Menghitung jarak dalam sentimeter (cm)
  distance = duration * 0.034 / 2;

  // Menampilkan pembacaan jarak pada Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Logika navigasi berdasarkan jarak halangan (< 7 cm)
  if (distance > 0 && distance < 7) {
    // Jika ada halangan, berhenti sejenak lalu belok di tempat ke kanan
    stopRobot();
    delay(100);
    turnRightInPlace();
    delay(600); // Durasi waktu belok, sesuaikan jika sudut belok kurang/lebih
  } else {
    // Jika jalur aman, berjalan maju
    moveForward();
  }

  delay(50);
}

// Fungsi untuk berjalan maju
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Fungsi untuk belok di tempat ke kanan (Motor kiri maju, motor kanan mundur)
void turnRightInPlace() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Fungsi untuk menghentikan robot
void stopRobot() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}
