#include <Sim800l.h>
#include <SoftwareSerial.h>
Sim800l Sim800l;  //declare the library

char number[20];
char text[200];
char parent[20]="+94766897230";
String lat;
String lang;
String loc="";
String balance;
void setup(){
  Serial.begin(9600);
  Sim800l.begin();
  Sim800l.activateBearerProfile();
  Sim800l.signalQuality();
  Sim800l.delAllSms();
}

void loop(){
  Sim800l.activateBearerProfile();
  Sim800l.signalQuality();
  String sms=Sim800l.readSms(1);
  if(sms.substring(72,sms.length()-8).equals("Where")){
    Serial.println("Text equal to Where"); 
    String cordinates=Sim800l.dateNet();
    delay(800);
    if(!cordinates.equals("Your bag cannot locate")){
      lat=cordinates.substring(0,cordinates.indexOf(",")); //Get lattitude
      lang=cordinates.substring(cordinates.indexOf(",")+1,cordinates.length()); //Get longitude
      loc="Your bag is located at ("+cordinates+")"+"\nClick the link http://maps.google.com/maps?q="+lang+","+lat; //Create sending text message
      delay(800);
      loc.toCharArray(text,200);// Convert to a character array
      delay(800);
      Serial.println("Sending text: "+(String)text);
      delay(800);
      String no=sms.substring(sms.indexOf(",")+2,sms.indexOf(",")+14);
      no.toCharArray(number,20);
      Serial.println("Requested user: "+(String)number);
      delay(800);
      Sim800l.sendSms(number,text);
      Sim800l.delAllSms(); 
    }else{
      Serial.println(cordinates);
    } 
  }else if(sms.substring(72,sms.length()-8).equals("Check")){
    Serial.println("Text equal to check");
    balance =Sim800l.getBalance();
    delay(1000);
    Serial.println(balance);
    String no=sms.substring(sms.indexOf(",")+2,sms.indexOf(",")+14);
    no.toCharArray(number,20);
    delay(800);
    balance.toCharArray(text,200);
    delay(800);
    Sim800l.sendSms(number,text);
    Sim800l.delAllSms(); 
  }else if(sms.substring(72,sms.length()-8).equals("Help")){
    Serial.println("Text equal to Help");
    String cordinates=Sim800l.dateNet();
    delay(800);
    if(!cordinates.equals("Your bag cannot locate")){
      lat=cordinates.substring(0,cordinates.indexOf(",")); //Get lattitude
      lang=cordinates.substring(cordinates.indexOf(",")+1,cordinates.length()); //Get longitude
      String no=sms.substring(sms.indexOf(",")+2,sms.indexOf(",")+14);
      no.toCharArray(number,20);
      delay(800);
      loc="Help me. Click the link\nhttp://maps.google.com/maps?q="+lang+","+lat+"\nSent by: "+number; //Create sending text message
      loc.toCharArray(text,200);// Convert to a character array
      delay(1000);
      Serial.println(text);
      delay(800);
      Serial.println("Requested user: "+(String)number);
      delay(800);
      Sim800l.sendSms(parent,text);
      delay(800);
      Sim800l.callNumber(number);
      delay(800);
      Sim800l.delAllSms(); 
    }
    
  }else if(sms.substring(72,sms.length()-8).equals("Delete")){
    Serial.println("Text equal to delete");
    Sim800l.delAllSms();
  }
}
