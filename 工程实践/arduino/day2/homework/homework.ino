int mode = 0;
bool interrupt = false;
bool done = false;
bool shine = false;
unsigned long changeTime;
const int LED[4]={11,4,5,6};
const int SIGNAL_LED=LED[0];
const int KEY[4]={3,8,9,10};

void setup() {
  // put your setup code here, to run once:
  mode = 0;
  interrupt = false;
  done = false;
  shine = false;
  changeTime = millis();
  for(int i = 0; i < 4; i++)pinMode(LED[i],OUTPUT);
  for(int i = 1; i < 4; i++)pinMode(KEY[i],INPUT);
  digitalWrite(SIGNAL_LED,HIGH);
  my_delay(200);
  digitalWrite(SIGNAL_LED,LOW);
  attachInterrupt(1, set, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(shine){
    my_delay(200);
    digitalWrite(SIGNAL_LED,LOW);
    shine = false;
  }
  if(mode > 0){
    switch(mode){
     case 1:cmd1();break;
     case 2:cmd2();break;
     case 3:cmd3();break;
      default:mode = 0;
    }
    if(done){done = false;interrupt = false;}
  }else
  {
    mode = 0;
    for(int i = 0;i<4;i++)digitalWrite(LED[i],LOW);
    my_delay(1000);
  }
}

void set(){
  for(int i = 0;i<4;i++)digitalWrite(LED[i],LOW);
  int new_mode = 0;
  for(int i = 1; i<=3; i++){
    int state = HIGH;
    state = digitalRead(KEY[i]);
    if(state == LOW && (millis() - changeTime)> 500)new_mode = i;
  }
  changeTime = millis();
  if(mode == new_mode){
    mode = 0;
  }else{
    mode = new_mode;
  }
  interrupt = true;
  done = false;
  digitalWrite(SIGNAL_LED,HIGH);
  shine = true;
}

void my_delay(unsigned int t){
  for(int i=0; i<t; i++){
    delay(1);
    if(interrupt){
      done = true;
      return;
    }
  }
}


void cmd1(){
    digitalWrite(LED[1],HIGH);
    digitalWrite(LED[2],LOW);
    digitalWrite(LED[3],LOW);
    while(1){
      my_delay(1000);
      if(interrupt){
        done = true;
        return;
      }
    }
}

void cmd2(){
  digitalWrite(LED[2],HIGH);
  digitalWrite(LED[1],LOW);
  digitalWrite(LED[3],LOW);
while(1){
  digitalWrite(LED[2],HIGH);
  my_delay(1000);
  if(interrupt){
    done = true;
    return;
  }
  digitalWrite(LED[2],LOW);
  my_delay(1000);
  if(interrupt){
    done = true;
    return;
  }
  }
}

void fadeOn(unsigned int time,int increament){
for (byte value = 0 ; value < 255; value+=increament){
  analogWrite(LED[3], value);
  if(interrupt){
    done = true;
    return;
  }
  my_delay(time/(255/5));
  if(interrupt){
    analogWrite(LED[3], 0);
    done = true;
    return;
  }
}
}

void fadeOff(unsigned int time,int decreament){
for (byte value = 255; value >0; value-=decreament){
  analogWrite(LED[3], value);
  if(interrupt){
    done = true;
    return;
  }
  my_delay(time/(255/5));
  if(interrupt){
    done = true;
    return;
  }
}
}

void cmd3(){
  digitalWrite(LED[3],HIGH);
  digitalWrite(LED[1],LOW);
  digitalWrite(LED[2],LOW);
  while(1){
    fadeOff(3000,5);
    if(interrupt){
      done = true;
      return;
    }
    fadeOn(3000,5);
    if(interrupt){
      done = true;
      return;
    }
  }
}

