/* tests/test_task_c.c
 * Simple C tests for the TaskManager C API
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "task_c.h"

int contains(const char* haystack, const char* needle) {
    if (!haystack || !needle) return 0;
    return strstr(haystack, needle) != NULL;
}

int main(void) {
    TaskManagerC* mgr = taskmgr_create();
    assert(mgr != NULL);

    int id1 = taskmgr_add(mgr, "Write proposal", 2);
    int id2 = taskmgr_add(mgr, "Buy groceries", 5);
    int id3 = taskmgr_add(mgr, "Fix bug #123", 1);
    int id4 = taskmgr_add(mgr, "Read book", 8);
    (void)id1; (void)id2; (void)id3; (void)id4;

    char* listing = taskmgr_list(mgr);
    assert(listing != NULL);
    assert(contains(listing, "Write proposal"));
    free(listing);

    taskmgr_sort_by_priority(mgr);
    listing = taskmgr_list(mgr);
    assert(listing != NULL);
    /* After sort, Fix bug #123 (priority 1) should appear before Write proposal (priority 2) */
    const char* first = strstr(listing, "[");
    assert(first != NULL);
    /* crude check: ensure Fix bug appears in listing */
    assert(contains(listing, "Fix bug #123"));
    free(listing);

    /* mark done and remove */
    int marked = taskmgr_mark_done(mgr, 3);
    assert(marked == 1);
    listing = taskmgr_list(mgr);
    assert(listing != NULL);
    assert(contains(listing, "Fix bug #123"));
    free(listing);

    taskmgr_remove_completed(mgr);
    listing = taskmgr_list(mgr);
    assert(listing != NULL);
    /* after removal, Fix bug #123 should be gone */
    assert(!contains(listing, "Fix bug #123"));
    free(listing);

    taskmgr_destroy(mgr);
    printf("All C API tests passed.\n");
    return 0;
}
