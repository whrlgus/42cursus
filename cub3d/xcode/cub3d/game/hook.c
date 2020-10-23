#include "hook.h"
#include "type.h"

void exit_hook()
{
	exit(0);
}

int key_pressed(int key, t_control* control){
	if (key == 53)
		exit(0);
	control->keyboard[key] = 1;
	return (0);
}

int key_released(int key, t_control* control){
	control->keyboard[key] = 0;
	return (0);
}

int motion_notified(int x, int y, t_control* control) {
	control->new_mouse_point.x = x;
	return (0);
}
