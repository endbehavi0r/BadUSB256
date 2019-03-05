#include <Keyboard.h>
#include <SPI.h>
#include <SD.h>
unsigned int d=500;
void setup(){
  String dip="";
  for(;dip.length()<8;dip+=(!digitalRead(dip.length()+2)))pinMode(dip.length()+2,INPUT_PULLUP);
  if(!SD.begin(10))return;                                                                                                            
  File file=SD.open(dip+".txt");
  if(file){
    Keyboard.begin();                                                                                                                                                                           
    delay(500);
    String line="";
    while(file.available()) {
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
void Line(String l){
  int sp=l.indexOf(" ");
  if(sp==-1)Press(l);
  else if(l.substring(0,sp)=="STRING")Keyboard.print(l.substring(sp+1));
  else if(l.substring(0,sp)=="STRINGLN")Keyboard.println(l.substring(sp+1));
  else if(l.substring(0,sp)=="DEFAULT_DELAY")d=l.substring(sp+1).toInt();
  else if(l.substring(0,sp)=="DELAY")delay((l.substring(sp+1)=="")?d:l.substring(sp+1).toInt());
  else if(l.substring(0,sp)=="REM");
  else{
    String rest=l;
    while(rest.length()>0){
      int spx=rest.indexOf(" ");
      if (spx==-1){
        Press(rest);
        rest="";
      }else{
        Press(rest.substring(0, spx));
        rest=rest.substring(spx+1);
      }
      delay(500);
    }
  }
  Keyboard.releaseAll();
}
void Press(String b){
  if(b.length()==1)Keyboard.press(b[0]);
  else if (b.equals("ENTER"))Keyboard.press(0xB0);
  else if (b.equals("CTRL"))Keyboard.press(0x80);
  else if (b.equals("SHIFT"))Keyboard.press(0x81);
  else if (b.equals("ALT"))Keyboard.press(0x82);
  else if (b.equals("GUI"))Keyboard.press(0x83);
  else if (b.contains("UP")||b.equals("UPARROW"))Keyboard.press(0xDA);
  else if (b.equals("DOWN")||b.equals("DOWNARROW"))Keyboard.press(0xD9);
  else if (b.equals("LEFT")||b.equals("LEFTARROW"))Keyboard.press(0xD8);
  else if (b.equals("RIGHT")||b.equals("RIGHTARROW"))Keyboard.press(0xD7);
  else if (b.equals("PAGEUP"))Keyboard.press(0xD3);
  else if (b.equals("PAGEDOWN"))Keyboard.press(0xD6);
  else if (b.equals("CAPSLOCK"))Keyboard.press(0xC1);
  else if (b.equals("DELETE"))Keyboard.press(0xD4);
  else if (b.equals("HOME"))Keyboard.press(0xD2);
  else if (b.equals("ESC"))Keyboard.press(0xB1);
  else if (b.equals("INSERT"))Keyboard.press(0xD1);
  else if (b.equals("TAB"))Keyboard.press(0xB3);
  else if (b.equals("END"))Keyboard.press(0xD5);
  else if (b.equals("BACKSPACE"))Keyboard.press(0xB2);
  else if (b.equals("F1"))Keyboard.press(0xC2);
  else if (b.equals("F2"))Keyboard.press(0xC3);
  else if (b.equals("F3"))Keyboard.press(0xC4);
  else if (b.equals("F4"))Keyboard.press(0xC5);
  else if (b.equals("F5"))Keyboard.press(0xC6);
  else if (b.equals("F6"))Keyboard.press(0xC7);
  else if (b.equals("F7"))Keyboard.press(0xC8);
  else if (b.equals("F8"))Keyboard.press(0xC9);
  else if (b.equals("F9"))Keyboard.press(0xCA);
  else if (b.equals("F10"))Keyboard.press(0xCB);
  else if (b.equals("F11"))Keyboard.press(0xCC);
  else if (b.equals("F12"))Keyboard.press(0xCD);
  else if (b.equals("BLK100")){
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    Keyboard.print("u2588");
    Keyboard.releaseAll();
  }else if (b.equals("BLK75")){
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    Keyboard.print("u2593");
    Keyboard.releaseAll();
  }else if (b.equals("BLK50")){
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    Keyboard.print("u2592");
    Keyboard.releaseAll();
  }else if (b.equals("BLK25")){
    Keyboard.press(0x80);
    Keyboard.press(0x81);
    Keyboard.print("u2591");
    Keyboard.releaseAll();
  }
} 
void loop() {}
