#include "../include/Task1.h"
#include <iostream>


int main() {
  TaskDB taskDB;
  taskDB.LoadTasks();

  Options options;
  int choice;

  while ((choice = DisplayMenu()) != 4) {
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
          
        default: 
          std::cout << "Invalid choice.\n";
      }
    } 
    catch (const std::exception& e) {
      std::cerr << "Error: " << e.what() << "\n";
    }
  }

  taskDB.SaveTasks();
  return 0;
}