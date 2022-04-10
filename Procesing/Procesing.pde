import processing.serial.*; // libreria Serial para recibir señal de arduino
import netP5.*;          // Protocolo OSC para enviar a Pure Data
import oscP5.*;

OscP5 oscP5;    
NetAddress myRemoteLocation;
Serial myPort;

void setup(){
  size (500,500);
  frameRate(1);
  oscP5 = new OscP5(this,12000);
  myRemoteLocation = new NetAddress("127.0.0.1",12001);
  // puertos para lectura de ARDUINO Serial COM3
  myPort = new Serial(this,Serial.list()[0],9600);
  //println(Serial.list());
  myPort.bufferUntil('\n');
}
  
void draw(){
   background(255);
   // lee los datos enviados por Arduino
   String inString = myPort.readStringUntil('\n');
   if (inString != null ){
   String values = (inString);
   print (values);
   // envia datos a Pure Data
   OscMessage card = new OscMessage("card");
        card.add(float(values));
        oscP5.send(card, myRemoteLocation);
   //se muestra en pantalla el numero de tarjeta que se recibe y que se envia
   textSize(30);
   fill(50);
   text(values,40,120);
  }
}
