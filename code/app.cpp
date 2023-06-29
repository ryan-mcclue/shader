// SPDX-License-Identifier: zlib-acknowledgement

#include "base-inc.h"

// TODO(Ryan): UI elements: https://mattiasgustavsson.itch.io/yarnspin/devlog/544215/coding-an-ad-hoc-ui   

// TODO(Ryan): Use "", as still implementation defined, however allows for easier overriding if required
// So, only use for stdlib?
// TODO(Ryan): Link ctags for library
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <GL/gl.h>

#include "app.h"

GLOBAL ThreadContext global_tctx;

EXPORT void
app(AppState *state, Renderer *renderer, Input *input, MemArena *perm_arena)
{
  if (!state->is_initialised)
  {
    global_debugger_present = state->debugger_present;

    state->is_initialised = true;

    // TODO(Ryan): More platform agnostic if these are passed in as 2 frame arenas
    global_tctx = thread_context_create();
    thread_context_set(&global_tctx);
  } 
}
