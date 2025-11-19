// task_c.cpp - C ABI wrapper around C++ Task/TaskManager
#include "task_c.h"
#include "TaskManager.hpp"

#include <cstring>
#include <cstdlib>

struct TaskC { Task* t; };
struct TaskManagerC { TaskManager* m; };

extern "C" {

TaskC* task_create(const char* title, int priority) {
    if (!title) return nullptr;
    TaskC* tc = (TaskC*)std::malloc(sizeof(TaskC));
    if (!tc) return nullptr;
    tc->t = new Task{0, std::string(title), priority, false};
    return tc;
}

void task_destroy(TaskC* t) {
    if (!t) return;
    delete t->t;
    std::free(t);
}

int task_get_id(const TaskC* t) {
    return t && t->t ? t->t->id : -1;
}

char* task_get_title(const TaskC* t) {
    if (!t || !t->t) return nullptr;
    const std::string& s = t->t->title;
    char* out = (char*)std::malloc(s.size() + 1);
    if (!out) return nullptr;
    std::memcpy(out, s.c_str(), s.size() + 1);
    return out;
}

int task_get_priority(const TaskC* t) {
    return t && t->t ? t->t->priority : 0;
}

int task_is_done(const TaskC* t) {
    return t && t->t && t->t->done ? 1 : 0;
}

void task_set_title(TaskC* t, const char* title) {
    if (!t || !t->t || !title) return;
    t->t->title = std::string(title);
}

void task_set_priority(TaskC* t, int priority) {
    if (!t || !t->t) return;
    t->t->priority = priority;
}

void task_set_done(TaskC* t, int done) {
    if (!t || !t->t) return;
    t->t->done = (done != 0);
}

/* TaskManager wrappers */
TaskManagerC* taskmgr_create(void) {
    TaskManagerC* mc = (TaskManagerC*)std::malloc(sizeof(TaskManagerC));
    if (!mc) return nullptr;
    mc->m = new TaskManager();
    return mc;
}

void taskmgr_destroy(TaskManagerC* m) {
    if (!m) return;
    delete m->m;
    std::free(m);
}

int taskmgr_add(TaskManagerC* m, const char* title, int priority) {
    if (!m || !m->m || !title) return -1;
    return m->m->add(std::string(title), priority);
}

int taskmgr_mark_done(TaskManagerC* m, int id) {
    if (!m || !m->m) return 0;
    return m->m->markDone(id) ? 1 : 0;
}

void taskmgr_remove_completed(TaskManagerC* m) {
    if (!m || !m->m) return;
    m->m->removeCompleted();
}

void taskmgr_sort_by_priority(TaskManagerC* m) {
    if (!m || !m->m) return;
    m->m->sortByPriority();
}

char* taskmgr_list(TaskManagerC* m) {
    if (!m || !m->m) return nullptr;
    std::string s = m->m->listAsString();
    char* out = (char*)std::malloc(s.size() + 1);
    if (!out) return nullptr;
    std::memcpy(out, s.c_str(), s.size() + 1);
    return out;
}

} // extern "C"
