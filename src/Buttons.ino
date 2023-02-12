#include "Buttons.h"

int ButtonState;

enum State
{
    LEFT,
    UP,
    DOWN,
    RIGHT,
    SELECT,
};

int GetButtonsState()
{

    ButtonState = analogRead(ButtonPin);
    if (ButtonState < RIGHT_THRESHOLD)
        return RIGHT;

    else if (ButtonState < UP_THRESHOLD)
        return UP;

    else if (ButtonState < DOWN_THRESHOLD)
        return DOWN;

    else if (ButtonState < LEFT_THRESHOLD)
        return LEFT;

    else if (ButtonState < SELECT_THRESHOLD)
        return SELECT;
}
