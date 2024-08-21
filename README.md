
# Concurrent News Broadcasting System

## Project Overview
This repository contains a concurrent news broadcasting system implemented in C++. The system simulates a news organization where different types of news stories are produced, managed, and displayed in real-time. It leverages concurrent programming techniques and synchronization mechanisms to ensure efficient and correct news story processing.

## Components Description

### Producers
Each producer generates news stories in a specified format, distinguishing them by type (SPORTS, NEWS, WEATHER). They submit these stories to their unique queues, managing the production rate and ensuring the system's responsiveness.

### Dispatcher
The dispatcher processes incoming news stories from multiple producers using a non-blocking Round Robin algorithm. It categorizes stories into type-specific queues for further processing by the corresponding Co-Editors.

### Co-Editors
Co-Editors receive stories from their type-specific queues, simulate an editing process, and forward the refined stories to a shared queue for display. This simulation includes a brief delay to mimic real-world processing times.

### Screen Manager
The Screen Manager is responsible for displaying the final edited stories to the end-user (console output). It ensures that all messages are displayed in the order they are received and concludes its operation upon receiving a "DONE" message from each Co-Editor.

## System Workflow
The workflow adheres to a strict producer-consumer pattern with enhanced synchronization:
- Producers generate and enqueue news stories.
- The Dispatcher dequeues these stories, sorts them, and enqueues them into type-specific queues.
- Co-Editors process and forward these to the Screen Manager.
- The Screen Manager finalizes the broadcasting by displaying the stories.

## Technical Implementation
- **Bounded Buffers**: Used for queues between all components to manage data flow.
- **Semaphores**: Employ binary and counting semaphores for synchronization across different stages of the pipeline to prevent race conditions and data corruption.
![image](https://github.com/user-attachments/assets/15af3a96-334b-4872-962d-1e57d7162d3a)

## Getting Started

### Prerequisites
- Linux-based OS
- GCC compiler

### Setup and Compilation
Clone the repository and compile the project using the provided Makefile:

```bash
git clone https://github.com/yourusername/concurrent-news-system.git
cd concurrent-news-system
make all
```

### Running the Application
Execute the program by specifying the configuration file:

```bash
./ex3.out config.txt
```

Ensure the configuration file is formatted correctly as per the specifications given in the original assignment description.

## Configuration
Edit the `config.txt` to adjust the number of products per producer and the sizes of the queues:

```
PRODUCER 1
30
queue size = 5

PRODUCER 2
25
queue size = 3

...
```
