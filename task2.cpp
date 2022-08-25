#include <Arduino.h>
#include "task2.h"
#include "events.h"

void task2()
{
    enum class TaskState
    {
        INIT,
        WAIT_PRESS,
        WAIT_STABLE,
        WAIT_RELEASE
    };
    static TaskState taskState = TaskState::INIT;
    static uint8_t lastButtonPressed;
    static uint32_t initStableTime;

    const uint8_t BTN_1_PIN = 12;
    const uint8_t BTN_2_PIN = 33;
    const uint32_t STABLE_TIME = 100;

    switch (taskState)
    {
    case TaskState::INIT:
    {
        pinMode(BTN_1_PIN, INPUT_PULLUP);
        pinMode(BTN_2_PIN, INPUT_PULLUP);
        printf("Button pressed: %d\n");

        taskState = TaskState::WAIT_PRESS; 
        break;
    }
    case TaskState::WAIT_PRESS:
    {
        if(digitalRead(BTN_2_PIN) == LOW)
        {
            lastButtonPressed = BTN_2_PIN;
            initStableTime = millis();
            taskState = TaskState::WAIT_STABLE;
        }
        if(digitalRead(BTN_1_PIN) == LOW)
        {
            lastButtonPressed = BTN_1_PIN;
            initStableTime = millis();
            taskState = TaskState::WAIT_STABLE;
        }
        break;
    }
    case TaskState::WAIT_STABLE:
    {
        if(digitalRead(lastButtonPressed) != LOW){
            taskState = TaskState::WAIT_PRESS;
        }
        else if ( (millis() - initStableTime) > STABLE_TIME){
            if(lastButtonPressed == BTN_1_PIN) buttonEvt.whichButton = BUTTONS::BTN_1;
            else if(lastButtonPressed == BTN_2_PIN) buttonEvt.whichButton = BUTTONS::BTN_2;
            buttonEvt.trigger = true;
            printf("Button pressed: %d\n", lastButtonPressed);
            taskState = TaskState::WAIT_RELEASE;
        }
        break;
    }
    case TaskState::WAIT_RELEASE:{
        if(digitalRead(lastButtonPressed) == HIGH){
            taskState = TaskState::WAIT_PRESS;
        }
        break;
    }

    default:
    {
    }
    }
}