#include "../include/Task.h"

void SaveTasks(const vector<Task>& pendingTasks, const vector<Task>& doneTasks) {
  ofstream outFile("tasks.txt");
  if (!outFile) {
    cout << "Error saving tasks to file.\n";
    return;
  }

  outFile << "Pending\n";
  for (const auto& task : pendingTasks) {
    outFile << task.name << '\n';
  }

  outFile << "Done\n";
  for (const auto& task : doneTasks) {
    outFile << task.name << '\n';
  }

  outFile.close();
  cout << "Tasks saved successfully.\n";
}

void LoadTasks(vector<Task>& pendingTasks, vector<Task>& doneTasks) {
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
    } else if (line == "Done") {
      isPending = false;
    } else {
      Task task;
      task.name = line;
      task.state = isPending ? "Pending" : "Done";
      task.finishedness = !isPending;
      if (isPending) {
        pendingTasks.push_back(task);
      } else {
        doneTasks.push_back(task);
      }
    }
  }

  inFile.close();
  cout << "Tasks loaded successfully.\n";
}

// Function to add a task to pendingTasks
void AddTask(const vector<Task>& pendingTasks) {
  Task newTask;
  cout << "Enter task name: ";
  cin.ignore();
  getline(cin, newTask.name);
  newTask.state = "Pending";
  newTask.finishedness = false;
  pendingTasks.push_back(newTask);
  cout << "Task added successfully.\n";
}

// Function to print tasks
void PrintTasks(const vector<Task>& tasks, const string& title) {
  if (tasks.empty()) {
    cout << "No " << title << " tasks.\n";
    return;
  }

  cout << title << " Tasks:\n";
  for (size_t i = 0; i < tasks.size(); ++i) {
    cout << "Task number: " << i + 1 << '\n';
    cout << "Name: " << tasks[i].name << "\n";
    cout << "State: " << tasks[i].state << "\n";
    cout << "Finishedness: " << tasks[i].finishedness << "\n";
  }
}

// Function to view all pending tasks
void ViewTask(const vector<Task>& pendingTasks) {
  PrintTasks(pendingTasks, "Pending");
}

// Function to mark a pending task as done
void MarkDone(vector<Task>& pendingTasks, vector<Task>& doneTasks) {
  int index;
  ViewTask(pendingTasks);
  cout << "Enter task number to mark as done: ";
  cin >> index;

  if (cin.fail() || index <= 0 || index > pendingTasks.size()) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid task number. Please try again.\n";
    return;
  }

  Task done = pendingTasks[index - 1];
  done.state = "Done";
  done.finishedness = true;
  doneTasks.push_back(done);
  pendingTasks.erase(pendingTasks.begin() + index - 1);
  cout << "Task marked as done.\n";
}

// Function to view all completed tasks
void ViewDone(const vector<Task>& doneTasks) {
  PrintTasks(doneTasks, "Completed");
}

// Function to delete tasks from either list
void DeleteTask(vector<Task>& pendingTasks, vector<Task>& doneTasks) {
  int type, index;
  cout << "Delete from: 1. Pending  2. Done\nChoose: ";
  cin >> type;

  if (type == 1) {
    if (pendingTasks.empty()) {
      cout << "No tasks in the pending list to delete.\n";
      return;
    }
    ViewTask(pendingTasks);
    cout << "Enter task number to delete: ";
    cin >> index;

    if (cin.fail() || index <= 0 || index > pendingTasks.size()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid task number. Please try again.\n";
      return;
    }

    cout << "Are you sure you want to delete this task? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
      pendingTasks.erase(pendingTasks.begin() + index - 1);
      cout << "Task deleted from pending list.\n";
    }
  } else if (type == 2) {
    if (doneTasks.empty()) {
      cout << "No tasks in the done list to delete.\n";
      return;
    }
    ViewDone(doneTasks);
    cout << "Enter task number to delete: ";
    cin >> index;

    if (cin.fail() || index <= 0 || index > doneTasks.size()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid task number. Please try again.\n";
      return;
    }

    cout << "Are you sure you want to delete this task? (y/n): ";
    char confirm;
    cin >> confirm;
    if (confirm == 'y' || confirm == 'Y') {
      doneTasks.erase(doneTasks.begin() + index - 1);
      cout << "Task deleted from done list.\n";
    }
  } else {
    cout << "Invalid option.\n";
  }
}

int DisplayMenu() {
  int choice;
  cout << "\nWelcome to Day-Tracker\n";
  cout << "We have a set of operations for you:\n";
  cout << "1. Add tasks\n";
  cout << "2. View tasks\n";
  cout << "3. Mark tasks as done\n";
  cout << "4. View marked tasks\n";
  cout << "5. View all tasks\n";
  cout << "6. Delete a task\n";
  cout << "7. Save tasks\n";
  cout << "8. Exit\n";
  cout << "Enter one of the options (1-8): ";
  cin >> choice;

  if (cin.fail() || choice < 1 || choice > 8) {
    cin.clear();
    cin.ignore(1000, '\n');
    cout << "Invalid input. Please enter an integer between 1 and 8.\n";
    return -1;
  }
  return choice;
}
