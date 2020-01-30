#include <iostream>
#include <vector>
#include <sstream>
#include <zconf.h>
ghinclude <fcntl.h>
#include <sys/wait.h>

using namespace std;

/**
 * The process class
 *
 * @param pid the pid
 * @param job_number the job number
 * @param the command the user wanted to run
 */
class Process {

    /**
     * The pid
     */
    pid_t pid;

    /**
     * The job number
     */
    int job_number;

    /**
     * The command
     */
    string command;

    public:
        void set_values(pid_t, int, string);
        pid_t get_pid() { return pid; }
        int get_job_number() { return job_number; }
        string get_command() { return command; }
};

/**
 * Sets the values of the process
 * @param p the pid
 * @param n the job number
 * @param c the command
 */
void Process::set_values(pid_t p, int n, string c) {
    pid = p;
    job_number = n;
    command = c;
}

/**
 * Parses the input and puts it into a vector
 * @param input the input string
 * @return the input vector
 */
vector<string> handleInput(string input, char delimeter) {

    vector<string> tokens;

    int beginning = input.find_first_not_of(' ');
    int end = input.find_last_not_of(' ');
    int range = end - beginning + 1;

    input = input.substr(beginning, range);


    istringstream ss(input);
    string token;

    while(getline(ss, token, delimeter)) {
        tokens.push_back(token);
    }

    return tokens;
}

/**
 * Handler for the change directories command
 * @param tokens the vector of tokens
 */
void handleChangeDirectory(vector<string> tokens) {

    // check for invalid format
    if(tokens.size() != 2) {
        cerr << "\tERROR: Invalid format for 'cd' command\n";
        return;
    }

    // try changing directories
    int result = 0;
    result = chdir(tokens[1].c_str());

    // there was an error changing directories
    if(result < 0) {
        cerr << "\tERROR: No such file or directory.\n";
    }

    // successful, print new working directory
    else {
        char* dir = (char*) malloc(256);
        getcwd(dir, 256);
        cout << dir << "\n";
    }
}

/**
 * Handler for the wait command
 * @param tokens the vector of tokens
 */
void handleWait(vector<string> tokens, vector<Process> &processes) {

    // check for invalid format
    if(tokens.size() != 2) {
        cerr << "\tERROR: Invalid format for 'wait' command\n";
        return;
    }

    // search for the job number in the processes vector, then call wait on that pid.
    for(int i = 0; i < processes.size(); i++) {
        if(processes[i].get_job_number() == atoi(tokens[1].c_str())) {
            int result = waitpid(processes[i].get_pid(), NULL, 0);

            if(result < -1) {
                cerr << "\tERROR: Could not wait!!\n";
            }
        }
    }
}

/**
 * Helper method that will execute the task passed in the command vector.
 * @param command the command to run
 */
void executeTask(vector<string> command) {
    // convert string vector to char* vector
    vector<char *> argVector;
    for(int i = 0; i < command.size(); i++) {
        argVector.push_back((char *)command[i].c_str());
    }

    // make the last element a null cell
    argVector.push_back(NULL);

    // convert vector to char**
    char** args = &argVector[0];

    // execute the command
    execvp(command[0].c_str(), args);
}


/**
 * Handler for the foreground task. This function will fork a new process, execute the process, and waits until
 * the process is finished
 * @param tokens the vector of tokens
 */
void handleForegroundTask(vector<string> tokens, string &outputFile, string &inputFile) {
    pid_t pid = fork();

    // error with the fork
    if(pid < 0) {
        cerr << "\tERROR: Could not create new process\n";
        return;
    }

    if(pid == 0) {

        if(inputFile.size() > 0) {
            // open the file
            int fd = open(inputFile.c_str(), O_RDONLY);

            if(fd < 0) {
                cerr << "Error Input file: " + inputFile << "\n";
            }

            else {

                // chance stdout to the file
                dup2(fd, STDIN_FILENO);

                // close the file
                close(fd);
            }
        }

        // check for output file
        if(outputFile.size() > 0) {

            // open the file
            int fd = open(outputFile.c_str(), O_RDWR | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);

            if(fd < 0) {
                cerr << "Error with file: " + outputFile << "\n";
            }

            else {

                // chance stdout to the file
                dup2(fd, STDOUT_FILENO);

                // close the file
                close(fd);
            }
        }

        executeTask(tokens);
        exit(0);
    }

    // wait for the task to finish
    waitpid(pid, NULL, 0);
}

/**
 * Handles the background task
 * @param input
 * @param tokens
 * @param jobCounter
 * @return
 */
Process handleBackgroundTask(string input, vector<string> tokens, int &jobCounter, string &outputFile, string &inputFile) {

    Process* process = new Process();
    pid_t pid = fork();

    // error with the fork
    if(pid < 0) {
        cerr << "\tERROR: Could not create new process\n";
    }

    if(!pid) {

        if(inputFile.size() > 0) {
            // open the file
            int fd = open(inputFile.c_str(), O_RDONLY);

            if(fd < 0) {
                cerr << "Error Input file: " + inputFile << "\n";
            }

            else {

                // chance stdout to the file
                dup2(fd, STDIN_FILENO);

                // close the file
                close(fd);
            }
        }

        // check for output file
        if(outputFile.size() > 0) {

            // open the file
            int fd = open(outputFile.c_str(), O_RDWR | O_CREAT | O_TRUNC,  S_IRUSR | S_IWUSR);

            if(fd < 0) {
                cerr << "Error Output File: " + outputFile << "\n";
            }

            else {

                // chance stdout to the file
                dup2(fd, STDOUT_FILENO);

                // close the file
                close(fd);
            }
        }


        executeTask(tokens);

        // free up the process space if there was an error with execvp
        delete(process);
        exit(0);
    }

    input.pop_back();
    process->set_values(pid, jobCounter, input);
    return *process;
}

/**
 * Helper method for making new process piping. This function is responsible for closing and opening the proper file
 * descriptors.
 * @param inFileDescriptor the in file descriptor
 * @param outFileDescriptor the out file descriptor
 * @param command the command to execute
 */
void makeNewProcess(int inFileDescriptor, int outFileDescriptor, vector<string> command) {

    pid_t pid;
    pid = fork();

    if(pid == 0) {
        if(inFileDescriptor != 0) {
            dup2(inFileDescriptor, 0);
            close(inFileDescriptor);
        }

        if(outFileDescriptor != 1) {
            dup2(outFileDescriptor, 1);
            close(outFileDescriptor);
        }

        executeTask(command);
    }
}

/**
 * Handles piping
 * @param tokens the tokens
 */
void handlePipe(vector<string> tokens) {

    pid_t pid;
    pid = fork();

    if(pid == 0) {
        int pipefd[2];
        int in = 0;
        int i;

        for(i = 0; i < tokens.size() - 1; ++i) {
            pipe(pipefd);

            makeNewProcess(in, pipefd[1], handleInput(tokens[i], ' '));

            close(pipefd[1]);
            in = pipefd[0];
        }

        if(in != 0) {
            dup2(in, 0);
        }


        vector<string> command = handleInput(tokens[i], ' ');
        executeTask(command);
    }

    else {
        waitpid(pid, NULL, 0);
    }
}

/**
 * Prints the current processes out. Will print nothing if there is no running tasks or no finsiehd tasks
 * @param processes
 * @param finishedProcesses
 */
void printProcesses(vector<Process> &processes, vector<Process> &finishedProcesses) {

    if(processes.size() > 0) {
        cout << "Running: \n";
        for(int i = 0; i < processes.size(); i++) {
            cout << "\t[" << processes[i].get_job_number() << "] " << processes[i].get_command() << "\n";
        }
    }

    if(finishedProcesses.size() > 0) {
        cout << "Finished: \n";
        for(int i = 0; i < finishedProcesses.size(); i++) {
            cout << "\t[" << finishedProcesses[i].get_job_number() << "] " << finishedProcesses[i].get_command() << "\n";
        }
    }

}

/**
 * Cleans up the processes. Moves the finished processes to the finshed array and removes all elements in the finished array
 * @param processes
 * @param finishedProcesses
 */
void cleanUpProcess(vector<Process> &processes, vector<Process> &finished, int &jobCounter) {

    // remove finished processes from the previous iteration
    for(int i = 0; i < finished.size(); i++) {
        finished.pop_back();
    }

    // remove finished processes from running, then add them to finished.
    for(int i = 0; i < processes.size(); i++) {
        if(waitpid(processes[i].get_pid(), NULL, WNOHANG) != 0) {
            finished.push_back(processes[i]);
            processes.erase(processes.begin() + i);

        }
    }

    if(processes.size() == 0) {
        jobCounter = 1;
    }
}

/**
 * The main program loop
 * @return
 */
int main() {

    vector<Process> processes;
    vector<Process> finished;
    int jobCounter = 1;
    int isRunning = 1;

    while(isRunning == 1) {

        // clean up the processes for the next round
        cleanUpProcess(processes, finished, jobCounter);

        string input;

        cout << "wsh: ";

        // get the input
        getline(cin, input);

        // if the file size is 0 (user just pressed enter), print the processes
        if(input.size() == 0) {
            isRunning = 1;
        }

        else {

            vector<string> tokens = handleInput(input, '|');
            if (tokens.size() > 1) {

                // remove pipes from tokens
                for (int i = 0; i < tokens.size(); i++) {
                    if (tokens[i].compare("|") == 0) {
                        tokens.erase(tokens.begin() + i);
                    }
                }

                // handle the pipe
                handlePipe(tokens);
            } else {
                tokens = handleInput(input, ' ');

                string outputFile = "";
                string inputFile = "";

                // check for input or output
                for (int i = 0; i < tokens.size(); i++) {

                    // if the token is >, then the next token is the output file
                    if (tokens[i].compare(">") == 0) {
                        outputFile = tokens[i + 1];
                        tokens.erase(tokens.begin() + i + 1);
                        tokens.erase(tokens.begin() + i);
                    }
                }

                for (int i = 0; i < tokens.size(); i++) {

                    // if the token is <, then the next token is the input file
                    if (tokens[i].compare("<") == 0) {
                        inputFile = tokens[i + 1];
                        tokens.erase(tokens.begin() + i + 1);
                        tokens.erase(tokens.begin() + i);
                    }
                }

                // if the first token is exit, exit the program.
                if (tokens[0].compare("exit") == 0) {
                    isRunning = 0;
                    cout << "Good Bye\n";
                }

                    // check for cd command
                else if (tokens[0].compare("cd") == 0) {
                    handleChangeDirectory(tokens);
                }

                    // check for wait command
                else if (tokens[0].compare("wait") == 0) {
                    handleWait(tokens, processes);
                    cleanUpProcess(processes, finished, jobCounter);
                }

                    // if the last token is the & symbol, run a background task
                else if (tokens[tokens.size() - 1].compare("&") == 0) {
                    Process *process = new Process();
                    tokens.pop_back();
                    *process = handleBackgroundTask(input, tokens, jobCounter, outputFile, inputFile);
                    processes.push_back(*process);
                    jobCounter++;
                }

                    // if none of the statements above were checked, then run a foreground task
                else {
                    handleForegroundTask(tokens, outputFile, inputFile);
                }

                isRunning = 1;
            }
        }

        // print the processes
        printProcesses(processes, finished);
    }
}
