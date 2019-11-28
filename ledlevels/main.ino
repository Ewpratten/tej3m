/**
 * TEJ3M
 * By: Evan Pratten 
 */

#define beep boop

// LED outputs
const int outputs[] = {10, 9, 8, 7, 6, 5, 4, 3, 2};
const int output_count = (sizeof(outputs) / sizeof(outputs[0]));

#define sense_pin A0

void setup(){
    // Config, and pull down each output
    for (int i = 0; i < output_count; i++)
    {
        pinMode(outputs[i], OUTPUT);
        digitalWrite(outputs[i], LOW);
    }

    // Config the sensor
    pinMode(sense_pin, INPUT);

}

void writeLEDProgress(int progress, int max_progress){
    // Map progress to pins
    int led_height = map(progress, 512, max_progress, 0, output_count );

    // Write each LED
    for (size_t i = 0; i < output_count; i++)
    {
        if (i < led_height){
            digitalWrite(outputs[i], HIGH);
        } else {
            digitalWrite(outputs[i], LOW);
        }
    }
    
}

void loop(){

    // Read sensor
    int raw_light = analogRead(sense_pin);

    // Write LEDs
    writeLEDProgress(raw_light, 1000);
}