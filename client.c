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

    // output file for easily use
    FILE *f = fopen("out.txt", "w");
    if (!f) {
        perror("Failed to open out.txt");
        exit(2);
    }

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

        long utime = tt2.tv_nsec - tt1.tv_nsec;
        long ktime = write(fd, write_buf, strlen(write_buf));
        fprintf(f, "%d, %ld, %ld, %ld\n", i, ktime, utime, utime - ktime);
        printf("Reading from " FIB_DEV
               " at offset %d, returned the sequence "
               "%s.\n",
               i, buf);
    }

    close(fd);
    fclose(f);
    return 0;
}
