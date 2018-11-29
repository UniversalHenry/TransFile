//项目一 —— LED 闪烁
/*
描述：LED每隔一秒交替亮灭一次
*/
int ledPin = 7;
int main() {
pinMode(ledPin, OUTPUT);
while(1){
  loop();
}
}
void loop() {
digitalWrite(ledPin,HIGH);
delay(1000);
digitalWrite(ledPin,LOW);
delay(1000);
}
