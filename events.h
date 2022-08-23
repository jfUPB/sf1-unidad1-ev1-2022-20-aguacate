#ifndef _EVENTS_H_
#define _EVENTS_H_

enum class BUTTONS{NONE, BTN_1, BTN_2};

typedef struct{
    bool trigger;
    BUTTONS whichButton;
} buttonEvt_t;

extern buttonEvt_t buttonEvt;

#endif