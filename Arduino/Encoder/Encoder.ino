byte ENC1_PIN = 11;
byte ENC2_PIN = 12;
 
int enc1_value;
int enc2_value;
char buff[2];
 
void setup() {
  pinMode(ENC1_PIN, INPUT);
  pinMode(ENC2_PIN, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  enc1_value = pulseIn(ENC1_PIN, HIGH);
  enc2_value = pulseIn(ENC2_PIN, HIGH);
  buff[0] = enc1_value;
  buff[1] = enc2_value;
  //Serial.write(buff, 2);
  Serial.println(enc2_value);
  delay(10);
}
