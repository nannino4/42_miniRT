#include "header.h"
#include "ANSI-color-codes.h"

int     keyboard_input(int keycode, void *param)
{
    void *temp;

    temp = param;
    printf("key pressed : %d\n", keycode);
    if(keycode == 53)
    {
        printf("EXITING\n");
        exit(0);
    }
    return keycode;
}
int     mouse_input(int button, int x, int y, void *param)
{
    t_scene *scene;

    scene = (t_scene*)param;
    x = x + 1 - 1;
    y = y + 1 - 1;
    printf("pressed mouse button : %d at %d,%d\n", button, x, y);
    if(button == 1)
    {
        if(scene->cam->next != NULL)
        {
            printf("Switching Camera\n");
            scene->cam = scene->cam->next;
            create_img(scene);
        }
        else
        {
            printf("Reached last camera. Rewinding...\n");
            while(scene->cam->prev != NULL)
                scene->cam = scene->cam->prev;
            create_img(scene);
        }
    }
    //else if (button == 3)
    //{
    //}
    else
    {
        printf("EXITING\n");
        exit(0);
    }
    return 1;
}
int     idle(void *param)
{
    t_scene *scene;

    scene = (t_scene*)param;

    if(scene->win == NULL)
        printf("Window closed\n");
    return 1;
}

void    terminal_info()
{
    system("clear");
    printf(BCYN"CAMERA MOVEMENT :\n\tW - Move Forward\n\t");
    printf("S - Move Backward\n\tA - Move Left\n\tD - Move Right\n");
    printf("CAMERA ROTATION\n\t◀- - Rotate Left\n\t");
    printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
    printf("⬆ - Rotate Up\n\n"BBLU"Press ESC or click the close button on the window to exit\n"reset);
}