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
    char    *line;

    scene = (t_scene*)param;
    x = x + 1 - 1;
    y = y + 1 - 1;
    //printf("pressed mouse button : %d at %d,%d\n", button, x, y);
    if(button == 1)
    {
        // intersezione
        get_next_line(0, &line);
    }

    // printi info su oggetto selezionato e istruzioni per interagirci
    return 1;
}
int     terminal_input(void *param)
{
    t_scene *scene;
    char    *temp="A.";
    char    *line;

    scene = (t_scene*)param;
    usleep(100000);
    if(get_next_line(0, &line) == 1)
    {
        //printf("%s", line);
        write(1, temp, 2);
	    mlx_loop_hook(scene->mlx, NULL, scene);
    }
    // controllo oggetto selezionato
    // gnl legge input da terminale e lo usa in base all'oggetto selezionato
    return 1;
}

void    terminal_info()
{
    system("clear");
    printf(BCYN"CAMERA MOVEMENT :\n\tW - Move Up\n\t");
    printf("S - Move Down\n\tA - Move Left\n\tD - Move Right\n\t");
    printf("⇞(Pg Up) - Move Forwards\n\t⇟(Pg Down) - Move Backwards\n");
    printf("CAMERA ROTATION\n\t◀- - Rotate Left\n\t");
    printf("-▶ - Rotate Right\n\t⬇ - Rotate down\n\t");
    printf("⬆ - Rotate Up\n\n\tC - Cycle cameras\n\n");
    printf(BBLU"Press ESC or click the close button on the window to exit\n"reset);
    printf("Enter any commands through the terminal ...\n");
}