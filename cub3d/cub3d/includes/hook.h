//
//  hook.h
//  cub3d
//
//  Created by 조기현 on 2020/10/23.
//

#ifndef hook_h
#define hook_h

#include <stdlib.h>
#include "type.h"
int exit_hook(int val);
int key_pressed(int key, t_control* control);
int key_released(int key, t_control* control);
int motion_notified(int x, int y, t_control* control);
#endif /* hook_h */
