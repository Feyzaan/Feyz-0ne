#include QMK_KEYBOARD_H

// Keymap layers
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │   │   │ F │ M │
     * ├───┼───┼───┼───┤
     * │ E │ ↑ │ Q │ R │
     * ├───┼───┼───┼───┤
     * │ ← │ ↓ │ → │ F │
     * ├───┼───┼───┼───┤
     * │   │   │   │   │
     * └───┴───┴───┴───┘
     */
    [0] = LAYOUT_ortho_4x4(
        KC_A,   KC_B,   KC_C,    KC_D,
        KC_E,    KC_F,   KC_G,    KC_H,
        KC_LEFT, KC_DOWN, KC_RIGHT,KC_F,
        KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {
        {KC_VOLD, KC_VOLU},           // Encoder 0 CCW, CW
        {KC_PGDN, KC_PGDN}  // Encoder 1 CCW, CW
    }
};

bool encoder_button_1_last = true;
bool encoder_button_2_last = true;

void keyboard_post_init_user(void) {
    // Initialize encoder button pins
    setPinInputHigh(B1);  // Encoder button 1 (SWITCH1)
    setPinInputHigh(F6);  // Encoder button 2 (SWITCH2)
}

void housekeeping_task_user(void) {
    // Encoder Button 1: Mute
    bool current1 = readPin(B1);
    if (!current1 && encoder_button_1_last) {
        tap_code(KC_MUTE);
    }
    encoder_button_1_last = current1;

    // Encoder Button 2: Screenshot (Win + Shift + S)
    bool current2 = readPin(F6);
    if (!current2 && encoder_button_2_last) {
        tap_code16(LGUI(LSFT(KC_S)));
    }
    encoder_button_2_last = current2;
}