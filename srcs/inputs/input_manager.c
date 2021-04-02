#include "header.h"
#include "ANSI-color-codes.h"

int     keyboard_input(int keycode, void *param)
{
    t_scene *scene;

    scene = (t_scene*)param;
    printf("key pressed : %d\n", keycode);
    if(keycode == 53)
        exit_func(NULL);
    else if(keycode == 8)
        camera_wheel(scene);
    return keycode;
}
int     mouse_input(int button, int x, int y, void *param)
{
    t_scene *scene;

    scene = (t_scene*)param;
    x = x + 1 - 1;
    y = y + 1 - 1;
    printf("pressed mouse button : %d at %d,%d\n", button, x, y);
    //if(button == 1)
    //else if (button == 3)
    //{
    //}
    return 1;
}
int     idle(void *param)
{
    t_scene *scene;

    scene = (t_scene*)param;

    return 1;
}

void    terminal_info()
{
    system("clear");
    printf(BCYN"CAMERA MOVEMENT :\n\tW - Move Forward\n\t");
    printf("S - Move Backward\n\tA - Move Left\n\tD - Move Right\n");
    printf("CAMERA ROTATION\n\t◀- - Rotate Left\n\t");
    printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
    printf("⬆ - Rotate Up\n\n\tC - Cycle cameras\n\n");
    printf(BBLU"Press ESC or click the close button on the window to exit\n"reset);
}