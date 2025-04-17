#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>

struct Task {
    std::string name;
    char state = 'P';  // 'P' for Pending, 'D' for Done
};

class TaskDB {
private:
    std::vector<Task> PendingTasks;
    std::vector<Task> DoneTasks;

public:
    TaskDB();
    void SaveTasks();
    void LoadTasks();

    // Getters
    const std::vector<Task>& getPendingTasks() const { return PendingTasks; }
    const std::vector<Task>& getDoneTasks() const { return DoneTasks; }

    // Task modification methods
    void addPendingTask(const Task& task);
    void markTaskDone(size_t index);
    void deletePendingTask(size_t index);
};

class Options {
public:
    void AddTask(TaskDB& taskDB);
    void ViewPending(const TaskDB& taskDB) const;
    void MarkDone(TaskDB& taskDB);
    void ViewDone(const TaskDB& taskDB) const;
    void DeleteTask(TaskDB& taskDB);
};

int DisplayMenu();

#endif