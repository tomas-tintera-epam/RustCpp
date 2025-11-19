// Sample C++ program: simple in-memory task manager
// Requires C++17 or later.

#include "TaskManager.hpp"
#include <iostream>

int main() {
    TaskManager mgr;
    mgr.add("Write proposal", 2);
    mgr.add("Buy groceries", 5);
    mgr.add("Fix bug #123", 1);
    mgr.add("Read book", 8);

    std::cout << "All tasks:\n";
    mgr.list();

    mgr.sortByPriority();
    std::cout << "\nSorted by priority:\n";
    mgr.list();

    mgr.markDone(3); // mark "Fix bug #123" done
    std::cout << "\nAfter marking task 3 done:\n";
    mgr.list();

    mgr.removeCompleted();
    std::cout << "\nAfter removing completed tasks:\n";
    mgr.list();

    return 0;
}