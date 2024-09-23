#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

class TodoList {
private:
    vector<Task> tasks;

public:
    void addTask(const string& taskDescription) {
        tasks.emplace_back(taskDescription);
        cout << "Task added: " << taskDescription << endl;
    }

    void viewTasks() {
        if (tasks.empty()) {
            cout << "No tasks available." << endl;
            return;
        }
        
        cout << "Tasks:\n";
        for (size_t i = 0; i < tasks.size(); i++) {
            cout << i + 1 << ". " << tasks[i].description
                 << " [ " << (tasks[i].completed ? "Completed" : "Pending") << " ]" << endl;
        }
    }

    void markTaskAsCompleted(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }
        tasks[index - 1].completed = true;
        cout << "Task marked as completed: " << tasks[index - 1].description << endl;
    }

    void removeTask(int index) {
        if (index < 1 || index > tasks.size()) {
            cout << "Invalid task number." << endl;
            return;
        }
        cout << "Removing task: " << tasks[index - 1].description << endl;
        tasks.erase(tasks.begin() + index - 1);
    }
};

int main() {
    TodoList todoList;
    int choice;

    do {
        cout << "\nTo-Do List Manager\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To ignore the newline character left in the input buffer

        switch (choice) {
            case 1: {
                cout << "Enter task description: ";
                string description;
                getline(cin, description);
                todoList.addTask(description);
                break;
            }
            case 2:
                todoList.viewTasks();
                break;
            case 3: {
                cout << "Enter task number to mark as completed: ";
                int taskNum;
                cin >> taskNum;
                todoList.markTaskAsCompleted(taskNum);
                break;
            }
            case 4: {
                cout << "Enter task number to remove: ";
                int taskNum;
                cin >> taskNum;
                todoList.removeTask(taskNum);
                break;
            }
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
