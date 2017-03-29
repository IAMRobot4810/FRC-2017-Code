#include <SPI.h>
#include <Pixy.h>
#include <math.h>

Pixy pix;
char bufr[3];
int xPos[2];
int heights[2];

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
  heights[0] = 0;
  heights[1] = 0;
  int xElem;
  float pegDist;
  float wallDist;
  bufr[0] = 0;
  bufr[1] = 0;
  bufr[2] = 0;

  if(blck){
    i++;
    if(i%10 == 0){
      i = 0;
      if(blck < 2){
        xPos[0] = 0;
        xPos[1] = 0;
      }
      else if(blck > 2){
        xElem = 0;
        for(j = 0; j < blck; j++){
          if((pix.blocks[j].width > 5 && pix.blocks[j].height > 10) && (pix.blocks[j].width < pix.blocks[j].height)){
            xPos[xElem] = pix.blocks[j].x;
            heights[xElem] = pix.blocks[j].height;
            xElem += 1;
          }
        }
      }
      else{
        for(j = 0; j < blck; j++){
         if((pix.blocks[j].width > 5 && pix.blocks[j].height > 10) && (pix.blocks[j].width < pix.blocks[j].height)){
            xPos[xElem] = pix.blocks[j].x;
            heights[xElem] = pix.blocks[j].height;
            xElem = xElem + 1;
          }
        }
      }
      if(xPos[0] == 0 || xPos[1] == 0){
        wallDist = 0;
        bufr[0] = wallDist;
        bufr[1] = 0;
        bufr[2] = 0;
        Serial.write(bufr, 3);
        //Serial.println(wallDist);
      }
      else{
        pegDist = abs(xPos[1] - xPos[0]);
        wallDist = (1960/pegDist);
        bufr[0] = wallDist;
        if(xPos[0] > xPos[1]){
          bufr[1] = xPos[1];
          bufr[2] = abs(319-xPos[0]);
        }
        else{
          bufr[1] = xPos[0];
          bufr[2] = abs(319-xPos[1]);
        }
        Serial.write(bufr, 3);
        //Serial.println(wallDist);
      }
    }
  }
}
