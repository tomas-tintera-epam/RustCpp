/* tests/example_consumer.c
 * Small C program that uses the public C API and links against the
 * produced static library to verify external C consumers can link.
 */
#include <stdio.h>
#include <stdlib.h>
#include "task_c.h"

int main(void) {
    TaskManagerC* mgr = taskmgr_create();
    if (!mgr) return 2;

    taskmgr_add(mgr, "consumer task", 3);
    char* s = taskmgr_list(mgr);
    if (!s) { taskmgr_destroy(mgr); return 3; }
    puts(s);
    free(s);

    taskmgr_destroy(mgr);
    return 0;
}
