/*
 * shell.h
 *
 *  Created on: Nov 7, 2022
 *      Author: nicolas
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_

#include "main.h"

#define CMD_BUFFER_SIZE 64
#define MAX_ARGS 9
// LF = line feed, saut de ligne
#define ASCII_LF 0x0A
// CR = carriage return, retour chariot
#define ASCII_CR 0x0D
// DEL = delete
#define ASCII_DEL 0x7F
// BS = backspace
#define ASCII_BS 0x08



void shellInit(void);
void shellCompute(void);
void shellPrompt(void);
void shellCmdNotFound(void);
uint8_t shellGetChar(void);
void shellExec(void);

#endif /* INC_SHELL_H_ */
