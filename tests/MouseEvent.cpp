#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <linux/input.h>
#include <fcntl.h>

#include <thread>
#include <chrono>

#define MOUSEFILE "/dev/input/event4"

int main()
{
    int fd;
    struct input_event ie;

    if((fd = open(MOUSEFILE, O_RDONLY)) == -1) {
        perror("opening device");
        exit(EXIT_FAILURE);
    }

    while(read(fd, &ie, sizeof(struct input_event))) {
        printf("time %ld.%06ld\ttype %d\tcode %d\tvalue %d\n",
               ie.time.tv_sec, ie.time.tv_usec, ie.type, ie.code, ie.value);
        std::this_thread::sleep_for(std::chrono::milliseconds(2));

}
    return 0;
}
