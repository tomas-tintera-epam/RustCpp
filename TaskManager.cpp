// TaskManager method implementations

#include "TaskManager.hpp"

int TaskManager::add(const std::string& title, int priority) {
    tasks.push_back({nextId, title, priority, false});
    return nextId++;
}

bool TaskManager::markDone(int id) {
    for (auto &t : tasks) {
        if (t.id == id) { 
            t.done = true; 
            return true; 
        }
    }
    return false;
}

void TaskManager::removeCompleted() {
    tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                               [](const Task& t){ return t.done; }),
                tasks.end());
}

void TaskManager::sortByPriority() {
    std::sort(tasks.begin(), tasks.end(),
              [](const Task& a, const Task& b) {
                  if (a.priority != b.priority) return a.priority < b.priority;
                  return a.id < b.id;
              });
}

void TaskManager::list() const {
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

std::string TaskManager::listAsString() const {
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
