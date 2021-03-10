#include "sensor.h"

sensor :: sensor(){
   
}

sensor :: ~sensor(){
   
}

bool sensor :: detectPoll(){
  
   //if((Result > offsetMin) && (Result < offsetMax)){
   if(Result > offsetMin){
      detect = true;
   }
   else{detect = false;}
   return detect;
}

void sensor :: Call(uint16_t *data){
  peak = 0;
  gorge = 0;
  for(int i = 0; i < timeCall; ++i)
  {
     Filter_SMA(*data);
     osDelay(1);
  }
   offsetMax = peak;
   offsetMin = gorge;
      
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
