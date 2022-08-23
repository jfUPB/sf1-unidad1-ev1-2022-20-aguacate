#include <Arduino.h>
#include "task3.h"
#include "events.h"

static bool compareKeys(BUTTONS *pSecret, BUTTONS *pKey)
{
    bool correct = true;
    for (uint8_t i = 0; i < 5; i++)
    {
        if (pSecret[i] != pKey[i])
        {
            correct = false;
            break;
        }
    }

    return correct;
}

void task3()
{

    enum class TaskStates
    {
        INIT,
        WAIT_CONFIG,
        COUNTING,
        MID,
        FAST,
        SLOW
    };
    static constexpr uint32_t INTERVAL_SLOW = 500;
    static constexpr uint32_t INTERVAL_MID = 250;
    static constexpr uint32_t INTERVAL_FAST = 125;
    static uint32_t lasTime;

    static TaskStates taskState = TaskStates::INIT;
    const uint8_t led = 14;
    const uint32_t BOMBINTERVAL = 1000U;
    const uint32_t LEDCOUNTERINTERVAL = 500U;

    static uint8_t bombCounter;
    static BUTTONS secret[5] = {
        BUTTONS::BTN_1,
        BUTTONS::BTN_1,
        BUTTONS::BTN_2,
        BUTTONS::BTN_2,
        BUTTONS::BTN_1,
    };

    static BUTTONS disarmKey[5] = {BUTTONS::NONE};
    static bool ledStatus = false;
    static uint8_t ledBombCountingState;
    static uint32_t initBombTimer;
    static uint32_t initLedCounterTimer;
    static uint8_t keyCounter;

    switch (taskState)
    {
    case TaskStates::INIT:
    {
        lasTime = millis();
        pinMode(led, OUTPUT);
        digitalWrite(led, HIGH);
        bombCounter = 20;
        keyCounter = 0;
        taskState = TaskStates::SLOW;
        break;
    }
    case TaskStates::WAIT_CONFIG:
    {

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::BTN_1)
            {
                if (bombCounter < 60)
                    bombCounter++;
            }
            else if (buttonEvt.whichButton == BUTTONS::BTN_2)
            {
                if (bombCounter > 10)
                    bombCounter--;
            }
            /*else if (buttonEvt.whichButton == BUTTONS::ARM_BTN)
            {
                initLedCounterTimer = millis();
                initBombTimer = millis();
                keyCounter = 0;
                taskState = TaskStates::COUNTING;
         }*/
            Serial.print("Counter: ");
            Serial.print(bombCounter);
            Serial.print("\n");
        }

        break;
    }
    case TaskStates::SLOW:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= INTERVAL_SLOW)
        {
            lasTime = currentTime;
            digitalWrite(led, ledStatus);
            ledStatus = !ledStatus;
        }
    }
    case TaskStates::MID:
    {
    }
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
    default:
    {
        break;
    }
    }
}
