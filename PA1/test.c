#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main() {
    write(1, "a", 1);
    write(1, " ", 1);
    write(1, "\b", 1);
    write(1, "", 0);
}