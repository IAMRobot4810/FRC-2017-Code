byte PWM_PIN = 11;
 
int pwm_value;
char buff[1];
 
void setup() {
  pinMode(PWM_PIN, INPUT);
  Serial.begin(9600);
}
 
void loop() {
  pwm_value = pulseIn(PWM_PIN, HIGH);
  //Serial.println(pwm_value);
  double printVal = 0.2490234375*pwm_value;
  buff[0] = printVal;
  Serial.write(buff, 1);
  //Serial.println(printVal);
  delay(100);
}
