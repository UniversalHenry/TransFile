//项目六 报警器
float sinVal;
int toneVal;
void setup(){
pinMode(8, OUTPUT);
}
void loop(){
for(int x=0; x<180; x++){
//将sin函数角度转化为弧度
sinVal = (sin(x*(3.1412/180)));
//用sin函数值产生声音的频率
toneVal = 2000+(int(sinVal*1000));
//给引脚8一个
tone(8, toneVal);
delay(2);
}
}
