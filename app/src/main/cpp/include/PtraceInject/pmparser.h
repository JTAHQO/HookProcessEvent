#pragma once

/*
 @Author	: ouadimjamal@gmail.com
 @date		: December 2015

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.  No representations are made about the suitability of this
software for any purpose.  It is provided "as is" without express or
implied warranty.

 */

#ifndef H_PMPARSER
#define H_PMPARSER
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/limits.h>

//maximum line length in a procmaps file
#define PROCMAPS_LINE_MAX_LENGTH  (PATH_MAX + 100) 

typedef struct procmaps_struct{
	void* addr_start; 	//< start address of the area
	void* addr_end; 	//< end address
	unsigned long length; //< size of the range

	char perm[5];		//< permissions rwxp
	short is_r;			//< rewrote of perm with short flags
	short is_w;
	short is_x;
	short is_p;

	long offset;	//< offset
	char dev[12];	//< dev major:minor
	int inode;		//< inode of the file that backs the area

	char pathname[600];		//< the path of the file that backs the area
	//chained list
	struct procmaps_struct* next;		//<handler of the chinaed list
} procmaps_struct;

typedef struct procmaps_iterator{
	procmaps_struct* head;
	procmaps_struct* current;
} procmaps_iterator;

procmaps_iterator* pmparser_parse(int pid);

procmaps_struct* pmparser_next(procmaps_iterator* p_procmaps_it);

void pmparser_free(procmaps_iterator* p_procmaps_it);

void _pmparser_split_line(char*buf,char*addr1,char*addr2,char*perm, char* offset, char* device,char*inode,char* pathname);

void pmparser_print(procmaps_struct* map,int order);





#endif
