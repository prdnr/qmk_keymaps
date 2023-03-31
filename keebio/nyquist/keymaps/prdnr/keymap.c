#include <nyquist/rev3/rev3.h> /* QMK_KEYBOARD_H caused problems with clangd */

/* Layer declarations. */
enum layer_names { _QWERTY, _ARROWS, _QMK, _NUMPAD, _MOUSE, _FN, _GAMING, _GAMING_MOUSE };

/* Combo declarations. */
/* clang-format off */
enum combos { 
    /* Top Row. */
    QA, WS, ED, RF, TG,
    /* split */
    YH, UJ, IK, OL, PSEMICOLON,
    /* Right Side. */
    ENTERBACKSPACE, SEMICOLONENTER, PBACKSPACE, SLASHSHIFT, OP,
    /* Space Area. */
    LGUILCONTROL, SPACERCONTROL,
    /* Quick Paren. */
    DF, FG, HJ, JK,
    /* Mouse. */
    KM, BTNONEBTNTWO, WHEELUPWHEELDOWN,
    /* Arrow Keys. */
    RECONERSTPPLYONE, DOWNUPRIGHT };
/* clang-format on */

/* Combo presses. */
/* Top Row. */
const uint16_t PROGMEM qa_combo[] = {KC_Q, KC_A, COMBO_END};
const uint16_t PROGMEM ws_combo[] = {KC_W, KC_S, COMBO_END};
const uint16_t PROGMEM ed_combo[] = {KC_E, KC_D, COMBO_END};
const uint16_t PROGMEM rf_combo[] = {KC_R, KC_F, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {KC_T, KC_G, COMBO_END};
/* split */
const uint16_t PROGMEM yh_combo[]         = {KC_Y, KC_H, COMBO_END};
const uint16_t PROGMEM uj_combo[]         = {KC_U, KC_J, COMBO_END};
const uint16_t PROGMEM ik_combo[]         = {KC_I, KC_K, COMBO_END};
const uint16_t PROGMEM ol_combo[]         = {KC_O, KC_L, COMBO_END};
const uint16_t PROGMEM psemicolon_combo[] = {KC_P, KC_SCLN, COMBO_END};

/* Right Side. */
const uint16_t PROGMEM enterbackspace_combo[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM semicolonenter_combo[] = {KC_SCLN, KC_ENT, COMBO_END};
const uint16_t PROGMEM pbackspace_combo[]     = {KC_P, KC_BSPC, COMBO_END};
const uint16_t PROGMEM slashshift_combo[]     = {KC_SLSH, KC_RSFT, COMBO_END};
const uint16_t PROGMEM op_combo[]             = {KC_O, KC_P, COMBO_END};

/* Space Area. */
const uint16_t PROGMEM lguilcontrol_combo[]  = {KC_LGUI, KC_LCTL, COMBO_END};
const uint16_t PROGMEM spacercontrol_combo[] = {KC_SPC, KC_RCTL, COMBO_END};

/* Quick Parens. */
const uint16_t PROGMEM df_combo[] = {KC_D, KC_F, COMBO_END};
const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};
const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

/* Mouse. */
const uint16_t PROGMEM km_combo[]               = {KC_K, KC_M, COMBO_END};
const uint16_t PROGMEM btnonebtntwo_combo[]     = {KC_MS_BTN1, KC_MS_BTN2, COMBO_END};
const uint16_t PROGMEM wheelupwheeldown_combo[] = {KC_WH_U, KC_WH_D, COMBO_END};

/* Arrow Keys. */
const uint16_t PROGMEM reconerstpplyone_combo[] = {DM_REC1, DM_RSTP, DM_PLY1, COMBO_END};
const uint16_t PROGMEM downupright_combo[]      = {KC_UP, KC_DOWN, KC_RIGHT, COMBO_END};

/* Combo Results.*/
/* clang-format off */
combo_t key_combos[COMBO_COUNT] = {
    /* Top Row. */
    [QA] = COMBO(qa_combo, KC_1),
    [WS] = COMBO(ws_combo, KC_2),
    [ED] = COMBO(ed_combo, KC_3),
    [RF] = COMBO(rf_combo, KC_4),
    [TG] = COMBO(tg_combo, KC_5),
    /* split */
    [YH] = COMBO(yh_combo, KC_6),
    [UJ] = COMBO(uj_combo, KC_7),
    [IK] = COMBO(ik_combo, KC_8),
    [OL] = COMBO(ol_combo, KC_9),
    [PSEMICOLON] = COMBO(psemicolon_combo, KC_0),
    /* Right Side. */
    [ENTERBACKSPACE] = COMBO(enterbackspace_combo, KC_DEL),
    [SEMICOLONENTER] = COMBO(semicolonenter_combo, KC_QUOTE),
    [PBACKSPACE] = COMBO(pbackspace_combo, KC_MINUS),
    [SLASHSHIFT] = COMBO(slashshift_combo, KC_EQUAL),
    [OP] = COMBO(op_combo, KC_BACKSLASH),
    /* Space Area. */
    [LGUILCONTROL] = COMBO(lguilcontrol_combo, KC_SPACE),
    [SPACERCONTROL] = COMBO(spacercontrol_combo, KC_RALT),
    /* Quick Parens. */
    [DF] = COMBO(df_combo, KC_LEFT_BRACKET),
    [FG] = COMBO(fg_combo, KC_LEFT_PAREN),
    [HJ] = COMBO(hj_combo, KC_RIGHT_PAREN),
    [JK] = COMBO(jk_combo, KC_RIGHT_BRACKET),
    [KM] = COMBO(km_combo, TG(_MOUSE)),
    /* Mouse. */
    [BTNONEBTNTWO] = COMBO(btnonebtntwo_combo, KC_MS_BTN3),
    [WHEELUPWHEELDOWN] = COMBO(wheelupwheeldown_combo, KC_MS_BTN3),
    /* Arrow Keys. */
    [RECONERSTPPLYONE] =COMBO(reconerstpplyone_combo, TG(_ARROWS)),
    [DOWNUPRIGHT] = COMBO(downupright_combo, TG(_ARROWS))
};
/* clang-format on */

/* Decide when to squash combos. */
bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
    /* Simplify combo selection when in _GAMING layer. */
    if (IS_LAYER_ON(_GAMING)) {
        switch (combo_index) {
            case KM: /* No entry to _MOUSE. */
            case DF: /* No quick parens. */
            case FG:
            case HJ:
            case JK:
            case BTNONEBTNTWO: /* No quick KC_MS_BTN3. */
                return false;
        }
    }

    return true;
}

/* Tap Dance declarations. */
enum { TD_ESC_TAB, TD_NUMPAD_QMK };

/* Turn on _NUMPAD layer on first tap, _QMK layer on all others. */
void dance_numpad_qmk_layers(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        // Numpad layer
        layer_on(_NUMPAD);
    } else {
        // QMK layer
        layer_on(_QMK);
    }
}

/* Tap Dance definitions. */
tap_dance_action_t tap_dance_actions[] = {[TD_ESC_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_TAB), [TD_NUMPAD_QMK] = ACTION_TAP_DANCE_FN(dance_numpad_qmk_layers)

};

/* Keymap definitions.
 *
 * !!
 * !! Do not use tap dance on the alpha keys or minus.  Doing so wrecks Caps Word.
 * !!
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* clang-format off */
    [_QWERTY] = LAYOUT_ortho_4x12(
        TD(TD_ESC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T, /*split*/ KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        TD(TD_NUMPAD_QMK), KC_A, KC_S, KC_D, KC_F, KC_G, /*split*/ KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, /*split*/ KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
        CW_TOGG, OSL(_FN), KC_GRV, KC_LALT, KC_LGUI, KC_LCTL, /*split*/ KC_SPC, KC_RCTL, KC_INS, DM_REC1, DM_RSTP, DM_PLY1),

    [_ARROWS] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT),

    [_QMK] = LAYOUT_ortho_4x12(
        KC_SLEP, KC_BRID, KC_BRIU, KC_KB_MUTE, KC_KB_VOLUME_DOWN, KC_KB_VOLUME_UP, /*split*/ _______, _______, _______, _______, _______, _______,
        TG(_QMK), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_GAMING), /*split*/ _______, _______, _______, _______, _______, _______,
        AS_TOGG, XXXXXXX, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, /*split*/ _______, _______, _______, _______, _______, _______,
        DM_PLY1, DM_PLY2 , DM_RSTP, DM_REC1, DM_REC2, XXXXXXX, /*split*/ _______, _______, _______, _______, _______, _______),

    [_NUMPAD] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, /*split*/ XXXXXXX, KC_7, KC_8, KC_9, KC_PMNS, KC_PAST,
        TG(_NUMPAD), _______, _______, _______, _______, _______, /*split*/ XXXXXXX, KC_4, KC_5, KC_6, KC_PPLS, KC_PSLS,
        _______, _______, _______, _______, _______, _______, /*split*/ XXXXXXX, KC_1, KC_2, KC_3, KC_PEQL, XXXXXXX,
        _______, _______, _______, _______, _______, _______, /*split*/ KC_0, KC_0, KC_0, KC_PDOT, KC_PENT, XXXXXXX),

    [_MOUSE] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, /*split*/ XXXXXXX, KC_WH_U, XXXXXXX, KC_WH_D, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, /*split*/ KC_MS_L, KC_MS_U, KC_MS_D, KC_MS_R, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, /*split*/ XXXXXXX, TG(_MOUSE), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        _______, _______, _______, _______, _______, _______, /*split*/ KC_MS_BTN1, KC_MS_BTN2, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

    [_FN] = LAYOUT_ortho_4x12(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, /*split*/ KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, TG(_FN), _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______),

    [_GAMING] = LAYOUT_ortho_4x12(
        KC_ESC, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        KC_TAB, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        TG(_GAMING), _______, _______, KC_RALT, KC_LCTL, KC_SPC, /*split*/ _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, TG(_GAMING_MOUSE)),

    [_GAMING_MOUSE] = LAYOUT_ortho_4x12(
        _______, _______, _______, _______, _______, _______, /*split*/ _______, KC_WH_U, KC_MS_U, KC_WH_D, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, /*split*/ KC_MS_BTN1, KC_MS_BTN2, KC_MS_BTN3, _______, _______, TG(_GAMING_MOUSE))

    // [_EMPTY] = LAYOUT_ortho_4x12(
    //     _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______,
    //     _______, _______, _______, _______, _______, _______, /*split*/ _______, _______, _______, _______, _______, _______
    // )

    /* clang-format on */
};

/* Light layers for keymap layer indication. */
const rgblight_segment_t PROGMEM _QWERTY_LIGHTS[]       = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_WHITE}, /* split */ {6, 6, HSV_WHITE});
const rgblight_segment_t PROGMEM _ARROW_LIGHTS[]        = RGBLIGHT_LAYER_SEGMENTS({7, 2, HSV_CORAL});
const rgblight_segment_t PROGMEM _CAPS_LIGHTS[]         = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_RED}, /* split */ {6, 6, HSV_RED});
const rgblight_segment_t PROGMEM _MOUSE_LIGHTS[]        = RGBLIGHT_LAYER_SEGMENTS({6, 6, HSV_CYAN});
const rgblight_segment_t PROGMEM _NUMPAD_LIGHTS[]       = RGBLIGHT_LAYER_SEGMENTS({6, 6, HSV_MAGENTA});
const rgblight_segment_t PROGMEM _QMK_LIGHTS[]          = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_YELLOW});
const rgblight_segment_t PROGMEM _FN_LIGHTS[]           = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_GREEN}, /* split */ {6, 6, HSV_GREEN});
const rgblight_segment_t PROGMEM _GAMING_LIGHTS[]       = RGBLIGHT_LAYER_SEGMENTS({0, 6, HSV_ORANGE}, /* split */ {6, 6, HSV_ORANGE});
const rgblight_segment_t PROGMEM _GAMING_MOUSE_LIGHTS[] = RGBLIGHT_LAYER_SEGMENTS({6, 6, HSV_CHARTREUSE});

/* RGB layers. */
const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(_QWERTY_LIGHTS, _ARROW_LIGHTS, _CAPS_LIGHTS, _MOUSE_LIGHTS, _NUMPAD_LIGHTS, _QMK_LIGHTS, _FN_LIGHTS, _GAMING_LIGHTS, _GAMING_MOUSE_LIGHTS);

/* Turn on capslock rgblight layer when capslock is on. */
bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(2, led_state.caps_lock);
    return true;
}

/* Turn on capslock rgblight layer when capsword is on. */
void caps_word_set_user(bool active) {
    rgblight_set_layer_state(2, active);
}

/* Stores autoshift state outside of _GAME. */
bool desire_autoshift = true;

/* Act when layer state changes. */
layer_state_t layer_state_set_user(layer_state_t state) {
    /* Turn on rgblight layers when keymap layers turn on. */
    rgblight_set_layer_state(0, true); /* Always apply bottom layer. */
    rgblight_set_layer_state(1, layer_state_cmp(state, _ARROWS));
    /* The next layer is _CAPS_LIGHTS, which isn't tied to a keymap layer. */
    rgblight_set_layer_state(3, layer_state_cmp(state, _MOUSE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(5, layer_state_cmp(state, _QMK));
    rgblight_set_layer_state(6, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(7, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(8, layer_state_cmp(state, _GAMING_MOUSE));

    /* Turn off autoshift in _GAMING. */
    if (layer_state_cmp(state, _GAMING)) autoshift_disable();
    /* Turn on autoshift when we return to base layer.
       (Ideally this would be when we exit _GAME) */
    if ((get_highest_layer(state) == _QWERTY) && desire_autoshift) autoshift_enable();
    return state;
}

/* Setup after the keyboard has been initalized. */
void keyboard_post_init_user(void) {
    /* Enable the LED layers. */
    rgblight_layers = my_rgb_layers;
    /* Default to having autoshift on. */
    autoshift_enable();
}

/* Time before _LAYER deactives after last input. */
#define NUMPAD_LAYER_TIMEOUT 3000 /* milliseconds */
#define FN_LAYER_TIMEOUT 2000
#define QMK_LAYER_TIMEOUT 5000

/* Run when the keyboard scans the matrix.
   Use minimally, as it runs pretty much constantly. */
void matrix_scan_user(void) {
    /* Allow highest layers to time out after going X milliseconds since last input */
    switch (get_highest_layer(layer_state)) {
        case _NUMPAD:
            if (last_input_activity_elapsed() > NUMPAD_LAYER_TIMEOUT) layer_off(_NUMPAD);
            break;
        case _FN:
            if (last_input_activity_elapsed() > FN_LAYER_TIMEOUT) layer_off(_FN);
            break;
        case _QMK:
            if (last_input_activity_elapsed() > QMK_LAYER_TIMEOUT) layer_off(_QMK);
            break;
    }

    /* Clean up when turning _GAMING off. */
    if (IS_LAYER_OFF(_GAMING) && IS_LAYER_ON(_GAMING_MOUSE)) layer_off(_GAMING_MOUSE);
}

/* React to key presses */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* Capture autoshift changes to sanely restore autoshift after dropping out of _GAME. */
    if (keycode == AS_TOGG) {
        desire_autoshift = get_autoshift_state();
    }
    return true;
}