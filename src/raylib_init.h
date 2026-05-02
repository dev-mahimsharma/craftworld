#ifndef RAYLIB_INIT_H
#define RAYLIB_INIT_H

#ifdef __CPLUSPLUS
extern "c" {
#endif

#define CREATE_WIN() (raylib_create_win())
#define RESIZE_WIN() (raylib_win_resize_screen())
#define CLOSE_WIN() (CloseWindow())

extern CW_Return raylib_create_win(void);
extern CW_Return raylib_win_resize_screen(void);

#ifdef __CPLUSPLUS
}
#endif


#endif
