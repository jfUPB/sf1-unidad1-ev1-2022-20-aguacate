#include <Arduino.h>
#include "task1.h"
#include "events.h"

void task1()
{
    /*enum class TaskState
    {
        INIT,
        WAIT_COMMANDS
    };
    static TaskState taskState = TaskState::INIT;
    static uint8_t lastButtonPressed;
    static uint32_t initStableTime;

    const uint8_t BTN_1_PIN = 33;
    const uint8_t BTN_2_PIN = 13;
    const uint8_t LED_PIN = 21;
    const uint32_t STABLE_TIME = 100;
    switch (taskState)
    {
    case TaskState::INIT:
    {
        Serial.begin(115200);
        taskState = TaskState::WAIT_COMMANDS;
        break;
    }
    case TaskState::WAIT_COMMANDS:
    {
        
    }
    default:
    {
    }
    }*/
    
    /*case TaskStates::RAPIDO:
    {

        uint32_t timeNow = millis();

        if ((timeNow - initBombTimer) > BOMBINTERVAL)
        {
            initBombTimer = timeNow;
            bombCounter--;
            Serial.print("Counter: ");
            Serial.print(bombCounter);
            Serial.print("\n");
            if (bombCounter == 0)
            {
                ledBombCountingState = HIGH;
                Serial.print("BOMB BOOM\n");
                digitalWrite(HIGH);
                delay(2000);
                digitalWrite(LOW);
                digitalWrite(ledBombCountingState);
                bombCounter = 20;
                taskState = TaskStates::WAIT_CONFIG;
            }
        }
        if ((timeNow - initLedCounterTimer) > LEDCOUNTERINTERVAL)
        {
            initLedCounterTimer = timeNow;
            ledBombCountingState = !ledBombCountingState;
            digitalWrite(ledBombCountingState);
        }

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            disarmKey[keyCounter] = buttonEvt.whichButton;
            keyCounter++;
            if (keyCounter == 7)
            {
                keyCounter = 0;
                if (compareKeys(secret, disarmKey) == true)
                {
                    ledBombCountingState = HIGH;
                    digitalWrite(ledBombCountingState);
                    Serial.print("BOMB DISARM\n");
                    bombCounter = 20;
                    taskState = TaskStates::WAIT_CONFIG;
                }
            }
        }

        break;
    }*/
}
