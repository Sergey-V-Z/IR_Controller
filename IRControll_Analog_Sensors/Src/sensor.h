#include "filter_sma.h"

//******************
// CLASS: sensor
//
// DESCRIPTION:
//  distance optical sensor class
//
// CREATED: 03.03.2021, by Sergey
//
// FILE: sensor.h
//
class sensor: public filter{
  public:
   sensor();
   ~sensor();
   void setOffsetMin(uint16_t offset);
   void setOffsetMax(uint16_t offset);
   uint16_t getOffsetMin();
   uint16_t getOffsetMax();
   bool detectPoll();
   bool getdetect();
   
  private:
   uint16_t offsetMin = 0;
   uint16_t offsetMax = 4096;
   bool detect; // в зоне сенсора что то есть
};
