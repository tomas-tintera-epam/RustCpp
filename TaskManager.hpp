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
    int add(const std::string& title, int priority = 5) {
        tasks.push_back({nextId, title, priority, false});
        return nextId++;
    }

    bool markDone(int id) {
        for (auto &t : tasks) {
            if (t.id == id) { t.done = true; return true; }
        }
        return false;
    }

    void removeCompleted() {
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                                   [](const Task& t){ return t.done; }),
                    tasks.end());
    }

    void sortByPriority() {
        std::sort(tasks.begin(), tasks.end(),
                  [](const Task& a, const Task& b) {
                      if (a.priority != b.priority) return a.priority < b.priority;
                      return a.id < b.id;
                  });
    }

    void list() const {
        if (tasks.empty()) {
            std::cout << "No tasks.\n";
            return;
        }
        for (const auto& t : tasks) {
            std::cout << "[" << t.id << "] "
                      << (t.done ? "[x] " : "[ ] ")
                      << "P" << t.priority << " "
                      << t.title << '\n';
        }
    }

    // Provide a textual listing used by C wrapper
    std::string listAsString() const {
        std::ostringstream os;
        if (tasks.empty()) {
            os << "No tasks.\n";
            return os.str();
        }
        for (const auto& t : tasks) {
            os << "[" << t.id << "] "
               << (t.done ? "[x] " : "[ ] ")
               << "P" << t.priority << " "
               << t.title << '\n';
        }
        return os.str();
    }
};
