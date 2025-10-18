#include <stdio.h>
#include <sys/utsname.h>
#include "utils.h"

void print_arch_info() {
    struct utsname sys_info;
    if (uname(&sys_info) == 0) {
        printf("System: %s\n", sys_info.sysname);
        printf("Architecture: %s\n", sys_info.machine);
        printf("Compiled with c.exe cross-architecture support\n");
    }
}
