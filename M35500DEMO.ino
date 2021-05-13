#include "M35500.h" 

//      CLK, SIN, SOUT, CS
M35500 vfd(2, 3, 4, 5);

//uint8_t dispdta[] =   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0X00, 0x00};
//uint8_t dispdta[] =   {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0XFF, 0xFF};
uint8_t dispdta[] =   {0x00, 0x00, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0X00, 0x00};

size_t dsize = sizeof(dispdta);

int intermitent = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial Started");

  Serial.println("Initializing M35500");
  vfd.init();
  
  Serial.println("Setup Done"); 
}
  
void loop() {
  
  vfd.Command0(M35500::Segments::SexteenOrLess, M35500::NumOfDigits::Ten, dispdta, dsize);
  
  if (intermitent == 0)
  {
    Serial.println("Display On");
    vfd.Command1(M35500::DisplayDuty::Five, M35500::DisplayStatus::On );
  }
  else
  {
    Serial.println("Display Off");
    vfd.Command1(M35500::DisplayDuty::Five, M35500::DisplayStatus::Off );
  }
  intermitent = !intermitent;
     
  delay(500);

}
