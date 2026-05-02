#include "cw_returns.h"
#include "except.h"
#include "raylib.h"

// keymapping for wsad and mouse movements is already done by raylib in updateCamera function.

void cw_key_mapping(void) {

    if (IsKeyPressed(KEY_F2)) {
        if (IsCursorHidden()) {
            ShowCursor();
        } else if (!IsCursorHidden()) {
            HideCursor();
        }
    }
}
