// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"

#define BUFFER_LENGTH 100

void increasePC() {
	int programCounter = machine->ReadRegister(PCReg);
	machine->WriteRegister(PrevPCReg, programCounter);
	programCounter = machine->ReadRegister(NextPCReg);
	machine->WriteRegister(PCReg, programCounter);
	machine->WriteRegister(NextPCReg, programCounter + 4);
}

int convertStringToInteger(char*a)
{
	int n = strlen(a);
	int minusCount = 0; 
	for (int i = 0; i < n; i++)
		if (!(('0' <= a[i] && a[i] <= '9') || (a[i] == '-' && minusCount++ == 0))) return 0;
 
	int q = atoi(a);
	return q;
}

//----------------------------------------------------------------------
// ExceptionHandler
// 	Entry point into the Nachos kernel.  Called when a user program
//	is executing, and either does a syscall, or generates an addressing
//	or arithmetic exception.
//
// 	For system calls, the following is the calling convention:
//
// 	system call code -- r2
//		arg1 -- r4
//		arg2 -- r5
//		arg3 -- r6
//		arg4 -- r7
//
//	The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//	"which" is the kind of exception.  The list of possible exceptions 
//	are in machine.h.
//----------------------------------------------------------------------

void
ExceptionHandler(ExceptionType which)
{
    int type = machine->ReadRegister(2);
	int data, i, arg2, arg1, tmp;
	char *buf = new char[BUFFER_LENGTH];
	buf[0] = '\0';
	static char bufStatic[BUFFER_LENGTH] = "";
	static int counter = 0;
    if (which == SyscallException/* && (type == SC_Halt)*/) {
		switch (type) {
			case SC_Halt:
				DEBUG('a', "Shutdown, initiated by user program.\n");
				interrupt->Halt();
				break;
			case SC_ReadInt:
				if (gSynchConsole->Read(buf, BUFFER_LENGTH - 1) != -1) {
					data = convertStringToInteger(buf);
					machine->WriteRegister(2, data);
				} else 
					machine->WriteRegister(2, 0);				
				increasePC();
				break;
			case SC_PrintInt:
				data = machine->ReadRegister(4);
				sprintf(buf, "%d", data);
				gSynchConsole->Write(buf, strlen(buf));
				increasePC();
				break;
			case SC_ReadChar:
				//Using static char to store buffer after system call
				
				//can't print -> read
				if (counter == strlen(bufStatic)) {
					gSynchConsole->Read(buf, BUFFER_LENGTH - 1);
					strcpy(bufStatic, buf);
					counter = 0;
				}			

				//can print -> print
				if (counter < strlen(bufStatic))
					machine->WriteRegister(2, bufStatic[counter++]);
				increasePC();
				break;
			case SC_PrintChar:
				data = machine->ReadRegister(4);
				sprintf(buf, "%c", char(data));
				gSynchConsole->Write(buf, 1);
				increasePC();
				break;
			case SC_ReadString:
				//read arg (bufID, len)
				arg1 = machine->ReadRegister(4);//buf 
				arg2 = machine->ReadRegister(5);//length
				i = 0;
				while (i < arg2) {		//max length
					tmp = min(BUFFER_LENGTH - 1, arg2 - i);		//length by reading
					data = gSynchConsole->Read(buf, tmp);
						
					machine->System2User(arg1, tmp, buf);
					i += tmp;			//now we read i					
					arg1 += tmp;			//increate virtual address will be stored
					
					if (data < tmp)		//pressed Enter
						break;
				}
				increasePC();
				break;
			case SC_PrintString:
				//read arg
				arg1 = machine->ReadRegister(4);//buf
				char *buffer;	//because user2system will make a new space!
				while ((buffer = machine->User2System(arg1, BUFFER_LENGTH - 1)) != NULL) {
					tmp = strlen(buffer);// the length of string;
					if (tmp == 0)	//empty string
						break;
					gSynchConsole->Write(buffer, tmp);
					arg1 += tmp;
					delete []buffer;
				}
				increasePC();
				break;
			default:
				increasePC();
				break;
		}
		
    } else if (which == NoException) {
		printf("Return to kernel");
	} else {
		printf("Unexpected user mode exception %d %d\n", which, type);
		ASSERT(FALSE);
    }
	delete []buf;
}
