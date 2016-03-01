/**
 * @file quash.c
 *
 * Quash's main file
 * Dylan Dreiling
 * Hayden Kaustinen
 */

/**************************************************************************
 * Included Files
 **************************************************************************/ 
#include "quash.h" // Putting this above the other includes allows us to ensure
                   // this file's header's #include statements are self
                   // contained.

#include <string.h>
#include <errno.h>

/**************************************************************************
 * Private Variables
 **************************************************************************/
/**
 * Keep track of whether Quash should request another command or not.
 */
// NOTE: "static" causes the "running" variable to only be declared in this
// compilation unit (this file and all files that include it). This is similar
// to private in other languages.
static bool running;

char home[MAX_COMMAND_LENGTH]; //$HOME variable
char path[MAX_COMMAND_LENGTH]; //#PATH variable
char cwd[MAX_COMMAND_LENGTH]; //current working directory

char* token;  //pointer to token in a given string, tokens are substrings delimted by second arg of strtok()
char *getcwd(char *buf, size_t size);

int status; //process status
int pid_1; //first child process


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
int main(int argc, char** argv) { 
  command_t cmd; //< Command holder argument
  
  //initialize variables.  
  strcpy(home, "/home/");
  strcpy(path, "/home/:/home/hkaustin/EECS_678/project1-quash/quash/Quash/");
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
char * pch;
//function to parse/manage/execute commands
void manager(command_t* cmd ){ 

	 char* temp [MAX_COMMAND_LENGTH];
	 strcpy(temp, cmd->cmdstr);
	 char* tokens = strtok(temp, " ");
	 
	 //cd if the first two chars are
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

//function to execute cd
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

//function to execute set

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

//function to execute echo
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

//function to execute pwd
void run_pwd( char* tokens  ){
	
   if (getcwd(cwd, sizeof(cwd)) != NULL){
   	fprintf(stdout, "Current working dir: %s/\n", cwd);
   	}	
   else{
   		perror("getcwd() error");
   	}
}

//function to execute jobs
void run_jobs( command_t* cmd, char* tokens  ){
	puts("jobs function");
}

//function to execute and executable
void run_exec( command_t* cmd, char* tokens ){
	puts("exec function");

	//inside cwd
	if( !strncmp(cmd->cmdstr, "./", 2) ){
		puts("DONT USE PATH!");
		char temp [MAX_COMMAND_LENGTH];
		char temp2 [MAX_COMMAND_LENGTH];
		
		//put the name of the executable into temp
		strcpy(temp,cwd);
		tokens = strtok(cmd->cmdstr, "/");
		tokens = strtok(NULL, "/");
	 	char* tokens2 = strtok(tokens, " ");
	 	strcat(temp,"/");
		strcat(temp,tokens2);
		
		//put arguments into temp2
		bzero(temp2, MAX_COMMAND_LENGTH);
		tokens2 = strtok(NULL, " ");		
		while(tokens2 != NULL){
				strcat(temp2, tokens2);
				strcat(temp2," ");
				tokens2 = strtok(NULL, " ");		
		}
		puts(temp2);
		
		
		pid_1 = fork(); 
		if (pid_1 == 0) {
			/* First Child */ 
			if ( (execl(temp, temp, temp2, (char *)0)) < 0) {
		     if(errno == 2){
		     		fprintf(stderr, "\nError execing %s. NOT FOUND", tokens);
		     }
		     else{
		     		fprintf(stderr, "\nError execing %s. ERROR#%d\n", tokens ,errno);
 	        		
		     }
 	        exit(0);
           return EXIT_FAILURE;
         }
    	}
    	
   	if ((waitpid(pid_1, &status, 0)) == -1) { 		
    		fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  		}
    	
    	
	}
	
	//outside cwd
	else{
		bool ran = false; //boolean to determine if executable is found/run
		puts("USE PATH!");
		char temp [MAX_COMMAND_LENGTH];
		char temp2 [MAX_COMMAND_LENGTH];
		char tempArgs [MAX_COMMAND_LENGTH];
		char tempCmd [MAX_COMMAND_LENGTH];
		
		
		//put arguments into tempArgs
		char* tokens2 = strtok(cmd->cmdstr, " ");
		strcpy(tempCmd, tokens2);
		bzero(tempArgs, MAX_COMMAND_LENGTH);
		tokens2 = strtok(NULL, " ");		
		while(tokens2 != NULL){
				strcat(tempArgs, tokens2);
				strcat(tempArgs," ");
				tokens2 = strtok(NULL, " ");		
		}
		puts(tempArgs);
		
		
		//temp has all the possible paths, tokens break it up
		strcpy(temp, path);
		tokens = strtok(temp, ":");
		
		//try to execute for all paths
		while(tokens != NULL){
			strcpy(temp2, tokens);
			strcat(temp2, tempCmd);
			puts(temp2);
			
			pid_1 = fork(); 
			if (pid_1 == 0) {
				// First Child 
				if ( (execl(temp2, temp2, tempArgs,( char *)0)) < 0) {
 	        	fprintf(stderr, "\nError execing USE PATH. ERROR#%d\n", errno);
			  	exit(0);           
           	return EXIT_FAILURE;
           
         	}
    		}
    		
    		if ((waitpid(pid_1, &status, 0)) == -1) {   		
    		 	fprintf(stderr, "Process 1 encountered an error. ERROR%d", errno);
  			}		
			tokens = strtok(NULL, ":");
						
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







