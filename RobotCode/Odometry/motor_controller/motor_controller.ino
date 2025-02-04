// Pins: L's should be digital, Enables should be analog.---
int L1 = 6;
int L2 = 7;
int L3 = 8;
int L4 = 9;
int E1n2 = 10;
int E3n4 = 11;
// ---------------------------------------------------------
char incoming;
int motorDelay = 500;
int motorSpeed = 10;
int wheelSpeedL = 0;
int wheelSpeedR = 0;

void setup()
{
  Serial.begin(9600);
  MotorControllerSetup();
}

void MotorControllerSetup() // Enable motor controller and pins, set motors to 'brake'.
{
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(L3, OUTPUT);
  pinMode(L4, OUTPUT);
  pinMode(E1n2, OUTPUT);
  pinMode(E3n4, OUTPUT);
  
  digitalWrite(E1n2, HIGH);
  digitalWrite(E3n4, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  
  Serial.println("Type 'h' for HELP.\nInitial speed: 100%");
}

void loop()
{
  ProcessInput();
}

void ProcessInput()
{
  if (Serial.available() > 0)
  {
    incoming = Serial.read();
    
    switch (incoming)
    {
      case 'w': // Move forward at variable speed.
        digitalWrite(L1, LOW);
        digitalWrite(L2, HIGH);
        digitalWrite(L3, LOW);
        digitalWrite(L4, HIGH);
        delay(motorDelay);
        break;
      case 'a': // Turn left.
        digitalWrite(L1, HIGH);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, HIGH);
        delay(motorDelay);
        break;
      case 's': // Move backward.
        digitalWrite(L1, HIGH);
        digitalWrite(L2, LOW);
        digitalWrite(L3, HIGH);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'd': // Turn right.
        digitalWrite(L1, LOW);
        digitalWrite(L2, HIGH);
        digitalWrite(L3, HIGH);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'q': // Up and left.
        digitalWrite(L1, LOW);
        digitalWrite(L2, HIGH);
        digitalWrite(L3, LOW);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'e': // Up and right.
        digitalWrite(L1, LOW);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, HIGH);
        delay(motorDelay);
        break;
      case 'z': // Back and left.
        digitalWrite(L1, HIGH);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'c': // Back and right.
        digitalWrite(L1, LOW);
        digitalWrite(L2, LOW);
        digitalWrite(L3, HIGH);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'x': // Pause.
        digitalWrite(L1, LOW);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
      case 'h': // HELP.
        Serial.print("HELP:\n\tW: Move forward.\n\tA: Turn left.\n\tS: Move backward. \n\tD: Turn left.\n");
        Serial.print("\tQ: Move forward and left (right wheel drive only).\n\tE: Move forward and right (left wheel drive only).\n");
        Serial.print("\tZ: Move backwards and left (left wheel drive only).\n\tC: Move backwards and right (right wheel drive only).\n\tX: Wait.\n");
        //Serial.print("\tM: Custom movement.\n\tP: Edit parameters: Want to go faster? Check here.\n");        
        delay(1000);
        break;
      /*case 'p': // Parameters. (bars for readability)--------------------------------------------------------
        Serial.print("Change drive time (positive int in half-seconds (int * 500 ms)):\n");
        while (!Serial.available());
        motorDelay = Serial.read() * 500;
        delay(500);
        do
        {
          Serial.print("Enter drive speed (int 1 to 10):\n");
          while (!Serial.available());
          motorSpeed = Serial.read();
          delay(1000);
        } while (motorSpeed < 1 || motorSpeed > 10);
        delay(1000);
        break;
      case 'm': // Movement (custom). -----------------------------------------------------------------------
        // Disable motors.
        digitalWrite(E1n2, LOW);
        digitalWrite(E3n4, LOW);
        
        do // Adjust for left wheel speed.
        {
          Serial.print("Left wheel speed (int -10 to 10):\n");
          wheelSpeedL = Serial.read();
          delay(50);
        } while (wheelSpeedL < -10 || wheelSpeedL > 10);
        if (wheelSpeedL > 0) // Prepare to move left wheel forward.
        {
          digitalWrite(L1, LOW);
          digitalWrite(L2, HIGH);
        }
        else // Prepare to move left wheel backward.
        {
          digitalWrite(L1, HIGH);
          digitalWrite(L2, LOW);
        }
        
        do // Adjust for right wheel speed.
        { 
          Serial.print("Right wheel speed (int -10 to 10):\n");
          wheelSpeedR = Serial.read();
          delay(50);
        } while (wheelSpeedR < -10 || wheelSpeedR > 10);
        if (wheelSpeedR > 0) // Prepare to move right wheel forward.
        {
          digitalWrite(L3, LOW);
          digitalWrite(L4, HIGH);
        }
        else // Prepare to move right wheel backward.
        {
          digitalWrite(L3, HIGH);
          digitalWrite(L4, LOW);
        }
        // Re-enable prepped motors.
        analogWrite(E1n2, 25*abs(wheelSpeedL));
        analogWrite(E3n4, 25*abs(wheelSpeedR));
        delay(motorDelay);
        break; // -------------------------------------------------------------------------------------------*/
        default:
        digitalWrite(L1, LOW);
        digitalWrite(L2, LOW);
        digitalWrite(L3, LOW);
        digitalWrite(L4, LOW);
        delay(motorDelay);
        break;
    }
  }
  
  // Brake.
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(L3, LOW);
  digitalWrite(L4, LOW);
  analogWrite(E1n2, 25*motorSpeed);
  analogWrite(E3n4, 25*motorSpeed);
}
