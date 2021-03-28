//
//  main.cpp
//  Writing_your_own_Unix_Shell
//
//  Created by Vladimir Antigua on 2/20/21.
//
#include "shelpers.h"
#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <stdio.h>
#include <initializer_list>
#include <readline/readline.h>

// compile:
    // g++ -std=c++14 main.cpp shelpers.cpp
        //run:
            //./a.out

// when submitting the assignemt put a comment in Canvas Enter EXIT to get out of the while loop.

int main(int argc, const char * argv[]) {
    
    //Part 1: running a single command at a time:
    
    //    Some example of commands that you should be able to perform:
    //
    //    ls
    //    cat someFile
    //    echo hello world
    
    
    std::string userInput;
    while(std::getline(std::cin, userInput)) {
        
        if (userInput == "exit") { // exit program if user requests
            exit(0);
        }
        //You'll need to fill in the appropriate parts of the getCommands functions (read the comments)
        std::vector<Command> args = getCommands(tokenize(userInput));
        
        // commands e.g. "ps -ax  | grep {print $1}"
        // execvp("ls", { "ls", "-l", NULL})
        // execvp("cat", { "cat", "myTextFile.txt", NULL})
        for (int i = 0; i < args.size(); i++) {
            
            // int execvp(const char *file, char *const argv[]);
            std::string file = args[i].exec;
            const char **argv_ = args[i].argv.data();
            
            int forked;
            if ((forked = fork()) == 0) { // in child process
                
                dup2(args[i].fdStdin, 0);
                dup2(args[i].fdStdout, 1);
                
                // converts string into character pointer:
                int execRes = execvp(file.c_str(), const_cast<char**> (argv_));
                if (execRes == -1) { printf("execvp error\n"); exit(1); }
            }
            else if (forked == -1) { perror("fork error\n"); exit(1); }
            
            else { // we're in the parent
                
                // check if the args[i].background if I am not waiting keep going: put the wait inside the if statement:
           
                if (args[i].background == false) {
                    waitpid(forked, NULL, 0); // wait for child to finish job
                }
                if (args[i].fdStdout != 1) {
                    close(args[i].fdStdout);
                }
                if (args[i].fdStdin != 0) {
                    close(args[i].fdStdin);
                }
                
                //   Part 4: shell builtins CD:
                              
                if (args[i].exec == "cd" ) {
                    if (args[i].argv.size() > 2) {
                        //change directory:
                        chdir(args[i].argv[1]);
                    }
                    else if (args[i].argv.size() == 2) {
                        chdir(getenv("HOME"));
                        
                    }
                    
                }
            }
        }
    }
    
    return 0;
}
