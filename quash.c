 //*****************************************************************************
 // @file quash.c
 //
 // Quash's main file
 // Dylan Dreiling
 // Hayden Kaustinen
 //
 //*****************************************************************************

 //*****************************************************************************
 //
 //! \addtogroup quash
 //! @{
 //
 //*****************************************************************************

//******************************************************************************
//  Included Files
//******************************************************************************

// Putting "quash.h"  above the other includes allows us to ensure
// this file's header's #include statements are self
// contained.
#include "quash.h"
#include <string.h>
#include <errno.h>

//**************************************************************************
// Private Variables
// **************************************************************************
/**
 * Keep track of whether Quash should request another command or not.
 */
// NOTE: "static" causes the "running" variable to only be declared in this
// compilation unit (this file and all files that include it). This is similar
// to private in other languages.
static bool running;

//**************************************************************************
// char array to hold value of $HOME
// **************************************************************************
char home[MAX_COMMAND_LENGTH]; //$HOME variable
//**************************************************************************
// char array to hold value of $PATH
// **************************************************************************
char path[MAX_COMMAND_LENGTH]; //#PATH variable
//**************************************************************************
// char array to hold value of current working directory
// **************************************************************************
char cwd[MAX_COMMAND_LENGTH];
//**************************************************************************
// pointer to token in a given string,
// tokens are substrings delimted by second arg of strtok()
// **************************************************************************
char* token;

//*****************************************************************************
//
//!
//! \param *buf character buffer to hold directory
//! \param size size of buf array
//!
//! Provides the current working diretory to the array, buf, which is of length size
//!
//! \return None.
//
//*****************************************************************************
char *getcwd(char *buf, size_t size);

//**************************************************************************
// process status
// **************************************************************************
int status;

//**************************************************************************
// child processes
// **************************************************************************
int pid_1, pid_2; //child processes

/**************************************************************************
 * Private Functions
 **************************************************************************/
/**
 * Start the main loop by setting the running flag to true
 */
static void start() {
  running = true;
}

/**************************************************************************
 * Public Functions
 **************************************************************************/
 bool is_running() {
  return running;
}

void terminate() {
  running = false;
}

bool get_command(command_t* cmd, FILE* in) {
  if (fgets(cmd->cmdstr, MAX_COMMAND_LENGTH, in) != NULL) {
    size_t len = strlen(cmd->cmdstr);
    char last_char = cmd->cmdstr[len - 1];

    if (last_char == '\n' || last_char == '\r') {
      // Remove trailing new line character.
      cmd->cmdstr[len - 1] = '\0';
      cmd->cmdlen = len - 1;
    }
    else
      cmd->cmdlen = len;

    return true;
  }
  else
    return false;
}

/**
 * Quash entry point
 *
 * @param argc argument count from the command line
 * @param argv argument vector from the command line
 * @return program exit status
 */
int main(int argc, char** argv){
  //Command holder argument
  command_t cmd;

  //initialize variables.
  strcpy(home, "/home/");
  strcpy(path, "/home/:/home/ddreilin/EECS_678/Project1/Quash/");

  getcwd(cwd, sizeof(cwd));
  start();

  puts("Welcome to Quash!");
  puts("Type \"exit\" or \"quit\" to quit");

  // Main execution loop
  while (is_running() && get_command(&cmd, stdin)) {
    // NOTE: I would not recommend keeping anything inside the body of
    // this while loop. It is just an example.
    // The commands should be parsed, then executed.
    manager(&cmd);
  }
  return EXIT_SUCCESS;
}

//what is pch?
char * pch;

//**************************************************************************
// function to parse/manage/execute commands
//**************************************************************************
void manager(command_t* cmd ){
	 char* temp [MAX_COMMAND_LENGTH];
	 strcpy(temp, cmd->cmdstr);
	 char* tokens = strtok(temp, " ");

	 //cd if the first two chars are cd
	 if (!strcmp(tokens, "cd")){
	 	run_cd( tokens );
	 }
	 //set
	 else if (!strcmp(tokens, "set")){
	 	run_set( tokens);
	 }
	 //echo
	 else if (!strcmp(tokens, "echo")){
	 	run_echo( tokens );
	 }
	 //pwd
	 else if (!strcmp(tokens, "pwd")){
	 	run_pwd( tokens );
	 }
	 //jobs
	 else if (!strcmp(tokens, "jobs")){
	 	run_jobs( cmd, tokens );
	 }
	 //exit command
	 else if (!strcmp(tokens, "exit") || !strcmp(tokens, "quit") )
      terminate(); // Exit Quash
  //run an executable
  else{
    	run_exec(cmd, tokens);
    }
}

/*******************************************************
*
*
* Run Command functions
*
*
*******************************************************/
//**************************************************************************
// function change directory
//**************************************************************************
void run_cd( char* tokens ){
	puts("cd function");
	tokens = strtok(NULL, "");
	//go to home
	if(tokens == NULL){
		chdir(home);
	}
	//go to an absolute directory
	else if(!strncmp(tokens, "/", 1)){
		char temp [MAX_COMMAND_LENGTH];
		temp[0]='\0';

		while(tokens != NULL){
				strcat(temp,"/");
				strcat(temp, tokens);
				tokens = strtok(NULL, "/");
		}
		chdir(temp);
	}
	//go to a directory inside current working directory.
	else{
		char temp [MAX_COMMAND_LENGTH];
		strcpy(temp,cwd);

		while(tokens != NULL){
				strcat(temp,"/");
				strcat(temp, tokens);
				tokens = strtok(NULL, "/");
		}
		chdir(temp);
	}
}

//**************************************************************************
// function to set variable values
//**************************************************************************
void run_set( char* tokens ){
	puts("set function");
	tokens = strtok(NULL, "=");
	//PATH variable
	if (!strcmp(tokens, "PATH")){
		puts("Setting PATH variable");
		tokens = strtok(NULL, "");
		strcpy(path, tokens);
	}
	//HOME Variable
	else if (!strcmp(tokens, "HOME")){
		puts("Setting HOME variable");
		tokens = strtok(NULL, "");
		puts(tokens);
		strcpy(home, tokens);
	}
	//default
	else{
		puts("Incorrect set syntax");
	}
}

//**************************************************************************
//function to execute echo
//**************************************************************************
void run_echo( char* tokens){
	puts("echo function");

	tokens = strtok(NULL, "");
	//PATH variable
	if (!strcmp(tokens, "$PATH")){
		puts(path);
	}
	//HOME Variable
	else if (!strcmp(tokens, "$HOME")){
		puts(home);
	}
	//default
	else{
		puts("Incorrect echo syntax");
	}
}

//**************************************************************************
//function to execute pwd
//**************************************************************************
void run_pwd(){
   if (getcwd(cwd, sizeof(cwd)) != NULL){
   	fprintf(stdout, "Current working dir: %s/\n", cwd);
   	}
   else{
   		perror("getcwd() error");
   	}
}

//**************************************************************************
//function to execute jobs
//**************************************************************************
void run_jobs(){
	puts("jobs function");
}

//**************************************************************************
//function to execute an executable
//**************************************************************************
void run_exec( command_t* cmd, char* tokens ){

	//Exec booleans to handle special characters
	bool special = false;
	bool greaterThan = false;
	bool lessThan = false;
	bool execPipe = false;
	bool background = false;
	bool moreArgs = false;

	//Inside CWD has "./exe arg" format
	if( !strncmp(cmd->cmdstr, "./", 2) ){
		//variables needed to execute a command
		char temp [MAX_COMMAND_LENGTH];//command
		char temp2 [MAX_COMMAND_LENGTH];//arguments
		char temp3 [MAX_COMMAND_LENGTH];//special argument
		char tempCWD[MAX_COMMAND_LENGTH];//cwd
    //Set all arrays to 0
		bzero(temp, MAX_COMMAND_LENGTH);
		bzero(temp2, MAX_COMMAND_LENGTH);
		bzero(temp3, MAX_COMMAND_LENGTH);
		bzero(tempCWD, MAX_COMMAND_LENGTH);

		//put the name of the executable into temp
		strcpy(tempCWD,cwd);
		strcpy(temp,tempCWD);
		tokens = strtok(cmd->cmdstr, "/");
		tokens = strtok(NULL, "/");
	 	char* tokens2 = strtok(tokens, " ");
	 	strcat(temp,"/");
		strcat(temp,tokens2);

		//put arguments into temp2
		tokens2 = strtok(NULL, " ");
		while( (tokens2 != NULL) && (!special) ){
				//checks for >
				if (!strcmp(tokens2, ">")) {
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after >");
						return;
					}
					puts("> execution");
					greaterThan = true;
				}
				//checks for <
				else if(!strcmp(tokens2, "<")){
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after <");
						return;
					}
					puts("< execution");
					lessThan = true;
				}
				//checks for |
				else if(!strcmp(tokens2, "|")){
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after |");
						return;
					}
					puts("| execution");
					execPipe = true;
				}
				//adds arguments
				if(!special){
					if(moreArgs){
						strcat(temp2," ");
					}
					strcat(temp2, tokens2);
					tokens2 = strtok(NULL, " ");
					moreArgs = true;
				}
				//adds special character argument
				else{
					strcat(temp3, tokens2);
				}
		}

		tokens2 = strtok(NULL, " ");
		//If not null after a special character
		if( tokens2 != NULL) {
				puts("invalid syntax");
				return;
		}
		//make sure the executable exists
		if(access(temp, F_OK) == 0){
			if(!execPipe){
				pid_1 = fork();
				if (pid_1 == 0) {
					//> redirection
					if(greaterThan){
						strcat(tempCWD, "/");
						strcat(tempCWD, temp3);
						exec_greaterThan(temp, temp2, tempCWD, tokens);
					}
					//< redirection
					else if(lessThan){
						strcat(tempCWD, "/");
						strcat(tempCWD, temp3);
						exec_lessThan(temp, temp2, tempCWD, tokens);
					}
					//default execution
					else{
						exec_default(temp, temp2, tokens);
      			}
    			}
   			if ((waitpid(pid_1, &status, 0)) == -1) {
    			fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  				}
  			}
  			//For piping
  			else{
  			  int pfd1[2];
  				pipe(pfd1);

  				pid_1 = fork();
  				if (pid_1 == 0) {
  					close(pfd1[0]);
  					dup2(pfd1[1], STDOUT_FILENO);
  					exec_default(temp, temp2, tokens);
  				}

  				pid_2 = fork();
  				if (pid_2 == 0) {
  					close(pfd1[1]);
  					dup2(pfd1[0], STDIN_FILENO);
  					strcpy(temp, cwd);
  					strcat(temp, "/");
  					strcat(temp, temp3);
  					exec_default(temp, temp2, tokens);
  				}

    			if ((waitpid(pid_1, &status, 0)) == -1) {
    			fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  				}
    		}
    	}
    	else{
			puts("Executable does not exist in current working directory");
    	}
	}

	//Outside CWD, must use PATH
	else{
		bool ran = false; //boolean to determine if executable is found/run
		char temp [MAX_COMMAND_LENGTH];//copy of PATH
		char temp2 [MAX_COMMAND_LENGTH];//Current PATH attempting execution
		char temp3 [MAX_COMMAND_LENGTH];//special argument
		char tempArgs [MAX_COMMAND_LENGTH];//holds command arguments
		char tempCMD [MAX_COMMAND_LENGTH];//name of actual command
		char tempCWD [MAX_COMMAND_LENGTH];//copy of current working directory
		bzero(temp, MAX_COMMAND_LENGTH);
		bzero(temp2, MAX_COMMAND_LENGTH);
		bzero(tempArgs, MAX_COMMAND_LENGTH);
		bzero(tempCMD, MAX_COMMAND_LENGTH);
		bzero(tempCWD, MAX_COMMAND_LENGTH);

		//put arguments into tempArgs
		char* tokens2 = strtok(cmd->cmdstr, " ");
		strcpy(tempCMD, tokens2);
		tokens2 = strtok(NULL, " ");
		while( (tokens2 != NULL) && (!special) ){
				//checks for >
				if (!strcmp(tokens2, ">")) {
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after >");
						return;
					}
					puts("> execution");
					greaterThan = true;
				}

				//checks for <
				else if(!strcmp(tokens2, "<")){
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after <");
						return;
					}
					puts("< execution");
					lessThan = true;
				}

				//checks for |
				else if(!strcmp(tokens2, "|")){
					special = true;
					tokens2 = strtok(NULL, " ");
					if(tokens2 == NULL){
						puts("Missing argument after |");
						return;
					}
					puts("| execution");
					execPipe = true;
				}

				//adds arguments
				if(!special){
					if(moreArgs){
						strcat(tempArgs," ");
					}
					strcat(tempArgs, tokens2);
					tokens2 = strtok(NULL, " ");
					moreArgs = true;
				}

				//adds special character argument
				else{
					strcat(temp3, tokens2);
				}

		}
		tokens2 = strtok(NULL, " ");
		//If not null after a special character
		if( tokens2 != NULL) {
				puts("invalid syntax");
				return;
		}


		//temp has all the possible paths, tokens break it up
		strcpy(temp, path);
		tokens = strtok(temp, ":");

		//try to execute for all paths
		while( (tokens != NULL) && (!ran) ){
			strcpy(temp2, tokens);
			strcpy(tempCWD, tokens);
			strcat(temp2, tempCMD);

			//see if the executable exists for the current path
			if(access(temp2, F_OK) == 0){
				ran = true;

				//not piping
				if(!execPipe){

					pid_1 = fork();
					if (pid_1 == 0) {

						//> redirection
						if(greaterThan){
							strcat(tempCWD, temp3);
							exec_greaterThan(temp2, tempArgs, tempCWD, tempCMD);
						}
						//< redirection
						else if(lessThan){
							strcat(tempCWD, "/");
							strcat(tempCWD, temp3);
							exec_lessThan(temp2, tempArgs, tempCWD, tempCMD);
							ran = true;
						}
						//default execution
						else{
							exec_default(temp2, tempArgs, tempCMD);
      				}

    				}

    				if ((waitpid(pid_1, &status, 0)) == -1) {
    		 			fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  					}
  				}
  				//piping
				else{
					int pfd1[2];
  					pipe(pfd1);

  					pid_1 = fork();
  					if (pid_1 == 0) {
  						close(pfd1[0]);
  						dup2(pfd1[1], STDOUT_FILENO);
  						exec_default(temp2, tempArgs, tempCMD);
  					}

  					pid_2 = fork();
  					if (pid_2 == 0) {
  						close(pfd1[1]);
  						dup2(pfd1[0], STDIN_FILENO);

  						strcpy(temp2, tokens);
  						strcat(temp2, temp3);

  						//temp ARGS needs to be the output of first fork.
  						exec_default(temp2, tempArgs , tempCMD);
  					}

    				if ((waitpid(pid_1, &status, 0)) == -1) {
    					fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  					}
				}

			}
			tokens = strtok(NULL, ":");
		}
		//If none of the paths contained the executable.
		if(!ran){
			puts("Executable does not exist in PATH.");
		}

	}

}

/*******************************************************
*
*
* Helper Functions
*
*
*******************************************************/
//**************************************************************************
//change program to write output to file
//**************************************************************************

void exec_greaterThan(char* command, char* args, char* output, char* tokens){
	FILE *fp;
	fp = fopen(output, "w");

	dup2(fileno(fp), STDOUT_FILENO);
	//attemp to execute
	if ( (execl(command, command, args, (char *)0)) < 0) {
		fprintf(stderr, "\nError execing %s. ERROR#%d\n", tokens ,errno);
		fclose(fp);
   	return EXIT_FAILURE;
  	}
  	fclose(fp);
  	exit(0);
}

//**************************************************************************
//change program to read in text from file
//**************************************************************************
void exec_lessThan(char* command, char* args, char* output, char* tokens){
	FILE *fp;
	fp = fopen(output, "r");

	dup2(fileno(fp), STDIN_FILENO);
	//attempt to execute
	if ( (execl(command, command, args, (char *)0)) < 0) {
		fprintf(stderr, "\nError execing %s. ERROR#%d\n", tokens ,errno);
		fclose(fp);
   	return EXIT_FAILURE;
  	}
 	fclose(fp);
 	exit(0);
}

//**************************************************************************
//Output of first progrma becomes input of second
//**************************************************************************
void exec_pipe(char* command, char* args, char* output, char* tokens){
	if ( (execl(command, command, "-c", (char *)0)) < 0) {
		fprintf(stderr, "\nError execing %s. ERROR#%d\n", tokens ,errno);
   	return EXIT_FAILURE;
  	}
  	exit(0);
}
//**************************************************************************
//execute default executable
//**************************************************************************
void exec_default(char* command, char* args, char* tokens){
  puts(tokens);
	if ( (execl(command, command, args, (char *)0)) < 0) {
		fprintf(stderr, "\nError execing %s. ERROR#%d\n", tokens ,errno);
   	return EXIT_FAILURE;
  	}
  	exit(0);
}
