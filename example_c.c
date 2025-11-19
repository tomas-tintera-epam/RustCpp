/* example_c.c - ANSI C89 example using the C wrapper */
#include "task_c.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    TaskManagerC* mgr = taskmgr_create();
    if (!mgr) return 1;

    /* mirror TaskManager.cpp main */
    taskmgr_add(mgr, "Write proposal", 2);
    taskmgr_add(mgr, "Buy groceries", 5);
    taskmgr_add(mgr, "Fix bug #123", 1);
    taskmgr_add(mgr, "Read book", 8);

    printf("All tasks:\n");
    char* s = taskmgr_list(mgr);
    if (s) { printf("%s", s); free(s); }

    taskmgr_sort_by_priority(mgr);
    printf("\nSorted by priority:\n");
    s = taskmgr_list(mgr);
    if (s) { printf("%s", s); free(s); }

    taskmgr_mark_done(mgr, 3); /* mark "Fix bug #123" done */
    printf("\nAfter marking task 3 done:\n");
    s = taskmgr_list(mgr);
    if (s) { printf("%s", s); free(s); }

    taskmgr_remove_completed(mgr);
    printf("\nAfter removing completed tasks:\n");
    s = taskmgr_list(mgr);
    if (s) { printf("%s", s); free(s); }

    taskmgr_destroy(mgr);
    return 0;
}
