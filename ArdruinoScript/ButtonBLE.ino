#include <SPI.h>
#include <boards.h>
#include <RBL_nRF8001.h>

// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status

void setup()
{  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  // Init. and start BLE library.
  ble_begin();
  
  // Enable serial debug
  Serial.begin(57600);
}
unsigned char buf[16] = {0};
unsigned char len = 0;

void loop()
{  
  if ( ble_connected() )
  {
    
    // read the state of the pushbutton value:
    buttonState = digitalRead(buttonPin);
    
    // check if the pushbutton is pressed.
    // if it is, the buttonState is HIGH:
    if (buttonState == HIGH) {
      
      ble_write('O');ble_write('N');
      
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      Serial.println("Led On");  
    }
    else {
      // turn LED off:
      Serial.println("Led Off");
      digitalWrite(ledPin, LOW);

    }
  
  }

  ble_do_events();
  
  if ( ble_available() )
  {
    while ( ble_available() )
    {
      Serial.write(ble_read());
    }
    
    Serial.println();
  }
}
