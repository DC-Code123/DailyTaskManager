include "../include/Task.h"
#include <iostream>
using namespace std;


// ====================
// TaskDB Implementation
// ====================

TaskDB::TaskDB() {
  cout << "Database initialized.\n";
}

void TaskDB::SaveTasks() {
  ofstream outFile("Data.txt");
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

  cout<<"\nTask saving";
  cout<<"\n...\n...\n...\n";
  cout<<"Task saved!";
}

void TaskDB::LoadTasks() {
  ifstream inFile("Data.txt");
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

  cout << "Task loading...."
       << "\n...\n...\n...\n";
  cout << "Tasks loaded.\n";
  cout << "------------------------------------------------\n";
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
  if (index > PendingTasks.size()||index<0) {
    throw out_of_range("Invalid task index.");
  }
  PendingTasks.erase(PendingTasks.begin() + index);
}

void TaskDB::deleteDoneTask(size_t index) {
  if (index > DoneTasks.size()||index<0) {
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

  cout << "Task adding"
       <<"\n...\n...\n...\n";
  cout << "Task added.\n";
  cout << "------------------------------------------------\n";
}

void Options::ViewPending(const TaskDB& taskDB,Options& options) const {
  const auto& tasks = taskDB.getPendingTasks();

  if (tasks.empty()) {
    cout << "No pending tasks.\n";
    options.empty = true;
  }

  cout << "Pending Tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    cout << i + 1 << ". " << tasks[i].name
              << " [State: " << tasks[i].state << "]\n";
  }
  cout << "------------------------------------------------\n";
  options.empty = false;
}

void Options::MarkDone(TaskDB& taskDB,Options& options){
  options.ViewPending(taskDB,options);

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

void Options::ViewDone(const TaskDB& taskDB,Options& options) const {
  const auto& tasks = taskDB.getDoneTasks();

  if (tasks.empty()) {
    cout << "No Done tasks.\n";
    options.empty = true;
  }

  cout << "Done Tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    cout << i + 1 << ". " << tasks[i].name
              << " [State: " << tasks[i].state << "]\n";
  }
  cout << "------------------------------------------------\n";
  options.empty = empty;
}

void Options::DeleteTask(TaskDB& taskDB,Options& options){
  cout<<"What type of task do you want to delete?\n";
  cout<<"1.Pending Task \n2.Done task\n"
      <<"------------------------------------------------\n";
  cout<<"Choice:";
  int choice1;
  cin>>choice1;

  if (cin.fail()||choice1>2||choice1<1){
    cin.clear();
    cin.ignore(1000,'\n');
    cout<<"\nInvalid input. Please enter 1 or 2\n";
    return;
  }

  else if (choice1==1){
    ViewPending(taskDB,options);
    if (options.empty){
      cout<<"There are no Uncompleted tasks to delete!!!\n";
      return;
    }
    else{
      size_t index;
      cout<<"Enter task number to delete: ";
      cin>>index;
      taskDB.deletePendingTask(index);
      cout<<"\nTask deleting";
      cout<<"\n...\n...\n...\n";
      cout<<"Task deleted!";
      cout<<"------------------------------------------------\n";
    }
  }


  else{
    empty = options.empty;
    if (empty){
      cout<<"There are no Completed tasks to delete!!!";
      return;
    }
    else{
      size_t index;
      cout<<"Enter task number to delete: ";
      cin>>index;
      taskDB.deleteDoneTask(index);
      cout<<"\nTask deleting";
      cout<<"\n...\n...\n...\n";
      cout<<"Task deleted!";
      cout<<"------------------------------------------------\n";
    }
  }
}
// ====================
// Menu Implementation
// ====================

int DisplayMenu(){
  int choice;

  cout << "\nMenu:\n"
            << "1. Add new task\n"
            << "2. View Pending tasks\n"
            << "3. Mark a task as Done\n"
            << "4. View Done tasks\n"
            << "5. Delete a task from memory\n"
            << "6. Exit\n"
            << "------------------------------------------------\n"
            << "Choice: ";
  cin >> choice;
  cout<< "------------------------------------------------\n";
  return choice;
}