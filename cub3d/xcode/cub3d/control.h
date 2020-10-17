#ifndef control_h
# define control_h

#include "type.h"

int key_pressed(int key, t_control* control);
int key_released(int key, t_control* control);
int motion_notified(int x, int y, t_control* control);
void calc_movement(t_player *p, t_control* control);

#endif
