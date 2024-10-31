The repository contains a simple .vtt file parser.

This parser will remove all timestamps except for when a new speaker begins talking. The only timestamps printed are the times when a new speaker begins talking. Also, it will remove all newlines from between lines of text when the speaker has not changed.

REQUIREMENTS

exactly 4 command line arguments are required to operate this parser.

./parser <transcript_file_name> <output_file_name> <name_file>

the ./parser is the executable of the code. This can be produced by typing make all into the command line. I have attached the EECS 281 makefile in this repository that I have already set up to properly make all
required files.

<transcript_file_name> is what it sounds like. It is the desired .vtt file transcript we are going to parse.

<output_file_name> is also what it sounds like. It is the desired .txt file where the parsed transcript will be printed out.

<name_file> this is less clear. So far the only way I have found to make this work is to have the names of all speakers input into a seperate .txt file. So take all the different names from the .vtt file. 
From my observations so far there are normally only 5 or 6 participants in these talks. The name file should be of the following form 

namecode1  

namecode2 

namecode3 

ect.

each name must be seperated by a newline in order for this to work properly. Names cannot all be on the same line


Also, the exact order in which I presented the files on the command line must be maintained. You cannot have a command line of the form ./parser <output_file_name> <transcript_file_name> <name_file>
this is an illegal command line and the script will not run as it was designed to do. 

BEGINING OPERATION

In order to begin utilizing this reposotory just clone it on the command line and perform the operations above as described. 

I will provide more information on operation and desgin of this script in our next meeting as a team.


Gavin Lauer :)
