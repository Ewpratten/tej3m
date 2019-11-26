/**
 * TEJ3M
 * By: Evan Pratten
 */

#define beep boop

// Players
const int players[][2] = {
    {2, A3},
    {3, A2},
    {4, A1}};
const int player_count = (sizeof(players) / sizeof(players[0]));

// Defines
#define reset_button A0
#define reset_led 13
#define buzzer 12
#define button_thresh 200

int player_latch = -1;

void setup()
{

    // Set each player for input and output
    for (int i = 0; i < player_count; i++)
    {
        // Set LED pin
        pinMode(players[i][0], OUTPUT);

        // Set button pin
        pinMode(players[i][1], INPUT);
    }

    // Set reset pins and buzzer
    pinMode(reset_button, INPUT);
    pinMode(reset_led, OUTPUT);
    pinMode(buzzer, OUTPUT);

    // force-disable reset LED
    digitalWrite(reset_led, LOW);
}

void loop()
{
    // Check if we can sense a button
    if(player_latch == -1){
        
        // Check each button
        for (int i = 0; i < player_count; i++)
        {
            
            // Set the latch if button pressed
            if(analogRead(players[i][1]) >= button_thresh){
                player_latch = i;
                break;
            }
        }

        // One-time write LEDs
        for (int i = 0; i < player_count; i++){
            if(i == player_latch){
                // Write LED
                digitalWrite(players[i][0], HIGH);

                // Beep for a bit
                digitalWrite(buzzer, HIGH);
                delay(400);
                digitalWrite(buzzer, LOW);

            }
            else
            {
                digitalWrite(players[i][0], LOW);
            }
        }
        
    }

    // Handle resets
    if (analogRead(reset_button) >+ button_thresh){
        player_latch = -1;
        digitalWrite(reset_led, HIGH);
    } else {
        digitalWrite(reset_led, LOW);
    }
}