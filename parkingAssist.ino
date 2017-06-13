// ---------------------------------------------------------
// This example code was used to successfully communicate
// with 15 ultrasonic sensors. You can adjust the number of
// sensors in your project by changing SONAR_NUM and the
// number of NewPing objects in the "sonar" array. You also
// need to change the pins for each sensor for the NewPing
// objects. Each sensor is pinged at 33ms intervals. So, one
// cycle of all sensors takes 495ms (33 * 15 = 495ms). The
// results are sent to the "oneSensorCycle" function which
// currently just displays the distance data. Your project
// would normally process the sensor results in this
// function (for example, decide if a robot needs to turn
// and call the turn function). Keep in mind this example is
// event-driven. Your complete sketch needs to be written so
// there's no "delay" commands and the loop() cycles at
// faster than a 33ms rate. If other processes take longer
// than 33ms, you'll need to increase PING_INTERVAL so it
// doesn't get behind.
// ---------------------------------------------------------
//#include <NewPing.h>

#define SONAR_NUM     4 // Number or sensors.
#define MAX_DISTANCE 200 // Max distance in cm.
#define PING_INTERVAL 33 // Milliseconds between pings.

unsigned long pingTimer[SONAR_NUM]; // When each pings.
unsigned int cm[SONAR_NUM]; // Store ping distances.
uint8_t currentSensor = 0; // Which sensor is active.

/* buzzer related stuff */

int passiveBuzPin = 11;
int i = 0;
int numOfLoops = 0;
int noteDuration = 1000/48;  // an eighth note
int pauseBetweenNotes = noteDuration * 0.2;

/*NewPing sonar[SONAR_NUM] = { // Sensor object array.
  NewPing(2, 3, MAX_DISTANCE),
  NewPing(4, 5, MAX_DISTANCE),
  NewPing(6, 7, MAX_DISTANCE),
  NewPing(8, 9, MAX_DISTANCE)
};*/
const int trigs[SONAR_NUM] = {2,4,6,8};
const int echos[SONAR_NUM] = {3,5,7,9};
bool doBeep = false;

void setup() {
  Serial.begin(115200);
  pingTimer[0] = millis() + 75; // First ping start in ms.
  for (uint8_t i = 1; i < SONAR_NUM; i++)
  {
    pinMode(trigs[i], OUTPUT);
    pinMode(echos[i], INPUT);
  }
  pinMode(11, OUTPUT);
}

void loop() {
  doBeep = false;
  for (uint8_t k = 0; k < SONAR_NUM; k++) {
    unsigned long duration;
    int distance;

    digitalWrite(trigs[k], HIGH);
    delay(1);
    digitalWrite(trigs[k], LOW);
  
    duration = pulseIn(echos[k], HIGH, 5700*2);  // Timeout if distance > 100 cm
  
    distance = duration / 57;  // Divide by round-trip microseconds per cm to get cm
  
    if (distance <= 200 && distance > 0) {
      Serial.print(duration);
      Serial.print("cm ");
      doBeep = true;
    }
  }
  Serial.println("");
  // The rest of your code would go here.
  
  // This outer for statement determines the number
  // of siren cycles that are played.
  //for(numOfLoops =0; numOfLoops < 4; numOfLoops++) 
  if (doBeep)
  {
    // Play low to high frequencies
    for(i=10;i<120;i++){
      tone(passiveBuzPin, 20*i, noteDuration);
      delay(pauseBetweenNotes);
    }
    // Play high to low frequencies
    for(i=120;i>=10;i--){
      tone(passiveBuzPin, 20*i, noteDuration);
      delay(pauseBetweenNotes);
    }
  }
}

