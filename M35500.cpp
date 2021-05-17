//Created by Pablo Abraham 2021
//License Apache 2.0

#include "M35500.h"

  /**
  * Constructor for class M35500
  */
  M35500::M35500(M35500::Pin CLK, M35500::Pin SIN, M35500::Pin SOUT, M35500::Pin CS)
  {
    this->CLK = CLK;
    this->SIN = SIN;
    this->SOUT = SOUT;
    this->CS = CS;    
  }

  /**
  * Initialises default pin states and resets M35500
  */
  void M35500::init()
  {
    pinMode(this->CLK, OUTPUT);
    pinMode(this->SIN, OUTPUT);
    pinMode(this->CS, OUTPUT);
    pinMode(this->SOUT, INPUT);

    // Init default state
    digitalWrite(this->CS, HIGH);
    digitalWrite(this->CLK, HIGH);
    digitalWrite(this->SIN, HIGH);

    this->reset();
    return;
  }

  /**
  * Reset the M35500
  */
  void M35500::reset()
  {
    
  }

  /**
  * Command 0 - M35500
  */
  void M35500::Command0(Segments Seg, NumOfDigits NumDigits, uint8_t DisplayData[], size_t DiplayDataLength)
  {    
    uint8_t command = 0b11100000 | (uint8_t)Seg | (uint8_t) NumDigits;
    this->starttransfer();
    this->sendByte(command);
    this->sendBytes(DisplayData, DiplayDataLength);
    this->endtransfer();
    return;
  }

  /**
  * Command 1 - M35500
  */
  void M35500::Command1(DisplayDuty dispduty, DisplayStatus dispstatus)
  {    
    uint8_t command = 0b11000000 | (uint8_t)dispduty | (uint8_t) dispstatus;
    this->starttransfer();
    this->sendByte(command);
    this->endtransfer();
    return;
  }

  /**
  * Command 2 - M35500
  */
  void M35500::Command2(DigitStartPin DigitPin)
  {
    uint8_t command = 0b10100000 | (uint8_t)DigitPin;
    this->starttransfer();
    this->sendByte(command);
    this->endtransfer();
    return;
  }


  /**
  * Command 3 - M35500
  */
  void M35500::Command3(PortSelection PortSel, uint8_t PortDta)
  {
    uint8_t command = 0b10000000 | (uint8_t)PortSel | (PortDta & 0b00001111);
    this->starttransfer();
    this->sendByte(command);
    this->endtransfer();
    return;
  }
  

  /**
  * Sends a Bit to M35500
  */
  void M35500::sendBit(const unsigned char bit)
  {
    // Set clock low
    digitalWrite(this->CLK, LOW);

    // Set data bit
    digitalWrite(this->SIN, bit == 0? LOW : HIGH);
    delayMicroseconds(20);

    // Set clock high
    digitalWrite(this->CLK, HIGH);
    delayMicroseconds(20);
    return;
  }

  /**
  * Start Data Transfer to M35500
  */
  void M35500::starttransfer(void)
  {
      // Enable data transfer to IC (CS = Low)
      digitalWrite(this->CS, LOW);
  
      // Wait before starting data transfer
      delayMicroseconds(20);
  }

  /**
  * End Data Transfer to M35500
  */
  void M35500::endtransfer(void)
  {
      // Wait before ending data transfer
      delayMicroseconds(20);
  
      // Stop data transfer to IC
      digitalWrite(this->CS, HIGH);
  }

  /**
  * Send a Byte to M35500
  */
  void M35500::sendByte(uint8_t byte)
  {
      // Send one bit at a time
      for (int i = 0; i < 8; i++)
      {
          this->sendBit(((byte >> i) & 0b00000001));
      }
  
      delayMicroseconds(20);
  }

  /**
  * Send multiple bytes to M35500
  */
  void M35500::sendBytes(uint8_t bytes[], size_t length)
  {
      // Send Bytes
      for (int j = 0; j < length; j++)
      {
          this->sendByte(bytes[j]);
      }      
      return;
  } 
