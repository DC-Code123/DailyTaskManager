#include "../include/Task.h"
#include <iostream>
using namespace std;


// ====================
// TaskDB Implementation
// ====================

TaskDB::TaskDB() {
  cout << "Database initialized.\n";
}


void TaskDB::SaveTasks() {
  ofstream outFile("tasks.txt");
  if (!outFile) {
    throw runtime_error("Failed to save tasks.");
  }

  outFile << "Pending\n";
  for (const auto& task : PendingTasks) {
    outFile << task.name << '\n';
  }

  outFile << "Done\n";
  for (const auto& task : DoneTasks) {
    outFile << task.name << '\n';
  }
  
  cout << "Tasks saved.\n";
}


void TaskDB::LoadTasks() {
  ifstream inFile("tasks.txt");
  if (!inFile) {
    cout << "No saved tasks found.\n";
    return;
  }

  string line;
  bool isPending = true;

  while (getline(inFile, line)) {
    if (line == "Pending") {
      isPending = true;
    } 
    else if (line == "Done") {
      isPending = false;
    } 
    else {
      Task task;
      task.name = line;
      task.state = isPending ? 'P' : 'D';
      
      if (isPending) {
        PendingTasks.push_back(task);
      } 
      else {
        DoneTasks.push_back(task);
      }
    }
  }
  
  cout << "Tasks loaded.\n";
}


void TaskDB::addPendingTask(const Task& task) {
  PendingTasks.push_back(task);
}


void TaskDB::markTaskDone(size_t index) {
  if (index >= PendingTasks.size()) {
    throw out_of_range("Invalid task index.");
  }
  
  Task task = PendingTasks[index];
  task.state = 'D';
  DoneTasks.push_back(task);
  PendingTasks.erase(PendingTasks.begin() + index);
}


void TaskDB::deletePendingTask(size_t index) {
  if (index >= PendingTasks.size()) {
    throw out_of_range("Invalid task index.");
  }
  PendingTasks.erase(PendingTasks.begin() + index);
}


// =====================
// Options Implementation
// =====================

void Options::AddTask(TaskDB& taskDB) {
  Task newTask;
  
  cout << "Enter task name: ";
  cin.ignore();
  getline(cin, newTask.name);
  
  newTask.state = 'P';
  taskDB.addPendingTask(newTask);
  
  cout << "Task added.\n";
}


void Options::ViewPending(const TaskDB& taskDB) const {
  const auto& tasks = taskDB.getPendingTasks();
  
  if (tasks.empty()) {
    cout << "No pending tasks.\n";
    return;
  }
  
  cout << "Pending Tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    cout << i + 1 << ". " << tasks[i].name 
              << " [State: " << tasks[i].state << "]\n";
  }
}


void Options::MarkDone(TaskDB& taskDB) {
  ViewPending(taskDB);
  
  cout << "Enter task number to mark as done: ";
  size_t index;
  cin >> index;

  if (cin.fail() || index < 1 || index > taskDB.getPendingTasks().size()) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input.\n";
    return;
  }
  
  taskDB.markTaskDone(index - 1);
}


// ====================
// Menu Implementation
// ====================

int DisplayMenu() {
  int choice;
  
  cout << "\nMenu:\n"
            << "1. Add Task\n"
            << "2. View Pending\n"
            << "3. Mark Done\n"
            << "4. Exit\n"
            << "Choice: ";
            
  cin >> choice;
  return choice;
}