#ifndef TASK1_H
#define TASK1_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Task{
  string name;
  char state;
  bool finishedness;
};

class TaskDB{
private:
  void SaveTasks();
  void LoadTasks();
public:
  vector<Task> PendingTasks;
  vector<Task> DoneTasks;
  TaskDB(){
    cout<<"Database Creating...";
    cout<<"Database Created!";
  }
};

class Options{
public:
  void Addtask(vector<Task>& PendingTasks, vector<Task>& DoneTasks);
  void PrintTasks(const vector<Task>& tasks, const string& title);
  void ViewPending(const vector<Task>& PendingTasks);
  void MarkDone(vector<Task>& PendingTasks, vector<Task>& DoneTasks);
  void ViewDone(const vector<Task>& DoneTasks);
  void DeleteTask(vector<Task>& PendingTasks, vector<Task>& DoneTasks);
  Options(){
    cout<<"Object creating...";
    cout<<"Object created!";
  }
};
int DisplayMenu();

#endif