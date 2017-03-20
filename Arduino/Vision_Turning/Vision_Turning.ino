#include <Pixy.h>
#include <SPI.h>

Pixy pix;
char bufr[1];
int heights[2];
void setup() {
 Serial.begin(9600);
 pix.init();

}

void loop() {
 static int i=0;
 int j;
 int hElem = 0;
 uint16_t blck = pix.getBlocks();
 if(blck){
  i++;
  if(i%10 ==0){
    if(blck < 2){
        heights[0]=0;
        heights[1] = 0;
      }
      else if(blck > 2){
        hElem = 0;
        for(j = 0; j < blck; j++){
          if(pix.blocks[j].width > 5 && pix.blocks[j].height > 10){
            heights[hElem] = pix.blocks[j].height;
            hElem += 1;
          }
        }
      }
      else{
        for(j = 0; j < blck; j++){
         if(pix.blocks[j].width > 5 && pix.blocks[j].height > 10){
            heights[hElem] = pix.blocks[j].height;
            hElem = hElem + 1;
          }
        }
      }
     for(int j=0; j< 2; j++){
      Serial.print("block");
      Serial.print(j);
      Serial.print(" ");
      Serial.print(heights[j]);
      Serial.print(" ");
    }
      Serial.println(" ");
  }
  
 }
 

}
