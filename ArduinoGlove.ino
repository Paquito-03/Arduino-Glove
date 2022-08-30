#include "Wire.h" // library to make work GY-521

#define ballSwitch 7 // pin of ball switch sensor
#define flexSensor A0 // pin of flex sensor

int jump; // value of the ball switch sensor
int flexVal; // analog value of flex sensor

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050

int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer
int16_t temperature; // variables for temperature data

char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

void setup() {
  pinMode(ballSwitch, INPUT);
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission with GY-521 board
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_ADDR, 7*2, true);

  accelerometer_x = Wire.read()<<8 | Wire.read(); // Save the reading of accelerometer x
  accelerometer_y = Wire.read()<<8 | Wire.read(); // Save the reading of accelerometer y
  accelerometer_z = Wire.read()<<8 | Wire.read(); // Save the reading of accelerometer z

  jump = digitalRead(ballSwitch); // read the ball switch sensor
  flexVal = analogRead(flexSensor); // Flex return 0 when not bend or > 0 when bend

  Serial.print(convert_int16_to_str(accelerometer_x)); // send serial axe x
  Serial.print(convert_int16_to_str(accelerometer_y)); // send serial axe y
  Serial.print(convert_int16_to_str(accelerometer_z)); // send serial axe z

  Serial.print(convert_int16_to_str(flexVal)); // send serial flexVal
  Serial.println(convert_int16_to_str(jump)); // send serial jump 
  
}
