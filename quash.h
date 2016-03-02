//*********************************************************
//@file quash.h
// 
//Quash essential functions and structures.
//
//*********************************************************

#ifndef QUASH_H
#define QUASH_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
//*****************************************************************************
//
// Specify the maximum number of characters accepted by the command string
//
//*****************************************************************************
#define MAX_COMMAND_LENGTH (1024)


//*****************************************************************************
//
//  Holds information about a command.
//
//*****************************************************************************
typedef struct command_t {
  char cmdstr[MAX_COMMAND_LENGTH]; ///< character buffer to store the
                                   ///< command string. You may want
                                   ///< to modify this to accept
                                   ///< arbitrarily long strings for
                                   ///< robustness.
  size_t cmdlen;                   ///< length of the cmdstr character buffer

  // Extend with more fields if needed
} command_t;

//*****************************************************************************
//
// Query if quash should accept more input or not.
// @return True if Quash should accept more input and false otherwise
//
//*****************************************************************************
bool is_running();

//*****************************************************************************
//
// Causes the execution loop to end.
//
//*****************************************************************************
void terminate();

/**
 *  Read in a command and setup the #command_t struct. Also perform some minor
 *  modifications to the string to remove trailing newline characters.
 *
 *  @param cmd - a command_t structure. The #command_t.cmdstr and
 *               #command_t.cmdlen fields will be modified
 *  @param in - an open file ready for reading
 *  @return True if able to fill #command_t.cmdstr and false otherwise
 */
bool get_command(command_t* cmd, FILE* in);

/**
 *  Read in a command and parse the input for executing.
 *
 *  @param cmd - a command_t structure.
 *  @return void
 */
void manager( command_t* cmd );

/**
 *  Changes current working directory of user. 
 *
 *  @param tokens - an absolute file path to go to. If NULL, current working directory goes home
 *  @return void
 */
void run_cd( char* tokens );

/**
 *  Set PATH to a new value
 *
 *  @param tokens - new value for PATH variable
 *  @return void
 */
void run_set( char* tokens );

/**
 *  Prints value for HOME or PATH variable,
 *
 *  @param tokens - string to be echoed
 *  @return void
 */
void run_echo( char* tokens );

/**
 *  Prints current working directory
 *
 *  @param none
 *  @return void
 */
void run_pwd();

/**
 * Print all of the currently running background processes in the format:[JOBID] PID COMMAND where JOBID is a
 * unique positive integer quash assigns
 * to the job to identify it, PID is the PID of the child process used for the job, and
 * COMMAND is the command used to invoke the job.
 *
 *  @param cmd - a command_t structure.
 *   
 *  @return void
 */
void run_jobs( command_t* cmd, char* tokens );


void run_exec( command_t* cmd, char* tokens );

//exec helper functions

void exec_greaterThan(char* command, char* args, char* output, char* tokens);

void exec_lessThan(char* command, char* args, char* output, char* tokens);

void exec_pipe(char* command, char* args, char* output, char* tokens);

void exec_default(char* command, char* args, char* tokens);




#endif // QUASH_H
