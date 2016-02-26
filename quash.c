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
                   // this file's headder's #include statements are self
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

	 //parse until white space, to get command

	 //cd if the first two chars are "cd"
	 if (!strcmp(cmd->cmdstr, "cd")){
	 	run_cd( &cmd );
	 }
	 
	 //set 
	 else if (!strcmp(cmd->cmdstr, "set")){
	 	run_set( &cmd );
	 }			
	 
	 //echo
	 else if (!strcmp(cmd->cmdstr, "echo")){
	 	run_echo( &cmd );
	 }
	 
	 //pwd
	 else if (!strcmp(cmd->cmdstr, "pwd")){ 	
	 	run_pwd( &cmd );
	 }
	 
	 //jobs
	 else if (!strcmp(cmd->cmdstr, "jobs")){
	 	run_jobs( &cmd );
	 }
	
	 //exit command
	 else if (!strcmp(cmd->cmdstr, "exit") || !strcmp(cmd->cmdstr, "quit") )
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
	puts("set funciton");	
}

//function to execute echo
void run_echo( command_t* cmd ){
	puts("echo funciton");
}

//function to execute pwd
void run_pwd( command_t* cmd ){
	puts("pwd funciton");
}

//function to execute jobs
void run_jobs( command_t* cmd ){
	puts("jobs funciton");
}