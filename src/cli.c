#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <libgen.h>

#include "mmc.h"
#include "utils.h"
#include "mmc_context.h"

const char* usage = "ccm [-i INPUT_PATH]\n";

void exitBadArg(){
	printf("ERROR: Bad arguments.\n");
	printf("%s", usage);
	exit(1);
}

void exitErr(const char* msg){
	printf("ERROR: %s\n", msg);
	exit(1);
}

char* getArg(int i, int argc, char **argv){
	if(i>=argc) exitBadArg();
	return argv[i];
}

int main(int argc, char **argv){

	MmcContext ctx;
	initMmcContext(&ctx);

	for(int i=0; i<argc; ++i){
		const char* arg = argv[i];
		if(streq("-i", arg) || streq("--input", arg)){
			strcpy(ctx.inputPath, getArg(++i, argc, argv));
		}
		if(streq("-o", arg) || streq("--output", arg)){
			strcpy(ctx.outputPath, getArg(++i, argc, argv));
		}
		if(streq("--overwrite", arg)){
			ctx.outputMode = MMC_OUTPUT_MODE_OVERWRITE;
		}
		if(streq("--img-min-length", arg)){
			ctx.imgMinLength = atoi(arg);
		}
	}

	bool res = MmcCompress(&ctx);

	return res ? 0 : 1;
}