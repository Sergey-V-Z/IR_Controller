#include "sensor.h"

sensor :: sensor(){
   
}

sensor :: ~sensor(){
   
}

bool sensor :: detectPoll(){
  
   if((Result > offsetMin) && (Result < offsetMax)){
      detect = true;
   }
   else{detect = false;}
   return detect;
}

bool sensor :: getdetect(){
   return detect;
}

void sensor :: setOffsetMin(uint16_t offset){
   offsetMin = offset;
}

void sensor :: setOffsetMax(uint16_t offset){
   offsetMax = offset;
}

uint16_t sensor :: getOffsetMin(){
   return offsetMin;
}

uint16_t sensor :: getOffsetMax(){
   return offsetMax;
}
