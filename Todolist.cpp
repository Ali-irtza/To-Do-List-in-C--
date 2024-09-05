/*

Project : To Do List
Made by : M-Ali irtza
Contact : aliirtza738 @gmail.com

*/
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<map>
using namespace std;
static int counter=0;
template<class T,class T1>
class Todolist{
private:
	T task, deadline,time,status,savingline;
	T1 priority;
	
public:
	Todolist(){}
	Todolist(T task, T deadline,T1 priority,T time):task(task),deadline(deadline),priority(priority),time(time),status("Pending"){
		datafile();  //Calling datafile function to directly enter the user's task into the file
	}
	
	void datafile(){
		int count=0;
		ofstream file;
		file.open("TaskFile.txt",ios::app);
		if (!file){
			cout << "Data file not opened" << endl;
			return;
		}
		file << "Task "<<counter++<<" : " << task << " Deadline: " << deadline << " Time: " << time << " Priority: " << priority << " Status: " << status << endl;
		savecounter();    //Saving the counter everytime we enter a new task
		file.close();
	}
	void loadfile(){
		ifstream file;
		file.open("TaskFile.txt");
		if (!file) {
			cout << "File not opened" << endl;
			return;
		}
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
		void savecounter() {
			ofstream file("TaskCounter.txt");
			if (!file) {
				cout << "TaskCounter Failed to open" << endl;
				return;
			}
			file << counter << endl;
			file.close();
		}
		void loadcounter() {
			ifstream file("TaskCounter.txt");
			if (!file) {
				cout << "First Time Execution Setting counter to 0" << endl;
				counter = 0;
				return;
			}
			file >> counter;
			file.close();
		}

		void taskmark(string number) {
			ifstream file("TaskFile.txt");
			ofstream file1("TempFile.txt");
			if (!file||!file1) {
				cout << "File not open to mark" << endl;
				return;
			}
			string cop = "Task " + number +" : ";    
			string line;
			while (getline(file, line)) {
				int pos = line.find(cop);
				if (pos != string::npos) {                          //String::npos returns if the wrod not found in the line
					size_t position = line.find("Status: ");                 //Size_t is just like in integer that stores non negative values used to store the size or indexes of arrays and strings   
						if (position != string::npos) {                      //We can also use int instead of size_t
							position += 8;
							size_t endpos = line.find(' ', position);
							if (endpos ==string::npos) {
								endpos = line.length();
							}
							line.replace(position, string::npos, "Completed");
						}
				}
				file1 << line << endl;
			}
			file.close();
			file1.close();
			remove("TaskFile.txt");
			rename("TempFile.txt", "TaskFile.txt");
			
		}

		void removetask(string number) {
			ifstream file("TaskFile.txt");
			ofstream file1("TempFile.txt");
			if (!file || !file1) {
				cout << "Task can not be removed file not open to remove the task" << endl;
				return;
			}
			string cop = "Task " + number + " : ";
			string line;
			while (getline(file, line)) {
				
				int pos = line.find(cop);
				if (pos == string::npos) {
					file1 << line << endl;
				}
			}
			file.close();
			file1.close();

			remove("TaskFile.txt");
			rename("TempFile.txt", "TaskFile.txt");
		}

		int pendingtasks() {
			ifstream file("TaskFile.txt");
			if (!file) {
				cout << "File not Open" << endl;
				return 1;
			}
			int count=0;
			string line;
			while (getline(file, line)) {
				size_t pos = line.find("Pending");
				if (pos != string::npos)
				{
					count++;
				}
			}
			file.close();
			return count;
		}
		int completedtasks() {
			ifstream file("TaskFile.txt");
			if (!file) {
				cout << "File not Open" << endl;
				return 1;
			}
			int count = 0;
			string line;
			while (getline(file, line)) {
				size_t pos = line.find("Completed");
				if (pos != string::npos)
				{
					count++;
				}
			}
			file.close();
			return count;
		}
		int totaltasks() {
			ifstream file("TaskFile.txt");
			if (!file) {
				cout << "File not Open" << endl;
				return 1;
			}
			int count = 0;
			string line;
			while (getline(file, line)) {
					count++;
			}
			file.close();
			return count;
		}
		void sortbypriority() {
			multimap<int, string> mymap;          //Multimap is a data structure that stores key value pairs where multiple keys can have same value
			ifstream file("TaskFile.txt");                        
			if (!file) {
				cout << "Sort Failed file not opened" << endl;
				return;
			}
			string line;
			while (getline(file, line)) {
				size_t pos = line.find("Priority: ");
				if (pos != string::npos) {
					int priority = stoi(line.substr(pos + 10));                  
					mymap.insert({ priority,line });
				}
			}
			file.close();
			ofstream file1("TaskFile.txt");
			for (const auto& task : mymap) {
				file1 << task.second << endl;
			}
			file1.close();
			cout << "Tasks have been sorted by Priority" << endl;
		}
		bool tasksearch(string name) {
			ifstream file("TaskFile.txt");
			if (!file) {
				cout << "Failed to open" << endl;
				return false;
			}
			string line;
			while (getline(file, line)) {
				int pos = line.find(name);
				if (pos != string::npos) {
					savingline = line;
					cout << line << endl;
					return true;
				}
			}
			return false;
		}
		void edittask(string choice)
		{
			ifstream file;
			ofstream file1;
			file.open("TaskFile.txt");
			file1.open("TempFile.txt");
			if (!file||!file1) 
			{
				cout << "Task Can not be edit" << endl;
				return;
			}
			string line;
			bool edited = false;
			
			while (getline(file, line)) {
				if (line.find(savingline) != string::npos && !edited) {
					size_t pos = line.find(choice);                         //size_t stroing the starting index of choice
					if (pos != string::npos) {
						pos = pos + choice.length();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');     // Clear the input buffer before using getline
						string replacement;
						cout << "Enter the replacement: ";
						getline(cin, replacement);	
						size_t end_pos;
						if (choice == " : ") {   //For changing in Task
						     end_pos = line.find(" Deadline", pos);
						}
						else {
							end_pos = line.find(' ', pos);        // Find the next space or end of line to limit the replacement
						}
						if (end_pos == string::npos) {
							end_pos = line.length();
						}
						line.replace(pos, end_pos - pos, replacement);     // Replace only the portion of the line corresponding to the choice
						savingline = line;  // Update savingline with the modified content
						edited = true;
					}
				}
				file1 << line << endl;  // Write the line (edited or not) to the temp file
			}

			file1.close();
			file.close();

			remove("TaskFile.txt");
			rename("TempFile.txt", "TaskFile.txt");
		}
};
int main(){
	Todolist<string, int>taskcounter;     //Object for loading Taskcounter in the Start
	taskcounter.loadcounter();
	string task,deadline,time,number;
	int priority,choice;
	do
	{
		cout << "0-Exit\n1-Add New Task\n2-Check The Previous Tasks\n3-Mark the Task\n4-Remove the Task\n5-Pending Tasks Count\n6-Completed Task Count\n7-Total Task Count\n8-Search For Task\n9-Sort by Priority\n10-Edit Task" << endl;
		cout << "Enter your choice:";
		cin >> choice;
		switch (choice) {
		case 0:
		{
			break;
		}
		case 1:
		{
			cin.ignore();
			cout << "Enter the task: ";
			getline(cin, task);
			cout << "Enter the task deadline (mm/dd/yyyy):";
			cin >> deadline;
			cout << "Enter the time (12:00):";
			cin >> time;
			cout << "Enter task Priority: ";
			cin >> priority;
			Todolist<string, int> obj(task, deadline, priority, time);
			break;
		}
		case 2:
		{
			cout << "Your Tasks:" << endl;
			taskcounter.loadfile();
			break;
		}
		case 3:
		{
			cout << "Enter the task number you want to mark completed: ";
			cin >> number;
			taskcounter.taskmark(number);
			break;
		}
		case 4:
		{
			cout << "Enter the task you want to remove:";
			cin >> number;
			taskcounter.removetask(number);
			break;
		}
		case 5:
		{
			cout << "Pending tasks:" << taskcounter.pendingtasks() << endl;
			break;
		}
		case 6:
		{
			cout << "Completed Tasks:" << taskcounter.completedtasks() << endl;
			break;
		}
		case 7:
		{
			cout << "Total Tasks:" << taskcounter.totaltasks() << endl;
			break;
		}
		case 8:
		{
			cout << "Enter the name of task you want to find:";
			cin.ignore();
			getline(cin, number);
			bool result=taskcounter.tasksearch(number);
			if (result == false) {
				cout << "Task Not found" << endl;
			}
			break;
		}
		case 9:
		{
			taskcounter.sortbypriority();
			break;
		}
		case 10:
		{
			cin.ignore();
			cout << "Enter the name of the task you want to edit" << endl;
			getline(cin, number);
			bool result = taskcounter.tasksearch(number);
			if (result == true) {
				int editchoice;
				do {
					cout << "0-Exit\n1-Task Name\n2-Date\n3-Time\n4-Priority" << endl;
					cout << "Enter your choice: ";
					cin >> editchoice;
					switch (editchoice) {
					case 1:{
						taskcounter.edittask(" : ");
						break;
					}
					case 2:{
						taskcounter.edittask("Deadline: ");
						break;
					}
					case 3:{
						taskcounter.edittask("Time: ");
						break;
					}
					case 4:{
						taskcounter.edittask("Priority: ");
						break;
					}
					default:{
						break;
					}
					}
				} while (editchoice != 0);
			}
			else {
				cout << "Please Enter the Correct Name" << endl;
			}
			break;
		}
		default: {
			break;
		}
	 }
	}
	while (choice != 0);
	
	cout << "Press any key to continue" << endl;
	cin.get();
	return 0;
}