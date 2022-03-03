
/*–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––/

  Write an array of instructions to EEPROM,
  Use it to control a car autonomously.

  Adapted by Ricky Thang
    from www.hobbytronics.co.uk 2012
    EEPROM_PAGE_WRITES

/–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––*/

#include <Wire.h>
#include "motorfunc.h"
#define eeprom1 0x50 //Address of 24LC256 eeprom chip

char rdata[32];
const int M1_1A = 11; //Motor 1 Control Input A through pin 11
const int M1_1B = 10; //Motor 1 Control Input B through pin 10
const int M2_1A = 6; //Motor 2 Control Input A through pin 6
const int M2_1B = 5; //Motor 2 Control Input B through pin 5
const int length_instruction_string = 13;
int speed = 0;
char data, lastData;

void setup(void)
{
  Serial.begin(9600);
  Wire.begin(); 
  pinMode(M1_1A, OUTPUT);
  pinMode(M1_1B , OUTPUT);
  pinMode(M2_1A, OUTPUT);
  pinMode(M2_1B , OUTPUT);
  // turn off motor
  stop();

  unsigned int i = 0; //for reading eeprom data
  unsigned int j = 0; //for counting length of data
  int total_str_len=0;
  const int max_num_instructions = 11; //stipulate max number of instructions
  int speed = 255;
  int delay_time = 0;
  char lastData;

/* Define instruction data to be written to EEPROM */
  char str_instructions[max_num_instructions][length_instruction_string]={
    "2 128 10000\n",  //forward, half speed, 10 seconds
    "6 100  1000\n",  //forward right point turn, 100 speed, 1 second
    "2 128  5000\n",  //forward, half speed, 5 seconds
    "5 100  1000\n",  //forward left point turn, 100 speed, 1 second
    "2 255  5000\n",  //forward, full speed, 5 seconds
    "1   0  2000\n",  //stop, two seconds
    "3 255  5000\n",  //reverse, full speed, 5 seconds
    "5 100  1000\n",  //reverse left point turn, 100 speed, 1 second
    "3 128  5000\n",  //reverse, half speed, 5 seconds
    "6 100  1000\n",  //reverse right point turn, 100 speed, 1 second
    "3 128 10000\n"}; //reverse, half speed, 10 seconds

  /* Write the data to the EEPROM */
  while (j < max_num_instructions)  
  {
    int str_len=0;
    do{ str_len+=length_instruction_string; } while(str_instructions[j][str_len]);
    writeEEPROM(eeprom1,total_str_len,str_instructions[j]);
    total_str_len+=strlen(str_instructions[j]);
    j++;
  }
  
  /* Scan, then use the recorded data as function arguments */
  Serial.println("DATA READ");
  for(i=0;i<max_num_instructions;i++) 
  {
    readEEPROM(eeprom1, i*(length_instruction_string-1), rdata, length_instruction_string-1);
    Serial.write(rdata,length_instruction_string-1);
    sscanf(rdata, "%c %i %i", &data, &speed, &delay_time);

    switch (data)
    {
    case '1':
      stop();
      speed = 0;
      Serial.print("The car has stopped for ");
      Serial.print(delay_time/1000);
      Serial.println(" seconds.");
      delay(delay_time);
      break;
    case '2':
      forward(speed);
      lastData = '2';
      Serial.print("The car is moving forward at ");
      Serial.print(speed);
      Serial.print(" speed for ");
      Serial.print(delay_time/1000);
      Serial.println(" seconds.");
      delay(delay_time);
      stop();
      break;
    case '3':
      reverse(speed);
      lastData = '3';
      Serial.print("The car is in reverse at ");
      Serial.print(speed);
      Serial.print(" speed for ");
      Serial.print(delay_time/1000);
      Serial.println(" seconds.");
      delay(delay_time);
      stop();
      break;
    case '4':
      Serial.print("Current Speed Setting: ");
      Serial.print(speed/25);
      Serial.print("/10");
      break;
    case '5':
      Serial.print("The car is turning right for ");
      Serial.print(delay_time/1000);
      Serial.println(" seconds.");
      if (lastData == '2')
      {
        forward_R(speed);
        delay(delay_time);
        stop();
      }
      if (lastData == '3')
      {
        reverse_R(speed);
        delay(delay_time);
        stop();
      }
      break;
    case '6':
      Serial.print("The car is turning left for ");
      Serial.print(delay_time/1000);
      Serial.println(" seconds.");
      if (lastData == '2')
      {
        forward_L(speed);
        delay(delay_time);
        stop();
      }
      if (lastData == '3')
      {
        reverse_L(speed);
        delay(delay_time);
        stop();
      }
      break;
    case '+':
      //increase speed by 1/10th
      if (speed < 250)
      {
        speed += 25;
        if (lastData == '2')
          forward(speed);
        if (lastData == '3')
          reverse(speed);
        Serial.print("Speed Setting: ");
        Serial.print(speed/25);
        Serial.print("/10");
      }
      else
        Serial.println("Maximum speed has been reached.");
      break;
    case '-':
      //decrease speed by 1/10th
      if (speed >= 25)
      {
        speed -= 25;
        if (lastData == '2')
          forward(speed);
        if (lastData == '3')
          reverse(speed);
        Serial.print("Speed Setting: ");
        Serial.print(speed/25);
        Serial.print("/10");
      }
      else
        Serial.println("The car has stopped.");
      break;
    }
  } 
}

void loop(){}

void writeEEPROM(int deviceaddress, unsigned int eeaddress, char* data) 
{
  // Uses Page Write for 24LC256
  // Allows for 64 byte page boundary
  // Splits string into max 16 byte writes
  unsigned char i=0, counter=0;
  unsigned int address;
  unsigned int page_space;
  unsigned int page=0;
  unsigned int num_writes;
  unsigned int data_len=0;
  unsigned char first_write_size;
  unsigned char last_write_size; 
  unsigned char write_size; 

  // Calculate length of data
  do{ data_len++; } while(data[data_len]); 

  // Calculate space available in first page
  page_space = int(((eeaddress/64) + 1)*64)-eeaddress;

  // Calculate first write size
  if (page_space>16){
  first_write_size=page_space-((page_space/16)*16);
  if (first_write_size==0) first_write_size=16;
  } 
  else 
  first_write_size=page_space; 

  // calculate size of last write 
  if (data_len>first_write_size) 
  last_write_size = (data_len-first_write_size)%16; 

  // Calculate how many writes we need
  if (data_len>first_write_size)
  num_writes = ((data_len-first_write_size)/16)+2;
  else
  num_writes = 1; 

  i=0; 
  address=eeaddress;
  for(page=0;page<num_writes;page++) 
  {
  if(page==0) write_size=first_write_size;
  else if(page==(num_writes-1)) write_size=last_write_size;
  else write_size=16;

  Wire.beginTransmission(deviceaddress);
  Wire.write((int)((address) >> 8)); // MSB
  Wire.write((int)((address) & 0xFF)); // LSB
  counter=0;
  do{ 
  Wire.write((byte) data[i]);
  i++;
  counter++;
  } while((data[i]) && (counter<write_size)); 
  Wire.endTransmission();
  address+=write_size; // Increment address for next write

  delay(6); // needs 5ms for page write
  }
  }

  void readEEPROM(int deviceaddress, unsigned int eeaddress, 
  char* data, unsigned int num_chars) 
  {
  unsigned char i=0;
  Wire.beginTransmission(deviceaddress);
  Wire.write((int)(eeaddress >> 8)); // MSB
  Wire.write((int)(eeaddress & 0xFF)); // LSB
  Wire.endTransmission();

  Wire.requestFrom(deviceaddress,num_chars);

  while(Wire.available()) data[i++] = Wire.read();

}
