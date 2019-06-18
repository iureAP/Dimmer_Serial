#include <mbed.h>
#include <USBSerial.h>

int main() {

USBSerial serial;
PwmOut led(PD_12);
static const int period = 10;
led.period_ms(period);
int increment = 0;
led.pulsewidth_ms(1);
float brightness = 0; 
char byte_received;

  while(1) {
    if(serial.readable()){
      byte_received = serial.getc(); 
      switch (byte_received) {
      case '-':
        if(increment > 0){
          increment--;
          led.pulsewidth_ms(increment);
        }
        break;
      case '+':
        if(increment < 10){
          increment++;
          led.pulsewidth_ms(increment);
        }
        break;
      }
      brightness = (increment / static_cast<float>(period)) * 100;
      serial.printf(" brightness = %.2f % \n ", brightness);
      wait_ms(100);
    }
  }
}