#include "my_library.h"

void setup() 
{
  Serial.begin(9600);
  
  
}

void loop() {
  while(1){
    int result = addThreeInts(4,3,2);
    Serial.println(result);
    delay(10000);
    }
  
  }
