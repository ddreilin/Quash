/**
 * @file quash.h
 *
 * EECS 678 - Project 1
 * Dylan Dreiling
 * Hayden Kaustinen
 *
 * Quash essential functions and structures.
 *
 */

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
  char cmdstr[MAX_COMMAND_LENGTH]; ///< character buffer to store the command string
  size_t cmdlen;                   ///< length of the cmdstr character buffer
  // Extend with more fields if needed
} command_t;

//*****************************************************************************
//
// Query if quash should accept more input or not.
// @param None.
// @return True if Quash should accept more input and false otherwise
//
//*****************************************************************************
bool is_running();

//*****************************************************************************
//
// Sets status of job (bool running) to false
// @param None.
// @return None.
//
//*****************************************************************************
void terminate();

/**
 *  Read in a command and setup the #command_t struct. Also perform some minor
 *  modifications to the string to remove trailing newline characters.
 *
 *  @param cmd A command_t structure. The #command_t.cmdstr and
 *               #command_t.cmdlen fields will be modified
 *  @param in An open file ready for reading
 *  @return True if able to fill #command_t.cmdstr and false otherwise
 */
bool get_command(command_t* cmd, FILE* in);

/**
 *  Read in a command and parse the input for executing.
 *
 *  @param cmd A command_t structure.
 *  @return None
 */
void manager( command_t* cmd );

/**
 *  Changes current working directory of user.
 *
 *  @param tokens An absolute file path to go to. If NULL, current working directory goes home
 *  @return void
 */
void run_cd( char* tokens );

/**
 *  Set PATH to a new value
 *
 *  @param tokens New value for PATH variable
 *  @return None
 */
void run_set( char* tokens );

/**
 *  Prints value for HOME or PATH variable,
 *
 *  @param tokens String to be echoed
 *  @return void
 */
void run_echo( char* tokens );

/**
 *  Prints current working directory
 *
 *  @param None.
 *  @return None.
 */
void run_pwd();

/**
 * Print all of the currently running background processes in the format:[JOBID] PID COMMAND where JOBID is a
 * unique positive integer quash assigns
 * to the job to identify it, PID is the PID of the child process used for the job, and
 * COMMAND is the command used to invoke the job.
 *
 *  @param None.
 *
 *  @return None.
 */
void run_jobs();

/**
 * Print all of the currently running background processes in the format:[JOBID] PID COMMAND where JOBID is a
 * unique positive integer quash assigns
 * to the job to identify it, PID is the PID of the child process used for the job, and
 * COMMAND is the command used to invoke the job.
 *
 *  @param cmd A command_t structure
 *  @param tokens A token
 *
 *  @return void
 */
void run_exec( command_t* cmd, char* tokens );

/**
 *  Run executable such that the output of the program is written to a file
 *
 *  @param cmd A command_t structure
 *  @param args Arguments for executeable
 *  @param output Output of program
 *  @param tokens A token
 *
 *  @return void
 */
void exec_greaterThan(char* command, char* args, char* output, char* tokens);

/**
 *  Run executable such that the input of the program is read from a file
 *
 *  @param cmd A command_t structure
 *  @param args Arguments for executeable
 *  @param output Output of program
 *  @param tokens Token
 *
 *  @return void
 */
void exec_lessThan(char* command, char* args, char* output, char* tokens);


/**
 *  Run executable such that the output of the first program is the argruments
 *  for the second executable.
 *
 *  @param cmd - a command_t structure
 *  @param args Arguments for executeable
 *  @param output Output of program
 *  @param tokens A token
 *
 *  @return void
 */
void exec_default(char* command, char* args, char* tokens);

#endif // QUASH_H
