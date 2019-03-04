#include <Keyboard.h>
#include <SPI.h>
#include <SD.h>
File file;  
int d=500;
void setup(){
  String dip="";
  while(dip.length()<8){
    pinMode(dip.length()+2,INPUT_PULLUP);
    dip+=(digitalRead(dip.length()+2)==1)?"0":"1";
  }
  if(!SD.begin(10))return;
  file=SD.open(dip+".txt");
  if(file){
    Keyboard.begin();
    delay(500);
    String line="";
    while(file.available()) {
      char m=file.read();
      if (m=='\n'){
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
      int spindex=rest.indexOf(" ");
      if (spindex==-1){
        Press(rest);
        rest="";
      }else{
        Press(rest.substring(0, spindex));
        rest=rest.substring(spindex+1);
      }
      delay(500);
    }
  }
  Keyboard.releaseAll();
}
void Press(String b){
  if(b.length()==1)Keyboard.press(b[0]);
  else if (b.equals("ENTER"))Keyboard.press(KEY_RETURN);
  else if (b.equals("CTRL"))Keyboard.press(KEY_LEFT_CTRL);
  else if (b.equals("SHIFT"))Keyboard.press(KEY_LEFT_SHIFT);
  else if (b.equals("ALT"))Keyboard.press(KEY_LEFT_ALT);
  else if (b.equals("GUI"))Keyboard.press(KEY_LEFT_GUI);
  else if (b.equals("UP")||b.equals("UPARROW"))Keyboard.press(KEY_UP_ARROW);
  else if (b.equals("DOWN")||b.equals("DOWNARROW"))Keyboard.press(KEY_DOWN_ARROW);
  else if (b.equals("LEFT")||b.equals("LEFTARROW"))Keyboard.press(KEY_LEFT_ARROW);
  else if (b.equals("RIGHT")||b.equals("RIGHTARROW"))Keyboard.press(KEY_RIGHT_ARROW);
  else if (b.equals("PAGEUP"))Keyboard.press(KEY_PAGE_UP);
  else if (b.equals("PAGEDOWN"))Keyboard.press(KEY_PAGE_DOWN);
  else if (b.equals("CAPSLOCK"))Keyboard.press(KEY_CAPS_LOCK);
  else if (b.equals("DELETE"))Keyboard.press(KEY_DELETE);
  else if (b.equals("HOME"))Keyboard.press(KEY_HOME);
  else if (b.equals("ESC"))Keyboard.press(KEY_ESC);
  else if (b.equals("INSERT"))Keyboard.press(KEY_INSERT);
  else if (b.equals("TAB"))Keyboard.press(KEY_TAB);
  else if (b.equals("END"))Keyboard.press(KEY_END);
  else if (b.equals("F1"))Keyboard.press(KEY_F1);
  else if (b.equals("F2"))Keyboard.press(KEY_F2);
  else if (b.equals("F3"))Keyboard.press(KEY_F3);
  else if (b.equals("F4"))Keyboard.press(KEY_F4);
  else if (b.equals("F5"))Keyboard.press(KEY_F5);
  else if (b.equals("F6"))Keyboard.press(KEY_F6);
  else if (b.equals("F7"))Keyboard.press(KEY_F7);
  else if (b.equals("F8"))Keyboard.press(KEY_F8);
  else if (b.equals("F9"))Keyboard.press(KEY_F9);
  else if (b.equals("F10"))Keyboard.press(KEY_F10);
  else if (b.equals("F11"))Keyboard.press(KEY_F11);
  else if (b.equals("F12"))Keyboard.press(KEY_F12);
  else if (b.equals("BLK100")){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("u2588");
    Keyboard.releaseAll();
  }else if (b.equals("BLK75")){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("u2593");
    Keyboard.releaseAll();
  }else if (b.equals("BLK50")){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("u2592");
    Keyboard.releaseAll();
  }else if (b.equals("BLK25")){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.print("u2591");
    Keyboard.releaseAll();
  }
}
void loop() {}
