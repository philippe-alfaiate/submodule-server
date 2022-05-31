#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int myOpen(const char *name)
{
    int fd;
    const char *pipe_file = "/tmp/fifofile";

    if ((fd = open(pipe_file, O_RDONLY)) < 0)
    {
        fprintf(stderr, "%s: Failed to open FIFO %s\n", name, pipe_file);
        return 1;
    }

    return fd;
}

int restart(const char *name, int *fd)
{
    close(*fd);
    *fd = myOpen(name);
    return *fd;
}


int main(int argc, char **argv)
{

    int fd = 0;
    int nread = 0;
    char buf[100];

    fd = myOpen(argv[0]);

    while (1)
    {
        memset(buf, 0, 100);
        nread = read(fd, buf, 100 - 1);
        if (nread > 0)
        {
            write(1, buf, nread);
        } else {
            write(1, "\n", 1);
            restart(argv[0], &fd);
        }
    }

    return 0;
}