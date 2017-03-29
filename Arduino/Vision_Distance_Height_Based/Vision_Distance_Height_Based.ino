#include <SPI.h>
#include <Pixy.h>
#include <math.h>

Pixy pix;
char bufr[6];
int xPos[2];
int heights[2];
double tapeDists[2];
bool ledOn = true;
double tapeGap = 0;
double wallDistGapBased = 0;
double wallDistHeightBased = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pix.init();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  int j;
  int xElem = 0;
  uint16_t blck = pix.getBlocks();
  
  if(blck){
      if(blck < 2){
        xPos[0] = 0;
        xPos[1] = 0;
        heights[0] = 0;
        heights[1] = 0;
        tapeDists[0] = 0;
        tapeDists[1] = 0;
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
  }
  else{
      xPos[0] = 0;
      xPos[1] = 0;
      heights[0] = 0;
      heights[1] = 0;
      tapeDists[0] = 0;
      tapeDists[1] = 0;
      tapeGap = 0;
      wallDistGapBased = 0;
      wallDistHeightBased = 0;
      bufr[0] = 0;
      bufr[1] = 0;
      bufr[2] = 0;
      bufr[3] = 0;
      bufr[4] = 0;
      bufr[5] = 0;      
  }
  if(xPos[0] == 0 || xPos[1] == 0 || heights[0] == 0 || heights[1] == 0){
    xPos[0] = 0;
    xPos[1] = 0;
    heights[0] = 0;
    heights[1] = 0;
    tapeDists[0] = 0;
    tapeDists[1] = 0;
    wallDistGapBased = 0;
    wallDistHeightBased = 0;
    bufr[0] = wallDistGapBased;
    bufr[1] = wallDistHeightBased;
    bufr[2] = heights[0];
    bufr[3] = heights[1];
    bufr[4] = xPos[0];
    bufr[5] = xPos[1];
    //Serial.write(bufr, 6);
    Serial.print(wallDistGapBased);
    Serial.print(" ");
    Serial.print(wallDistHeightBased);
    Serial.print(" ");
    Serial.print(heights[0]);
    Serial.print(" ");
    Serial.print(heights[1]);
    Serial.print(" ");
    Serial.print(xPos[0]);
    Serial.print(" ");
    Serial.println(xPos[1]);
  }
  else{
    tapeGap = abs(xPos[1] - xPos[0]);
    wallDistGapBased = (1960/tapeGap);
    //wallDistHeightBased = heightsToMidDist(heights[0], heights[1], tapeGap);
    wallDistHeightBased = 0;
    bufr[0] = wallDistGapBased;
    bufr[1] = wallDistHeightBased;
    bufr[2] = heights[0];
    bufr[3] = heights[1];
    if(xPos[1] >= xPos[0]){
      bufr[4] = xPos[0];
      bufr[5] = 319-xPos[1];          
    }
    else{
      bufr[4] = 319-xPos[0];
      bufr[5] = xPos[1]; 
    }
    //Serial.write(bufr, 6);
    Serial.print(wallDistGapBased);
    Serial.print(" ");
    Serial.print(wallDistHeightBased);
    Serial.print(" ");
    Serial.print(heights[0]);
    Serial.print(" ");
    Serial.print(heights[1]);
    Serial.print(" ");
    Serial.print(xPos[0]);
    Serial.print(" ");
    Serial.println(xPos[1]);
  }
}

double heightToDist(double height){
  return 1224.53*pow(height, -1);
}

double heightsToMidDist(double height1, double height2, double gap){
  double dist1 = heightToDist(height1);
  double dist2 = heightToDist(height2);
  double distDiff = abs(dist1-dist2);
  double hypoteneuse = pow((pow(gap, 2) + pow(distDiff, 2)), 0.5);
  double halfHypoteneuse = hypoteneuse/2;
  double halfTapeGap = gap/2;
  double distAdd = pow((pow(halfHypoteneuse, 2) - pow(halfTapeGap, 2)), 0.5);
  if(height1 > height2){
    return distAdd + dist2;
  }
  else{
    return distAdd + dist1;
  }
}

