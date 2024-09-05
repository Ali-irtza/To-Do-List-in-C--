# To-Do List Application

This repository contains a C++ program that implements a simple "To-Do List" application. The application allows users to manage their tasks with associated deadlines, time, priority, and status. The tasks are saved to a file and can be retrieved or updated as needed.

## Features

- **Add Tasks**: Users can add tasks along with a deadline, time, and priority level.
- **Task Status**: Each task is initially marked as "Pending" and can be updated as completed.
- **File Storage**: All tasks are stored in a text file (`TaskFile.txt`) and can be loaded for future use.
- **Task Counter**: Each task is automatically numbered with a unique ID, ensuring task organization.
- **Data Persistence**: The application supports saving and loading tasks, preserving task information across sessions.

## Project Structure

- `Todolist.cpp`: The main C++ program that implements the to-do list functionality.
- `TaskFile.txt`: The file where all tasks are saved. This file is generated automatically when tasks are added.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., g++)

### Compiling the Code

To compile the code, run the following command in your terminal:

```bash
g++ Todolist.cpp -o todolist
```
Running the Application
Once compiled, you can run the program using the following command: 

`  ./todolist    `

When you run the program, you will be prompted to add tasks with details such as task name, deadline, time, and priority. 
The tasks will then be saved to the TaskFile.txt file with a unique ID and an initial status of "Pending".

Example task structure:
Task 1: Complete project report
Deadline: 2024-09-10
Time: 14:00
Priority: High
Status: Pending

Contributing
Feel free to fork this repository and submit pull requests for any improvements or additional features you would like to add.

License
This project is licensed under the MIT License - see the LICENSE file for details.

Contact
For any questions or inquiries, please contact M-Ali Irtza at aliirtza738@gmail.com.


---

This `README.md` provides an introduction to your project, along with instructions on how to compile and run the program. 
If you'd like to include any additional information, such as specific commands or more detailed usage instructions, feel free to let me know!
