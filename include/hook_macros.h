#ifndef MLX_HOOK_H
#define MLX_HOOK_H

#define KeyPressMask 1
#define KeyPress 2
#define DestroyNotify 17
#ifdef __linux__
#define XK_Escape 0xff1b
#else
#define XK_Escape 53
#endif

#endif
