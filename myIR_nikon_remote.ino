/*
  myIR_nikon_remote

  Connect an IR LED on pin 9
  Push button on pin 7 (pullup, default HIGH)
  Open the Tools->serial monitor 
  Shot is sent if pushbutton pressed, or  send 11 (command) via serial comm
*/

int ledIR = 9;           // the PWM pin the LED is attached to
int pushButton = 7;

unsigned long previousMillis = 0;     // will store last time LED was updated
const long interval = 1000;           // interval at which to blink (milliseconds)

int carrier_halfperiod = 9;  // 26us period ?!? 

unsigned int delays[] = {76, 1064, 15, 60, 15, 136, 15}; 

unsigned long debug_start_time;

// the setup routine runs once when you press reset:
void setup() {
  // Init pins
  pinMode(ledIR, OUTPUT);
  pinMode(pushButton, INPUT);

  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
}

// the loop routine runs over and over again forever:
void loop() {

  while (Serial.available() > 0) {
    int cmd = Serial.parseInt();
    //carrier_halfperiod = Serial.parseInt();

    if (cmd == 11)
    {
      //debug_start_time = millis();
      
      send_command();

      Serial.println("Command executed");
      //Serial.println(millis()-debug_start_time);
    }
  }

  if (digitalRead(pushButton) == LOW)
  {
    send_command();
  }
  
  //}
}

void send_ir1()
{
    digitalWrite(ledIR, HIGH);
    delayMicroseconds(carrier_halfperiod);
    digitalWrite(ledIR, LOW);
    delayMicroseconds(carrier_halfperiod);
}

void send_ir0()
{
    digitalWrite(ledIR, LOW);
    delayMicroseconds(carrier_halfperiod);
    digitalWrite(ledIR, LOW);
    delayMicroseconds(carrier_halfperiod);
}

void send_command()
{
      unsigned long i;
      for (i=0; i<delays[0]; i++) send_ir1();
      for (i=0; i<delays[1]; i++) send_ir0();
      for (i=0; i<delays[2]; i++) send_ir1();
      for (i=0; i<delays[3]; i++) send_ir0();
      for (i=0; i<delays[4]; i++) send_ir1();
      for (i=0; i<delays[5]; i++) send_ir0();
      for (i=0; i<delays[6]; i++) send_ir1();
      //for (i=0; i<2427; i++) send_ir0();
      send_ir0();
      delay(64);
      for (i=0; i<delays[0]; i++) send_ir1();
      for (i=0; i<delays[1]; i++) send_ir0();
      for (i=0; i<delays[2]; i++) send_ir1();
      for (i=0; i<delays[3]; i++) send_ir0();
      for (i=0; i<delays[4]; i++) send_ir1();
      for (i=0; i<delays[5]; i++) send_ir0();
      for (i=0; i<delays[6]; i++) send_ir1();
      //for (i=0; i<2427; i++) send_ir0();
      send_ir0();  
}
