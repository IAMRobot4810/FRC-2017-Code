#include <SPI.h>
#include <Pixy.h>
#include <math.h>

Pixy pix;
char bufr[1];
int xPos[2];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pix.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  static int i = 0;
  int j;
  uint16_t blck = pix.getBlocks();
  xPos[0] = 0;
  xPos[1] = 0;
  int xElem;
  float pegDist;
  float wallDist;
  bufr[0] = 0;

  if(blck){
    i++;
    if(i%10 == 0){
      if(blck < 2){
        xPos[1] = 0;
      }
      else if(blck > 2){
        xElem = 0;
        for(j = 0; j < blck; j++){
          if(pix.blocks[j].width > 5 && pix.blocks[j].height > 10){
            xPos[xElem] = pix.blocks[j].x;
            xElem += 1;
          }
        }
      }
      else{
        for(j = 0; j < blck; j++){
         if(pix.blocks[j].width > 5 && pix.blocks[j].height > 10){
            xPos[xElem] = pix.blocks[j].x;
            xElem = xElem + 1;
          }
        }
      }
      if(xPos[0] == 0 || xPos[1] == 0){
        wallDist = 0;
        bufr[0] = wallDist;
        //Serial.write(bufr, 1);
        Serial.println(wallDist);
      }
      else{
        pegDist = abs(xPos[1] - xPos[0]);
        wallDist = (1960/pegDist);
        bufr[0] = wallDist;
        //Serial.write(bufr, 1);
        Serial.println(wallDist);
      }
    }
  }
}
