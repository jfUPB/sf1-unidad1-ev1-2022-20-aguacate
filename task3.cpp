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
        SLOW,
        OFF,
        ON,
        WAIT_CHANGE_OFF
    };

    static constexpr uint32_t INTERVAL_SLOW = 1000;
    static constexpr uint32_t INTERVAL_MID = 500;
    static constexpr uint32_t INTERVAL_FAST = 125;
    static uint32_t lasTime;

    static TaskStates taskState = TaskStates::INIT;
    static TaskStates lastTask = TaskStates::INIT;
    const uint8_t led = 14;

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
        taskState = TaskStates::SLOW;
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

        if (buttonEvt.trigger == true)
        {
            if (buttonEvt.whichButton == BUTTONS::BTN_1)
            {
                taskState = TaskStates::WAIT_CHANGE_OFF;
            }
            else if (buttonEvt.whichButton == BUTTONS::BTN_2)
            {
                taskState = TaskStates::MID;
            }

            buttonEvt.trigger = false;
        }
        break;
    }
    case TaskStates::WAIT_CHANGE_OFF:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= INTERVAL_SLOW)
        {
            taskState = TaskStates::OFF;
        }

        
        break;
    }
    
    case TaskStates::OFF:
    {
        digitalWrite(led, LOW);

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::BTN_1)
            {
                taskState = TaskStates::SLOW;
                lastTask = TaskStates::OFF;
            }
            else if (buttonEvt.whichButton == BUTTONS::BTN_2)
            {
                taskState = TaskStates::FAST;
                lastTask = TaskStates::OFF;
            }
        }
        break;
    }
    case TaskStates::MID:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= INTERVAL_MID)
        {
            lasTime = currentTime;
            digitalWrite(led, ledStatus);
            ledStatus = !ledStatus;
        }

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::BTN_1)
            {
                taskState = TaskStates::ON;
            }
            else if (buttonEvt.whichButton == BUTTONS::BTN_2)
            {
                taskState = TaskStates::SLOW;
            }
        }
        break;
    }

    case TaskStates::ON:
    {
        digitalWrite(led, HIGH);

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            if (buttonEvt.whichButton == BUTTONS::BTN_1)
            {
                taskState = TaskStates::MID;
            }
            else if (buttonEvt.whichButton == BUTTONS::BTN_2)
            {
                taskState = TaskStates::FAST;
                lastTask = TaskStates::ON;
            }
        }
        break;
    }

    case TaskStates::FAST:
    {
        uint32_t currentTime = millis();
        if ((currentTime - lasTime) >= INTERVAL_FAST)
        {
            lasTime = currentTime;
            digitalWrite(led, ledStatus);
            ledStatus = !ledStatus;
        }

        if (buttonEvt.trigger == true)
        {
            buttonEvt.trigger = false;
            disarmKey[keyCounter] = buttonEvt.whichButton;
            keyCounter++;
            if (keyCounter == 5)
            {
                keyCounter = 0;
                if (compareKeys(secret, disarmKey) == true)
                {
                    taskState = lastTask;
                }
            }
        }
        break;
    }

    default:
    {
        break;
    }
    }
}
