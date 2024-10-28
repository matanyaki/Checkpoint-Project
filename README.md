# Check Point Project: School Management and Kernel Modules
This project consists of two main parts: a school management system that tracks students, grades, and courses, and a kernel module implementation for network security, including a mini firewall that blocks specified IP addresses.

### Part 1: School Management System
This system manages high school students, classes, and grades, with a focus on memory efficiency and optimized data access.

### Overview
The school management system has three main entities:
- School (single entity)
- Layers (grades)
- Classes
- Students
All data is stored in a structured file format, using a **hash table** for efficient data access.

### Key Features
Load data from a file into a structured database and display the full student list.
Menu options include:
* Adding new students, assigning them to classes and layers, and linking them to courses.
* Removing students from the system.
* Editing student information (e.g., updating grades).
* Searching for students by name, displaying full information.
* Retrieving performance-based reports:
  * Top 10 students in each layer by subject.
  * Identifying students at risk of failing based on specific criteria.
  * Calculating average grades per course by layer.
*Exporting the entire database to a file.
### Design Goals
- Memory Efficiency: Prioritizes reducing memory usage, even if it impacts runtime.
- Optimized Runtime: Ensures quick data retrieval and sorting, using data structures and algorithms with time complexity lower than O(n).
### Development Process
- Validate inputs and test each feature with valgrind to ensure memory integrity.
- Use gdb for debugging, and include error handling for unexpected inputs.
- Run valgrind checks after completing the full project and provide a clean report.
### How to Run
Load Data:
```
cd src
gcc Terminal.c -o Terminal
./Terminal
```
Run Menu and Features: Use the interactive menu to manage student records and generate reports.

# Part 2: Kernel Modules – Mini Firewall Implementation
This section involves creating and managing kernel modules for network security.

### Kernel Modules
- Basic Module:
  A simple module that prints messages on init and exit.
- Netfilter Hooks:
  A kernel module that connects to all five primary Netfilter hooks and prints a message every 10 seconds for each hook.
- Network Security Policy:
  Implements a security feature (e.g., blocking IPs from a specific country) in one of the Netfilter hooks, with policy explanations and test results.
### Mini Firewall with Kernel Driver API
A firewall with at least three security features, using an API that communicates with kernel modules.

### Key Features
- **Help Command**: Overview of available firewall commands and expected arguments.
- **Individual Commands**: Specific commands for each feature with necessary arguments.
- **API Communication**: Uses kernel communication methods to interact with modules.
### Example Security Feature
**IP Blocking**: Blocks traffic from specific "evil" IP addresses, demonstrating the firewall’s enforcement capability.
### How to Run
Load Kernel Module:
```
sudo insmod firewall_module.ko
```
Interact with Mini Firewall: Use the API to execute commands, e.g., help for available features.

### Resources
Kernel module programming references.
Netfilter and iptables documentation.

