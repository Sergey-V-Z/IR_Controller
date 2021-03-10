#include "filter_sma.h"

void filter :: Filter_SMA(uint16_t For_Filtered)
{
   /* Load new value */
   Filter_Buffer[FILTER_SMA_ORDER - 1] = For_Filtered;
   /* For output value */
   uint32_t Output = 0;
   /* Sum */
   for(uint8_t i = 0; i < FILTER_SMA_ORDER; i++)
   {
      Output += Filter_Buffer[i];
   }
   /* Divide */
   Output /= FILTER_SMA_ORDER;
   /* Left Shift */
   for(uint8_t i = 0; i < FILTER_SMA_ORDER; i++)
      Filter_Buffer[i] = Filter_Buffer[i+1];
   /* Return filtered value */
   Result = (uint16_t) Output;
   
   if(Result > peak){peak = Result;}
   if(Result < gorge){gorge = Result;}
}

uint16_t filter :: Get_Result(){
   return Result;
}

filter :: filter(){
   
}

filter :: ~filter(){
   
}
