//#include <IRremote.h>
//#include <Bounce2.h>

// Type 0 = Lamp ; 1 = Port ; 2 = Door ; 3 = Brightness
//const int relayPin[2][4] = {{39, 41, 43, 45}, {47, 49, 51, 53}};
//                            2   4   3  1
const int relayPin[2][4] = {{45, 39, 43, 41}, {47, 49, 51, 53}};
const int pbPin[4] = {23, 25, 27, 29};
int RECV_PIN = 2;
//IRrecv irrecv(RECV_PIN);
//decode_results results;

int state[2][4];
//Bounce* pB = new Bounce[4];

const int ledSecurityPin = 46;
const int pbOpenPin = 48;
const int buzzerPin = 50;

int lock = 0;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(ledSecurityPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      pinMode(relayPin[i][j], OUTPUT);
      state[i][j] = 1;
    }
  }

  for (int i = 0; i < 4; i++) {
    pB[i].attach(pbPin[i], INPUT_PULLUP);
    pB[i].interval(25);
  }
  irrecv.enableIRIn();
}

void loop() {
  //  Update Push Button state
  for (int i = 0; i < 4; i++) {
    pB[i].update();
  }

  //  Change state by push button condition
  for (int i = 0; i < 4; i++) {
    if (pB[i].fell()) {
      state[0][i] = !state[0][i];
      Serial.println("m0," + String(i + 1) + "," + String(state[0][i])); // Show data to console
      Serial1.println("m0," + String(i + 1) + "," + String(state[0][i])); // Send data to ESP
    }
  }

  //  Change state by data from ESP
  if (Serial1.available() > 0) {
    if (Serial1.find("m")) {
      int type = Serial1.parseInt();
      int channel = Serial1.parseInt();
      int data = Serial1.parseInt();
      state[type][channel - 1] = data; 

      // Change lock status
      if(type == 2){        
        lock = data;
        delay(1000);
      }
    }
  }
//  if(lock == 0){
//    Serial.println("Buka");
//  }
//  else {
//    Serial.println("Kunci");
//  }

  //  Turn lock status led
  digitalWrite(ledSecurityPin, lock);

  //  Change relay by state
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      digitalWrite(relayPin[i][j], state[i][j]);
    }
  }
}

int getRemote(unsigned long x) {
  //  unsigned long data[] = {0x38863BD2, 0x38863BE0, 0x38863BD0, 0x38863BF0, 0x38863BC8, 0x38863BE8};
  //  unsigned long data[] = {0xF124B0B6, 0x207BEF0F, 0xE8455D8E, 0xCBB7E949, 0x2C1F3172, 0x905ED4F5};
  unsigned long data[] = {0x6F9E817, 0x6F9B04F, 0x6F9708F, 0x6F9F00F, 0x6F938C7, 0x6F9B847};
  for (int i = 0; i < 6; i++) {
    if (data[i] == x) {
      return i;
    }
  }
  return -1;
}
