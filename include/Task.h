#ifndef TASK_H
#define TASK_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

// Structure to define a task
struct Task {
  string name;          // Task description
  string state;         // "Pending" or "Done"
  bool finishedness;    // true if done, false otherwise
};

// Function declarations
void SaveTasks(const vector<Task>& pendingTasks, const vector<Task>& doneTasks);
void LoadTasks(vector<Task>& pendingTasks, vector<Task>& doneTasks);
void AddTask(vector<Task>& pendingTasks);
void PrintTasks(const vector<Task>& tasks, const string& title);
void ViewTask(const vector<Task>& pendingTasks);
void MarkDone(vector<Task>& pendingTasks, vector<Task>& doneTasks);
void ViewDone(const vector<Task>& doneTasks);
void DeleteTask(vector<Task>& pendingTasks, vector<Task>& doneTasks);
int DisplayMenu();

#endif // TASK_H