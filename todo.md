<!--
File: todo.md
Brief: Project cleanup and architecture checklist for Craftworld.

Details:
  This file records follow-up work that should happen after the current code is
  stable. It is written in normal language so both programmers and beginners can
  understand what still needs attention.

Copyright 2026 Craftworld contributors

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

SPDX-License-Identifier: Apache-2.0
-->

# Craftworld TODO

This checklist tracks project-level cleanup and architecture tasks. Each item is
written so it can later become a small, focused code change.

1. Fix enable/disable key mappings.

2. Make sure the cursor remains captured inside the window when `DisableCursor()`
   is active.

3. Improve the naming convention of `raylib_init.c` and `raylib_init.h` so the
   module name reflects its full responsibility.

4. Make the code more modular, with special attention to ownership and memory
   management.

5. Move `raylib_win_resize_screen` into `key_mapping.c` if window shortcuts are
   going to be owned by the input-mapping layer.
