#define RELAY_1_PIN         12
#define RELAY_2_PIN         11
#define RELAY_3_PIN         10
#define RELAY_4_PIN         9
#define RELAY_5_PIN         8
#define RELAY_6_PIN         7
#define RELAY_7_PIN         6
#define RELAY_8_PIN         5

#define SERIAL_LEN          2
String serial_buff;
bool serial_complete        = false;

uint32_t led_time;
bool led_state;

void setup(){
    Serial.begin(9600);
    serial_buff.reserve(SERIAL_LEN);

    pinMode(LED_BUILTIN, OUTPUT);

    pinMode(RELAY_1_PIN, OUTPUT);
    pinMode(RELAY_2_PIN, OUTPUT);
    pinMode(RELAY_3_PIN, OUTPUT);
    pinMode(RELAY_4_PIN, OUTPUT);
    pinMode(RELAY_5_PIN, OUTPUT);
    pinMode(RELAY_6_PIN, OUTPUT);
    pinMode(RELAY_7_PIN, OUTPUT);
    pinMode(RELAY_8_PIN, OUTPUT);

    led_time = millis();
}

void loop(){
    if(serial_complete){
        serial_complete = false;

        if(serial_buff == "10")     {   digitalWrite(RELAY_1_PIN, HIGH);    }
        else if(serial_buff == "11"){  digitalWrite(RELAY_1_PIN, LOW); }

        if(serial_buff == "20")     {   digitalWrite(RELAY_2_PIN, HIGH);    }
        else if(serial_buff == "21"){  digitalWrite(RELAY_2_PIN, LOW); }

        if(serial_buff == "30")     {   digitalWrite(RELAY_3_PIN, HIGH);    }
        else if(serial_buff == "31"){  digitalWrite(RELAY_3_PIN, LOW); }

        if(serial_buff == "40")     {   digitalWrite(RELAY_4_PIN, HIGH);    }
        else if(serial_buff == "41"){  digitalWrite(RELAY_4_PIN, LOW); }

        if(serial_buff == "50")     {   digitalWrite(RELAY_5_PIN, HIGH);    }
        else if(serial_buff == "51"){  digitalWrite(RELAY_5_PIN, LOW); }

        if(serial_buff == "60")     {   digitalWrite(RELAY_6_PIN, HIGH);    }
        else if(serial_buff == "61"){  digitalWrite(RELAY_6_PIN, LOW); }

        if(serial_buff == "70")     {   digitalWrite(RELAY_7_PIN, HIGH);    }
        else if(serial_buff == "71"){  digitalWrite(RELAY_7_PIN, LOW); }

        if(serial_buff == "80")     {   digitalWrite(RELAY_8_PIN, HIGH);    }
        else if(serial_buff == "81"){  digitalWrite(RELAY_8_PIN, LOW); }

        if(serial_buff == "00")     {   
            digitalWrite(RELAY_1_PIN, HIGH);
            digitalWrite(RELAY_2_PIN, HIGH);
            digitalWrite(RELAY_3_PIN, HIGH);
            digitalWrite(RELAY_4_PIN, HIGH);
            digitalWrite(RELAY_5_PIN, HIGH);
            digitalWrite(RELAY_6_PIN, HIGH);
            digitalWrite(RELAY_7_PIN, HIGH);
            digitalWrite(RELAY_8_PIN, HIGH);    
        }
        else if(serial_buff == "01"){  
            digitalWrite(RELAY_1_PIN, LOW);
            digitalWrite(RELAY_2_PIN, LOW);
            digitalWrite(RELAY_3_PIN, LOW);
            digitalWrite(RELAY_4_PIN, LOW);
            digitalWrite(RELAY_5_PIN, LOW);
            digitalWrite(RELAY_6_PIN, LOW);
            digitalWrite(RELAY_7_PIN, LOW);
            digitalWrite(RELAY_8_PIN, LOW);    
        }

        Serial.println(serial_buff);
        serial_buff = "";
    }

    if((millis() - led_time) > 1000){
        led_time = millis();

        toggleLed();
    }
}

void toggleLed(){
  if(led_state){
    digitalWrite(LED_BUILTIN, LOW);
    led_state = false;
  }else{
    digitalWrite(LED_BUILTIN, HIGH);
    led_state = true;
  }
}

/******* Serial Interrupt Event Callback ********/
void serialEvent(){
  while(Serial.available()){
    char inChar = (char) Serial.read();
    if(inChar == '\n'){
      serial_complete = true;
    }else if(inChar == '\r'){
      // do nothing
    }else{
      if(!serial_complete){
        serial_buff += inChar;
      }
    }
  }
}