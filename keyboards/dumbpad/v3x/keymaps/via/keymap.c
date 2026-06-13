/*
Copyright 2022 imchipwood && deveth0

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
            BASE LAYER - Generic F13-F24 Pad
    /-----------------------------------------------------`
    |             |   F13   |   F14   |   F15   |  TO(3)  |
    |             |---------|---------|---------|---------|
    |             |   F16   |   F17   |   F18   |  TO(2)  |
    |             |---------|---------|---------|---------|
    |             |   F19   |   F20   |   F21   |  TO(1)  |
    |-------------|---------|---------|---------|---------|
    |    Mute     |   F22   |   F23   |   F24   |  TO(0)  |
    \-----------------------------------------------------'
    */
    [0] = LAYOUT(
                    KC_F13,   KC_F14,   KC_F15,   TO(3),
                    KC_F16,   KC_F17,   KC_F18,   TO(2),
                    KC_F19,   KC_F20,   KC_F21,   TO(1),
        KC_MUTE,    KC_F22,   KC_F23,   KC_F24,   TO(0)
    ),
    /*
            2nd LAYER  - RGB controls, Brightness on encoder
    /-----------------------------------------------------`
    |             | Mode-   | Mode+   |         | \/      |
    |             |---------|---------|---------|---------|
    |             | Hue-    | Hue+    |         | \/      |
    |             |---------|---------|---------|---------|
    |             | Sat-    | Sat+    | On/Off  | \/      |
    |-------------|---------|---------|---------|---------|
    |     \/      | Effect- | Effect+ |         | \/      |
    \-----------------------------------------------------'
    */
    [1] = LAYOUT(
                    RM_PREV,  RM_NEXT,  KC_NO,     KC_TRNS,
                    RM_HUED,  RM_HUEU,  KC_NO,     KC_TRNS,
                    RM_SATD,  RM_SATU,  RM_TOGG,   KC_TRNS,
        KC_NO,      RM_SPDD,  RM_SPDU,  KC_NO,     KC_TRNS
    ),
};
// clang-format on

bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            // main layer, volume
            if (clockwise) {
                tap_code(KC_VOLU);
            } else {
                tap_code(KC_VOLD);
            }
            break;
        default:
            // rgb control layer, effects
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
            break;
    }
    return false;
}
