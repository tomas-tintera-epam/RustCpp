// TaskManager.hpp
// Header containing Task and TaskManager (small, header-only)
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

struct Task {
    int id;
    std::string title;
    int priority; // lower = higher priority
    bool done = false;
};

class TaskManager {
    std::vector<Task> tasks;
    int nextId = 1;
public:
    int add(const std::string& title, int priority = 5);
    bool markDone(int id);
    void removeCompleted();
    void sortByPriority();
    void list() const;
    std::string listAsString() const;
};
