
#define sense_pin A0
#define buzzer_pin 3

void setup(){
    pinMode(sense_pin, INPUT);
    pinMode(buzzer_pin, OUTPUT);
}

void loop(){
    int buzzer_output = map(analogRead(sense_pin), 0, 255, 255, -20) ;
    analogWrite(buzzer_pin, buzzer_output);
}