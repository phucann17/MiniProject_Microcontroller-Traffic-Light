#include "button.h"

const int MAX_BUTTON = 5;

int KeyReg0[5] = {SET, SET, SET, SET, SET};
int KeyReg1[5] = {SET, SET, SET, SET, SET};
int KeyReg2[5] = {SET, SET, SET, SET, SET};
int KeyReg3[5] = {SET, SET, SET, SET, SET};

int TimeOutForKeyPress[5] = {100, 100, 100, 100, 100};

int button_pressed[5] = {0, 0, 0, 0, 0};
int button_long_pressed[5] = {0, 0, 0, 0, 0};
int button_flag[5] = {0, 0, 0, 0, 0};

// Check if the button was pressed
int isButtonPressed(int button_index) {
    if (button_pressed[button_index] == 1) {
        button_pressed[button_index] = 0;
        return 1;
    }
    return 0;
}

// Check if the button was long-pressed
int isButtonLongPressed(int button_index) {
    if (button_long_pressed[button_index] == 1) {
        button_long_pressed[button_index] = 0;
        return 1;
    }
    return 0;
}

// Process button press (short or long)
void subKeyProcess(int button_index) {
    // Handle the button press event here
    button_flag[button_index] = 1;
    // Add specific logic for short press or long press
}

// Detect button input and process short/long presses
void getKeyInput() {
    for (int i = 0; i < MAX_BUTTON; i++) {
        KeyReg2[i] = KeyReg1[i];
        KeyReg1[i] = KeyReg0[i];

        // Replace MODIFY_BUTTON, MODE_BUTTON, etc., with the actual GPIO pins for your buttons
        KeyReg0[0] = HAL_GPIO_ReadPin(GPIOA, UP_BUTTON);
        KeyReg0[1] = HAL_GPIO_ReadPin(GPIOA, SET_BUTTON);
        // Add more buttons as needed

        // Debounce logic
        if ((KeyReg1[i] == KeyReg0[i]) && (KeyReg1[i] == KeyReg2[i])) {
            if (KeyReg2[i] != KeyReg3[i]) {
                KeyReg3[i] = KeyReg2[i];

                // Button is pressed
                if (KeyReg3[i] == PRESSED_STATE) {
                    TimeOutForKeyPress[i] = 200; // Reset long press timeout
                    button_pressed[i] = 1;       // Mark as a short press
                }
            } else {
                // If button is still pressed, decrement timeout for long press
                if (KeyReg3[i] == PRESSED_STATE) {
                    if (TimeOutForKeyPress[i] > 0) {
                        TimeOutForKeyPress[i]--;
                    } else {
                        // Long press detected
                        button_long_pressed[i] = 1;
                        TimeOutForKeyPress[i] = 200; // Reset timeout
                    }
                }
            }
        }
    }
}
