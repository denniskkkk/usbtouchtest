#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/input.h>

#define EVENT_DEVICE    "/dev/input/event4"
#define EVENT_TYPE      EV_ABS
#define EVENT_CODE_X    ABS_X
#define EVENT_CODE_Y    ABS_Y

/* TODO: Close fd on SIGINT (Ctrl-C), if it's open */

int main(int argc, char *argv[])
{
    struct input_event ev;
    int fd;
    char name[256] = "Unknown";
    char devicename[256];

    if ((getuid ()) != 0) {
        fprintf(stderr, "You are not root! This may not work...\n");
        return EXIT_SUCCESS;
    }

    
    /* Open Device */
    sprintf (devicename, "/dev/input/event%s", argv[1]);
    printf ("get event name = %s\n", devicename);

    fd = open(devicename, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "%s is not a vaild device\n", EVENT_DEVICE);
        return EXIT_FAILURE;
    }

    /* Print Device Name */
    ioctl(fd, EVIOCGNAME(sizeof(name)), name);
    printf("Reading from:\n");
    printf("device name = %s\n", name);

}
