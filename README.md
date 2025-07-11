The repository contains a simple .vtt file parser.

This parser will remove all timestamps except for when a new speaker begins talking. The only timestamps printed are the times when a new speaker begins talking. Also, it will remove all newlines from between lines of text when the speaker has not changed.

COMPILATION

The script does not come with an already prepared executable you must compile it on your own or recompile after changes to the code. 

I have attached the standard EECS 281 makefile to make this process easier. At the command line all you need to do is type

make all

this will compile multiple forms of the execuatble parser_profile, parser_valgrind, parser_debug, and parser. The profile and valgrind version are not important and can be deleted after compilation. The debug executable must be used if you are looking to debug the code after an update or change. For all normal purposes the standard parser executable will be used when using the code to clean files.



There are two poosible modes that can be executed either manual mode or automatic mode


MANUAL MODE

This mode can be used when you want to process a single file. First you must place the unprocessed .vtt file into the main directory containing the parsing script. Then input the following commands into the command line in the terminal. 

./parser -m [filename]

you can also use 

./parser --manual [filename] 

for the same results

When this command is executed it will automatically create an output directory title output if one with that name does not already exist. The parsed file will then be put into the created output directory and can then be moved into a seperate document for later revision.


AUTOMATIC MODE

For automatic mode you can parse mutliple files at one time. First place all unprocessed .vtt files into a subfolder of the main directory. This can be named anything but do not name it output this will cause issues after processing of the files if it is named this way. Also, make sure that the given folder contains no spaces in the name. This will cause issues and might not properly work when executed. Input the following commands into the terminal to being the parsing

/.parser -a

you can also use

./parser --auto

When this command is executed you will then be prompted to enter the name of the directory that contains the unprocessed files. Input the name of the directory and then the processing will begin. After this all processed files will be placed into an output folder that will be created if one does not exist yet. The initial folder that contained the unprocessed files can then be deleted and the completed files can be moved for later revision. 


HELP MODE

If any issues arise and you need a refresher on the proper commands to input just type in the command line 

./parser -h or ./parser --help

This will display a simple message that gives basic understanding of how to execute the desired mode. 

OUPUT MODE

If you desire to change the name of the output directory from output you can 

