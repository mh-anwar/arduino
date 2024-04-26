const int trigPin = 12;
const int echoPin = 13;
const int buzzer = 8;
const int btnPin = 2;

// defines variables
long duration;
int distance;
int btnState = 0;

void setup() {
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(btnPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);  // Starts the serial communication
}
void loop() {
  btnState = digitalRead(btnPin);
  if (btnState == HIGH) {
    // When user presses button, get max clearance
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
  } else {
    // Detect any number 15 less/more than max clearance and raise sound alarm

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    int newd = duration * 0.034 / 2;
    if (newd >= distance-15 && newd <= distance+15) {
      noTone(buzzer);//Sets the voltage to low and makes no noise
      delay(1000);//Waits for 1000 milliseconds
      Serial.println("Everything is fine");
    } else{
      Serial.println("Start up sound");
      tone(buzzer, 1000);  // Send 1KHz sound signal... 
      delay(1000);//Waits for 1000 milliseconds 
    }
  }
}