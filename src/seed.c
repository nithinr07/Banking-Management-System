#include "database.h"
#include "constants.h"
#include <sys/types.h>          /* See NOTES */
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    mkdir(BASE_PATH, 0744);
    int fd1 = open(NORMALUSER_DB_PATH, O_RDWR | O_CREAT, 0744);
    normalUser u1 = {
        .userID = 1,
        .name = "Nithin",
        .password = "1234",
        .account_no = 1000,
        .balance = 1000.0,
        .status = "ACTIVE"
    };
    write(fd1, &u1, sizeof(u1));
    close(fd1);

    int fd2 = open(JOINTUSER_DB_PATH, O_RDWR | O_CREAT, 0744);
    jointUser u2 = {
        .userID = 1,
        .name1 = "ABCD",
        .name2 = "Raj",
        .password = "1234",
        .account_no = 2000,
        .balance = 1000.0,
        .status = "ACTIVE"
    };
    write(fd2, &u2, sizeof(u2));
    close(fd2);

    int fd3 = open(ADMIN_DB_PATH, O_RDWR | O_CREAT, 0744);
    admin u3 = {
        .userID = 1,
        .username = "admin",
        .password = "1234"
    };
    write(fd3, &u3, sizeof(u3));
    close(fd3);
    return 0;
}