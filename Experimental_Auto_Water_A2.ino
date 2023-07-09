
//Input Pins
//I.e. Sensors
int MoistPinA = A0;
int MoistPinB = A1;
//int MoistPinC = A2;
//int MoistPinD = A3;

//Output Pins
//int WaterPinA = 2;
//int WaterPinB = 3;
//int WaterPinC = 4;
//int WaterPinD = 5;

//This is for setting the bar on how much moisture is ENOUGH moisture
int MaxMoistLevel = 65;

//Sensor Values
int sensorValueA = 0;
int sensorValueB = 0;
int sensorValueC = 0;
int sensorValueD = 0;

//Average Dryness Level
float avgMoistLevel = 0;

//Create a olace to hold the incoming message
const unsigned int MAX_MSG_LENGTH = 3;
static char message[MAX_MSG_LENGTH - 1];
static unsigned int msg_pos = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);

  // Setting the Pins for reading moisture from the dirt
  pinMode(MoistPinA, INPUT);
  pinMode(MoistPinB, INPUT);
  //pinMode(MoistPinC, INPUT);
  //pinMode(MoistPinD, INPUT);

  //Setting the pins to output the signal to tell the sprinkler to turn on
  //pinMode(WaterPinA, OUTPUT);
  //pinMode(WaterPinB, OUTPUT);
  //pinMode(WaterPinC, OUTPUT);
  //pinMode(WaterPinD, OUTPUT);

}

void loop() {

  if(Serial.available() > 0)
  {
    readMaxMoistLevelValue();
  }  

  //Initial Reading of the moisture level of the dirt
  sensorValueA = analogRead(MoistPinA);
  sensorValueB = analogRead(MoistPinB);
  //sensorValueC = analogRead(MoistPinC);
  //sensorValueD = analogRead(MoistPinD);
  
  printMoistureDisplay(sensorValueA, sensorValueB, sensorValueC, sensorValueD, avgMoistLevel);
  
  //Checking if the soil is wet, if it is wet enough turn off the water. Otherwise turn the water on
  //turnWaterOn(convertToPercentage(sensorValueA), WaterPinA);
  //turnWaterOn(convertToPercentage(sensorValueB), WaterPinB);
  //turnWaterOn(convertToPercentage(sensorValueC), WaterPinC);
  //turnWaterOn(convertToPercentage(sensorValueD), WaterPinD);

  delay(8000); //Wait 8 seconds before next read
}

void readMaxMoistLevelValue()
{
      //read the next available byte in the serial recieve buffer
    char inByte = Serial.read();

    //Message coming in (Check not terminating char and if message is oversized)
    if(inByte != '\n' && (msg_pos < MAX_MSG_LENGTH))
    {
      //fill in the message

      //Add the coming byte to our message
      message[msg_pos] = inByte; //Array will have our complete message
      msg_pos++;
    }
    //Full Message Recieved
    else
    {
      //resets the message position so we can overwirte the previous message in the buffer with each new message
      msg_pos = 0;

      //converts to integer and sets MaxMoistLevel to atoi(message)
      MaxMoistLevel = atoi(message);
    }
}

//Converts sensor values into a readable moisture percentage
float convertToPercentage(int sValue)
{
  //Maximum dryness = 1024
  float cPert = (1024 - sValue) / 10.24;
  return cPert;
}

//Prints the sensor value onto the Serial Monitor
void printMoistureLevel(int sValue, int num)
{
  Serial.println("---------------------------------------");
  Serial.print("Pin Moisture Level ");
  Serial.print(num);
  Serial.print(" : ");
  Serial.println(convertToPercentage(sValue));
  Serial.println("---------------------------------------");
}

//Temporary Display until beeter system can be made
void printMoistureDisplay(int a, int b, int c, int d, int avg)
{
  //Printing Out all of the data values
  printMoistureLevel(a, 1);
  printMoistureLevel(b, 2);
  printMoistureLevel(c, 3);
  printMoistureLevel(d, 4);

  Serial.println("-----------------------");
  Serial.print("Max Moisture Level: ");
  Serial.println(MaxMoistLevel);
  Serial.println("-----------------------");

}

//Turn on the sprinkler system if the moisture level given is less than the maximum moisture level
void turnWaterOn(float moistLevel, int outputPin)
{
  if(moistLevel >= MaxMoistLevel){
    digitalWrite(outputPin, LOW);
  }
  else{
    digitalWrite(outputPin, HIGH);
  }
}
