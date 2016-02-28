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
char home[MAX_COMMAND_LENGTH];
char path[MAX_COMMAND_LENGTH];
char* token;
char *getcwd(char *buf, size_t size);


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
  strcpy(home, "/home");  
  
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

	
	 char* tokens = strtok(cmd->cmdstr, " ");

	 
	 //cd if the first two chars are
	 if (!strcmp(tokens, "cd")){
	 	run_cd( cmd, tokens );
	 }
	 
	 //set 
	 else if (!strcmp(tokens, "set")){
	 	run_set( cmd, tokens);
	 }			
	 
	 //echo
	 else if (!strcmp(tokens, "echo")){
	 	run_echo( cmd, tokens );
	 }
	 
	 //pwd
	 else if (!strcmp(tokens, "pwd")){ 	
	 	run_pwd( cmd, tokens );
	 }
	 
	 //jobs
	 else if (!strcmp(tokens, "jobs")){
	 	run_jobs( cmd, tokens );
	 }
	
	 //exit command
	 else if (!strcmp(tokens, "exit") || !strcmp(tokens, "quit") )
      terminate(); // Exit Quash
      
    //run an executable 
    else 
      puts(cmd->cmdstr); // Echo the input string
}


/*******************************************************
*
*
* Run Command functions
*
*
*******************************************************/

//function to execute cd
void run_cd( command_t* cmd, char* tokens ){
	puts("cd function");
	tokens = strtok(NULL, "/");
	
	//go to home
	if(tokens == NULL){
		chdir(home);
	      
	}
	
	//argument given, watch for bad input?
	else{
		char temp [MAX_COMMAND_LENGTH];
		temp[0]='\0';
		
		while(tokens != NULL){
				strcat(temp,"/");
				strcat(temp, tokens);
				tokens = strtok(NULL, "/");		
		}
		chdir(temp);	
	}	
	
	
}

//function to execute set

void run_set( command_t* cmd, char* tokens ){
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
void run_echo( command_t* cmd, char* tokens){
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
void run_pwd( command_t* cmd, char* tokens  ){
	
	char cwd[1024];
   if (getcwd(cwd, sizeof(cwd)) != NULL){
   	//fprintf(stdout, "Current working dir: %s\n", cwd);
   	}	
   else{
   		perror("getcwd() error");
   	}
  fprintf(stdout, "Current working dir: %s\n", cwd);
}

//function to execute jobs
void run_jobs( command_t* cmd, char* tokens  ){
	puts("jobs function");
}

/*******************************************************
*
*
* Helper Functions
*
*
*******************************************************/
