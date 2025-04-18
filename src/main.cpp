#include "../include/Task.h"
#include <iostream>
using namespace std;


int main() {
  TaskDB taskDB;
  taskDB.LoadTasks();

  Options options;
  int choice;

  while ((choice = DisplayMenu()) != 6) {
    try {
      switch (choice) {
        case 1: 
          options.AddTask(taskDB); 
          break;
          
        case 2: 
          options.ViewPending(taskDB); 
          break;
          
        case 3: 
          options.MarkDone(taskDB); 
          break;

        case 4:
          options.ViewDone(taskDB);
          break;

        case 5:
          options.DeleteTask(taskDB);
          break;

        default: 
          cout << "Invalid choice.\n";
      }
    } 
    catch (const exception& e) {
      cerr << "Error: " << e.what() << "\n";
    }
  }

  taskDB.SaveTasks();
  return 0;
}
