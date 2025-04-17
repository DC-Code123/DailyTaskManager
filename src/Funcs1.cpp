#include "../include/Task1.h"

void TaskDB::SaveTasks(){
  ofstream outFile("tasks.txt");
  if(!outFile){
    cout<<"Error saving tasks to file.\n";
    return;
  }

  outFile <<"Pending\n";
  for (const auto& task : PendingTasks){
    outFile<<task.name<<'\n';
  }

  outFile<<"Done\n";
  for(const auto& task :DoneTasks){
    outFile<<task.name <<'\n';
  }

  outFile.close();
  cout<<"Tasks saving...\n";
  cout<<"Tasks saved successfully.\n";
}
void TaskDB::LoadTasks(){
  ifstream inFile("tasks.txt");
  if(!inFile){
    cout<<"No saved tasks found.\n";
  }

  string line;
  bool isPending;

  while (getline(inFile, line)){
    if (line== "Pending"){
      isPending = true;
    }
    else if (line=="Done"){
      isPending = false;
    }
    else{
      Task task;
      task.name = line;
      if (isPending){
        task.state = 'P';
      }
      else{
        task.state = 'D';
      }
      task.finishedness = !isPending;
      if (isPending){
        PendingTasks.push_back(task);
      }
      else {
        DoneTasks.push_back(task);
      }
    }
  }
  inFile.close();
  cout<<"Tasks loading...\n";
  cout<<"Tasks loaded successfully.\n";
}

void Options:: Addtask(vector<Task>& PendingTasks, vector<Task>& DoneTasks){
  Task newTask;
  cout<<"Enter task name: ";
  cin.ignore();
  getline(cin, newTask.name);
  newTask.state = 'P';
  newTask.finishedness = false;
  PendingTasks.push_back(newTask);
  cout<<"Task adding to list...\n";
  cout<<"Task added to list\n";
}


void Options::PrintTasks(const vector<Task>& tasks, const string& title){
  if (tasks.empty()){
    cout<< "No "<< title <<" tasks.\n";
    return;
  }

  cout<<title<<" Tasks:\n";
  for(size_t i = 0; i < tasks.size();++i){
    cout<<"Task number: "<<i +1<<'\n';
    cout<<"Name: "<<tasks[i].name<<'\n';
    cout<<"State: "<<tasks[i].state<<'\n';
    cout<<"Finishedness: "<<tasks[i].finishedness<<'\n';
  }
}

void Options::ViewPending(const vector<Task>& PendingTasks){
  PrintTasks(PendingTasks,"Pending");
}

void Options::MarkDone(vector<Task>& PendingTasks,vector<Task>& DoneTasks){
  int index;
  ViewPending(PendingTasks);
  cout<<"Enter task number to mark as done: \n";
  cin>>index;
  
  if (cin.fail()||index <= 0||index >PendingTasks.size()){
    cin.clear();
    cin.ignore(1000,'\n');
    cout<<"Invalid task number. Please try again.\n";
    return;
  }

  Task Done = PendingTasks[index-1];
  Done.state = 'D';
  Done.finishedness = true;
  DoneTasks.push_back(Done);
  PendingTasks.erase(PendingTasks.begin()+index-1);
  cout<<"Task marking as done...\n";
  cout<<"Task marked ad done!\n";
}

void Options::ViewDone(const vector<Task>& DoneTasks)