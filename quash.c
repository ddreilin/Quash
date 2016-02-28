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

//function to parse/manage/execute commands
void manager(command_t* cmd ){ 
	 
	 //cd if the first two chars are "cd"
	 if (!strncmp(cmd->cmdstr, "cd", 2)){
	 	run_cd( cmd );
	 }
	 
	 //set 
	 else if (!strncmp(cmd->cmdstr, "set", 3)){
	 	run_set( cmd );
	 }			
	 
	 //echo
	 else if (!strncmp(cmd->cmdstr, "echo", 4)){
	 	run_echo( cmd );
	 }
	 
	 //pwd
	 else if (!strncmp(cmd->cmdstr, "pwd", 3)){ 	
	 	run_pwd( cmd );
	 }
	 
	 //jobs
	 else if (!strncmp(cmd->cmdstr, "jobs", 4)){
	 	run_jobs( cmd );
	 }
	
	 //exit command
	 else if (!strncmp(cmd->cmdstr, "exit", 4) || !strncmp(cmd->cmdstr, "quit", 4) )
      terminate(); // Exit Quash
      
    //run an executable 
    else 
      puts(cmd->cmdstr); // Echo the input string
}

//function to execute cd
void run_cd( command_t* cmd ){
	puts("cd function");
}

//function to execute set
void run_set( command_t* cmd ){
	puts("set function");
	
	//PATH variable
	if (!strncmp(cmd->cmdstr, "set PATH=", 9)){
		puts("Setting PATH variable");	
		strcpy(path, cmd->cmdstr);//need to cut off first 9
	}
	
	//HOME Variable
	else if (!strncmp(cmd->cmdstr, "set HOME=", 9)){
		puts("Setting HOME variable");
		strcpy(home, cmd->cmdstr); //need to cut off first 9
			
	}
	
	//default
	else{
		puts("Unknown variable");	
	}
		
}

//function to execute echo
void run_echo( command_t* cmd ){
	puts("echo function");
	
	//PATH variable
	if (!strncmp(cmd->cmdstr, "echo $PATH", 10)){
		puts(path);	
	}
	
	//HOME Variable
	else if (!strncmp(cmd->cmdstr, "echo $HOME", 10)){
		puts(home);
			
	}
	
	//default
	else{
		puts("Unknown variable");	
	}
	
}

//function to execute pwd
void run_pwd( command_t* cmd ){
	puts("pwd function");
}

//function to execute jobs
void run_jobs( command_t* cmd ){
	puts("jobs function");
}


