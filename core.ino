#include <Keyboard.h>
#include <SPI.h>
#include <SD.h>
unsigned int d=500;
String key[31]={"ENTER","CTRL","SHIFT","ALT","GUI","UP","DOWN","LEFT","RIGHT","PAGEUP","PAGEDOWN","CAPSLOCK","DELETE","HOME","ESC","INSERT","TAB","END","BACKSPACE","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12"};
uint8_t val[31]={0xB0,0x80,0x81,0x82,0x83,0xDA,0xD9,0xD8,0xD7,0xD3,0xD6,0xC1,0xD4,0xD2,0xB1,0xD1,0xB3,0xD5,0xB2,0xC2,0xC3,0xC4,0xC5,0xC6,0xC7,0xC8,0xC9,0xCA,0xCB,0xCC,0xCD};
void setup(){
  String dip ="";
  for(;dip.length()<8;dip+=!digitalRead(dip.length()+2))pinMode(dip.length()+2,INPUT_PULLUP);
  if(!SD.begin(10))return;
  File file=SD.open(dip+".txt");
  if(file){
    Keyboard.begin();
    delay(500);
    String line="";
    while(file.available()){
      char m=file.read();
      if (m==10){
        Line(line);
        line="";
      }
      else if((int)m!=13)line+=m;
    }
    Line(line);
    file.close();
    Keyboard.end();
    SD.end();
  }
}
void Line(String l) {
  int sp=l.indexOf(" ");
  if(sp==-1)press(l);
  else if(l.substring(0,sp)=="STRING")Keyboard.print(l.substring(sp+1));
  else if(l.substring(0,sp)=="STRINGLN")Keyboard.println(l.substring(sp+1));
  else if(l.substring(0,sp)=="DEFAULT_DELAY")d=l.substring(sp+1).toInt();
  else if(l.substring(0,sp)=="DELAY")delay((l.substring(sp+1)=="")?d:l.substring(sp+1).toInt());
  else if(l.substring(0,sp)=="REM");
  else {
    String rest=l;
    while(rest.length()>0){
      int spx=rest.indexOf(" ");
      if(spx==-1) {
        press(rest);
        rest="";
      }else{
        press(rest.substring(0,spx));
        rest=rest.substring(spx+1);
      }
      delay(500);
    }
  }
  Keyboard.releaseAll();
}
void press(String b) {
  if(b.length()==1)Keyboard.press(b[0]);
  else if(b.startsWith("BLK")){
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    if(b.endsWith("100"))Keyboard.print("u2588");
    else if(b.endsWith("75"))Keyboard.print("u2593");
    else if(b.endsWith("50"))Keyboard.print("u2592");
    else if(b.endsWith("25"))Keyboard.print("u2591");
    Keyboard.releaseAll();
  }else for(int i=0;i<31;i++)if(b.equals(key[i]))Keyboard.press(val[i]);
}
void loop() {}
