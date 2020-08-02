#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define FIB_DEV "/dev/fibonacci"
#define BUF_SIZE 128

int main()
{
    char buf[BUF_SIZE];
    char write_buf[] = "testing writing";
    int offset = 184; /* TODO: try test something bigger than the limit */

    int fd = open(FIB_DEV, O_RDWR);
    if (fd < 0) {
        perror("Failed to open character device");
        exit(1);
    }

    struct timespec tt1, tt2;
    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        clock_gettime(CLOCK_REALTIME, &tt1);
        read(fd, buf, BUF_SIZE);
        clock_gettime(CLOCK_REALTIME, &tt2);
        printf("%d, %ld, %s\n", i, tt2.tv_nsec - tt1.tv_nsec, buf);
        /*printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%s.\n",
               i, buf);*/
    }


    for (int i = 0; i <= offset; i++) {
        lseek(fd, i, SEEK_SET);
        read(fd, buf, BUF_SIZE);
        printf("%d, %ld, %s\n", i, write(fd, write_buf, strlen(write_buf)),
               buf);
    }

    close(fd);
    return 0;
}
