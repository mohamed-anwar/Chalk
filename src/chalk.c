#include "include/system.h"
#include "parser.c"
#include "runtime.c"
#include "repl.c"

#define CHALK_VERSION "Chalk VM version : 0.0.1 (Pre-Alpha)"

void print_message () {
  	fprintf(stderr,
  	"usage: chalk filename [options].  Available options are:\n"
  	"  -c [file]  compile only\n"
  	"  -o [file]  specify output file (default chalk.out)\n"
  	"  -i       	interactive shell (Not fully implemented)\n" 
  	"  -v       	print version information\n" 
	);
  	chalk_exit();
}

void print_version (void) {
  	printf("%s\n" , CHALK_VERSION);	/* Notice that the version is a string and not just a number */
	chalk_exit();
}

char * out_error()
{
	print_message();
	return NULL;
}

int main(int argc , char * argv[])
{
	//repl();
	//chalk_exit();

	//printf("int = %ld , long = %ld , double = %ld , long double = %ld\n" , sizeof(int) , sizeof(long) , sizeof(double) , sizeof(long double) );

	if(argc < 2) print_message();
	int i , compile = 0;
	char * input = NULL;
	char * output = "chalk.out";
	for(i = 1 ; i < argc ; i++ )
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1])
			{
				case 'c': compile = 1; continue; 
				case 'o': output = (argc-i)?argv[++i]:out_error(); continue;
				case 'v': print_version();
				case 'i': repl();
				default : print_message();
			}
		}
		if(!input)
		{ 
			input = argv[i];
			continue;
		}
		print_message();
	}
	
	/* Checking if binary file */ 
    {
    	FILE * in = fopen(input , "r");
    	char src[4];
    	fread(src , 4 , 1 , in);
    	fclose(in);
    	if(check_header(src))
    	{
            char * in_file = open_file(input);
    		launch_exec(in_file);
            terminate_exec();
            free(in_file);
    		chalk_exit();
    	}
    }

    parse_return executable = parse_file(argv[1]);
    if(compile)
    {
    	str_table_t * str_table = encode_str_table(Strings);
    	char header[] = { 'C' , 'H' , 'K' , 0x21 };
    	FILE * out = fopen( output , "w");
    	fwrite( &header , 4 , 1 , out);
    	int inst_size = executable.inst_count * 10;
    	fwrite( &inst_size , sizeof(int) , 1 , out);
    	fwrite( &executable.globals->count , sizeof(int) , 1 , out);
    	fwrite( chunk_buf , inst_count*10 , 1 , out);
    	fwrite( str_table->slots , (Strings->count + 1) * sizeof(int) , 1 , out);
    	fwrite( str_table->str , strlen(str_table->str) , 1 , out);
    	int file_size = ftell(out);
    	fwrite( &file_size , sizeof(int) , 1 , out);
    	fclose(out);
    	chalk_exit();
    }

    launch(executable.src , executable.globals_count , executable.strings , executable.globals);
    chalk_exit();
    return 0;
}