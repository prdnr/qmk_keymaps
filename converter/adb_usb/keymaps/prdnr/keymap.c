#include <adb_usb/adb_usb.h> /* QMK_KEYBOARD_H caused problems with clangd */

/* Layer declarations. */
enum layer_names { _STOCK, _QWERTY };

/* Combo declarations. */
enum combos { ASM, CW };

/* Combo presses. */
const uint16_t PROGMEM asm_combo[] = {KC_A, KC_S, KC_M, COMBO_END};
const uint16_t PROGMEM cw_combo[] = {KC_C, KC_W, COMBO_END};

/* Combo results. */
combo_t key_combos[COMBO_COUNT] = {
    [ASM] = COMBO(asm_combo, AS_TOGG),
    [CW] = COMBO(cw_combo, CW_TOGG),
};

/* clang-format off */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_STOCK] = LAYOUT_ext_ansi(
    KC_ESC,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                 KC_PSCR,KC_SCRL,KC_PAUS,                                DF(_QWERTY),
    KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_INS, KC_HOME, KC_PGUP,     KC_NUM,  KC_EQL, KC_PSLS, KC_PAST,
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_DEL, KC_END,  KC_PGDN,     KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
    KC_LCAP, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,                                      KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,                   KC_RSFT,                KC_UP,               KC_P1,   KC_P2,  KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                                  KC_RALT, KC_RCTL,                         KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,           KC_PDOT, KC_PENT
    ),

    [_QWERTY] = LAYOUT_ext_ansi(
    KC_ESC,  KC_F1,   KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,                 KC_F13, KC_F14,  KC_F15,                                DF(_STOCK),
    KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,   KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_INS, KC_HOME, KC_PGUP,     KC_NUM,  KC_EQL, KC_PSLS, KC_PAST,
    KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_DEL, KC_END,  KC_PGDN,     KC_P7,   KC_P8,  KC_P9,   KC_PMNS,
    KC_LCAP, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,          KC_ENT,                                      KC_P4,   KC_P5,  KC_P6,   KC_PPLS,
    KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH,                   KC_RSFT,                KC_UP,               KC_P1,   KC_P2,  KC_P3,
    KC_LCTL, KC_LALT, KC_LGUI,                KC_SPC,                                  KC_RALT, KC_RCTL,                         KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,           KC_PDOT, KC_PENT
    ),
};
/* clang-format on */

/* Keeps track if extra features should be enabled. */
static bool stock_mode = true;
/* Stores the desired autoshift state outside of _STOCK. */
static bool desire_autoshift = true;

/* Act when layer state changes. */
layer_state_t default_layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) == _STOCK) {
        autoshift_disable();
        stock_mode = true;
    } else {
        if (desire_autoshift) {
            autoshift_enable();
        }
        stock_mode = false;
    }
    return state;
}

/* React to key press */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == AS_TOGG) {
        /* Record autoshift state to resume where it was when coming out of _STOCK. */
        desire_autoshift = get_autoshift_state();
    }
    return true;
}

/* Decide when to squash combos. */
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Kill all combos when using _STOCK. */
    if (stock_mode) {
        return false;
    }

    return true;
}
