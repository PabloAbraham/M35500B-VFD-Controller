#ifndef M35500_H
#define M35500_H

#include <Arduino.h>

class M35500
{
public:
  using Pin = unsigned int;

  /**
  * Constructor for the M35500 class
  * @param CLK Serial clock pin, connect to CLK pin of IC
  * @param SIN Serial In pin, connect to SIN pin of IC
  * @param SOUT Serial Out pin, connect to SOUT pin of IC
  * @param CS Chip select pin, connect to CS pin of IC
  */
  M35500(M35500::Pin CLK, M35500::Pin SIN, M35500::Pin SOUT, M35500::Pin CS);

  /**
  * Initialises default pin states and resets M35500
  */
  void init();

  /**
  * Reset the M35500
  */
  void reset();
  //Number of Segments
  //2 Bits (Bit 0 and 1)
  enum class Segments
    {
        SexteenOrLess = 0b00000000,
        SeventeenOrMore = 0b00000001
    };

  //Number of Digits
  //2 Bits (Bit 2 and 3)
  enum class NumOfDigits
    {
        Seven = 0b00000000, // 7
        Eight = 0b00000100, // 8
        Nine = 0b00001000, // 9
        Ten = 0b00001100 // 10
    };

  //2 Bits (Bit 1 and 2)
  //Higher the Number brighter of the display
  enum class DisplayDuty
    {
        Fifthteen =  0b00000110, // 15/16
        Fourteen = 0b00000100, // 14/16
        Six =      0b00000010, // 6/16
        Five =     0b00000000 // 5/16
    };

  //1 Bit (Bit 0)
  enum class DisplayStatus
    {
        On =  0b00000001, // On
        Off = 0b00000000  // Off
    };

  //4 Bits (Bit 0 - 3)
  enum class DigitStartPin
    {
        D17 =  0b00000000, // D17
        D16 =  0b00000001, // D16
        D15 =  0b00000010, // D15
        D14 =  0b00000011, // D14
        D13 =  0b00000100, // D13
        D12 =  0b00000101, // D12
        D11 =  0b00000110, // D11
        D10 =  0b00000111, // D10
        D9 =   0b00001000, // D9
        D8 =   0b00001001, // D8
        D7 =   0b00001010, // D7
    };

    
    enum class PortSelection
    {
        P3_P0 =  0b00000000, // P3-P0
        P7_P4 =  0b00010000, // P7-P4
        
    };

  /**
  * Command 0 - Display Data Settings M35500
  * @param Seg Segments
  * @param NumDigits Number of Digits
  * @param DisplayData Display Data Bytes to send
  * @param DiplayDataLength amount of bytes to send
  */
  void Command0(Segments Seg, NumOfDigits NumDigits, uint8_t DisplayData[], size_t DiplayDataLength);

  /**
  * Command 1 - Display State Settings M35500
  * @param dispduty Dsplay Duty
  * @param dispstatus Display Status
  */
  void Command1(DisplayDuty dispduty, DisplayStatus dispstatus);

  /**
  * Command 2 - Digit Selection M35500
  * @param dispduty Dsplay Duty
  * @param dispstatus Display Status
  */
  void Command2(DigitStartPin DigitPin);

  /**
  * Command 3 - Port Data Setting M35500
  * @param PortSel Port Selection
  * @param PortDta (Low 4 Bits)
  */
  void Command3(PortSelection PortSel, uint8_t PortDta);


private:
    M35500::Pin CLK;
    M35500::Pin SIN;
    M35500::Pin SOUT;
    M35500::Pin CS;


    /**
     * Internal function, sends a single bit to M35500
     * @param bit Bit to send
     */
    void sendBit(const unsigned char bit);

    /**
     * Internal function, sends single byte to M35500
     * @param byte Byte to send
     */
    void sendByte(uint8_t byte);

    /**
     * Internal function, starts transfer to M35500
     */
    void starttransfer(void);

    /**
     * Internal function, ends transfer to M35500
     */
    void endtransfer(void);

    /**
     * Internal function, sends series of bytes to M35500
     * @param bytes Sequential bytes to send
     * @param length Number of bytes in the array (param bytes)
     */
    void sendBytes(uint8_t bytes[], size_t length);
};

#endif
