// task_c.h - C wrapper API for Task and TaskManager
#ifndef TASK_C_H
#define TASK_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct TaskC TaskC;
typedef struct TaskManagerC TaskManagerC;

/* Task APIs */
TaskC* task_create(const char* title, int priority);
void task_destroy(TaskC* t);

int task_get_id(const TaskC* t);
char* task_get_title(const TaskC* t); /* returns malloc'd string, caller frees */
int task_get_priority(const TaskC* t);
int task_is_done(const TaskC* t);

void task_set_title(TaskC* t, const char* title);
void task_set_priority(TaskC* t, int priority);
void task_set_done(TaskC* t, int done);

/* TaskManager APIs */
TaskManagerC* taskmgr_create(void);
void taskmgr_destroy(TaskManagerC* m);

int taskmgr_add(TaskManagerC* m, const char* title, int priority);
int taskmgr_mark_done(TaskManagerC* m, int id);
void taskmgr_remove_completed(TaskManagerC* m);
void taskmgr_sort_by_priority(TaskManagerC* m);

char* taskmgr_list(TaskManagerC* m); /* returns malloc'd string, caller frees */

#ifdef __cplusplus
}
#endif

#endif /* TASK_C_H */
