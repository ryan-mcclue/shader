// SPDX-License-Identifier: zlib-acknowledgement
#if !defined(APP_H)
#define APP_H

IGNORE_WARNING_PADDED()
typedef struct AppState AppState;
struct AppState
{
  b32 debugger_present;
  b32 is_initialised;
  f32 delta;
  u64 ms;
  u32 rand_seed; // perhaps rename effects_series?
};
IGNORE_WARNING_POP()

IGNORE_WARNING_PADDED()
typedef struct Renderer Renderer;
struct Renderer
{
  SDL_Renderer *renderer;
  u32 window_width, window_height;
  u32 render_width, render_height;
};
IGNORE_WARNING_POP()

IGNORE_WARNING_PADDED()
typedef struct Input Input;
struct Input
{
  b32 move_left, move_right, move_up, bullet_fired;
  f32 mouse_x, mouse_y; 
  b32 mouse_clicked;
  b32 mouse_pressed;
  b32 mouse_held;
};
IGNORE_WARNING_POP()

typedef void (*app_func)(AppState *state, Renderer *renderer, Input *input, MemArena *perm_arena);

EXPORT void
app(AppState *state, Renderer *renderer, Input *input, MemArena *perm_arena);

#endif
