#include "../include/Task.h"
#include <iostream>

// --- TaskDB Methods ---
TaskDB::TaskDB() {
    std::cout << "Database initialized.\n";
}

void TaskDB::SaveTasks() {
    std::ofstream outFile("tasks.txt");
    if (!outFile) {
        throw std::runtime_error("Failed to save tasks.");
    }

    outFile << "Pending\n";
    for (const auto& task : PendingTasks) {
        outFile << task.name << '\n';
    }

    outFile << "Done\n";
    for (const auto& task : DoneTasks) {
        outFile << task.name << '\n';
    }
    std::cout << "Tasks saved.\n";
}

void TaskDB::LoadTasks() {
    std::ifstream inFile("tasks.txt");
    if (!inFile) {
        std::cout << "No saved tasks found.\n";
        return;
    }

    std::string line;
    bool isPending = true;

    while (std::getline(inFile, line)) {
        if (line == "Pending") {
            isPending = true;
        } else if (line == "Done") {
            isPending = false;
        } else {
            Task task;
            task.name = line;
            task.state = isPending ? 'P' : 'D';
            
            if (isPending) {
                PendingTasks.push_back(task);
            } else {
                DoneTasks.push_back(task);
            }
        }
    }
    std::cout << "Tasks loaded.\n";
}

void TaskDB::addPendingTask(const Task& task) {
    PendingTasks.push_back(task);
}

void TaskDB::markTaskDone(size_t index) {
    if (index >= PendingTasks.size()) {
        throw std::out_of_range("Invalid task index.");
    }
    Task task = PendingTasks[index];
    task.state = 'D';  // Only update state (no finishedness)
    DoneTasks.push_back(task);
    PendingTasks.erase(PendingTasks.begin() + index);
}

void TaskDB::deletePendingTask(size_t index) {
    if (index >= PendingTasks.size()) {
        throw std::out_of_range("Invalid task index.");
    }
    PendingTasks.erase(PendingTasks.begin() + index);
}

// --- Options Methods ---
void Options::AddTask(TaskDB& taskDB) {
    Task newTask;
    std::cout << "Enter task name: ";
    std::cin.ignore();
    std::getline(std::cin, newTask.name);
    newTask.state = 'P';
    taskDB.addPendingTask(newTask);
    std::cout << "Task added.\n";
}

void Options::ViewPending(const TaskDB& taskDB) const {
    const auto& tasks = taskDB.getPendingTasks();
    if (tasks.empty()) {
        std::cout << "No pending tasks.\n";
        return;
    }
    std::cout << "Pending Tasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        std::cout << i + 1 << ". " << tasks[i].name 
                  << " [State: " << tasks[i].state << "]\n";
    }
}

void Options::MarkDone(TaskDB& taskDB) {
    ViewPending(taskDB);
    std::cout << "Enter task number to mark as done: ";
    size_t index;
    std::cin >> index;

    if (std::cin.fail() || index < 1 || index > taskDB.getPendingTasks().size()) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input.\n";
        return;
    }
    taskDB.markTaskDone(index - 1);
}

// (Other Options methods updated similarly...)

int DisplayMenu() {
    int choice;
    std::cout << "\nMenu:\n"
              << "1. Add Task\n"
              << "2. View Pending\n"
              << "3. Mark Done\n"
              << "4. Exit\n"
              << "Choice: ";
    std::cin >> choice;
    return choice;
}