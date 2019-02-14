# Thompson VM Lexer #
This lexer tokenizes input for a simple language that consists of 4 types of instructions:
+ `CHAR`
+ `MATCH`
+ `SPLIT`
+ `JMP`

## Specificatons ##
The lexical analysis engine:
1. Matches prefixes of the input.
2. Matches multiple patterns at once.
3. Picks the pattern that matches the longest prefix.
4. Breaks ties by picking the pattern that appears earliest in the user supplied list of patterns.

## Input ##
The engine accepts input in a precompiled NFA Program format.

Each line in the NFA program has the following format:
`INSTRUCTION-INDEX OP-CODE [OPERAND-A [OPERAND-B]]`

The lines in the program are delimited by `\n` and the field of the instructions are delimited by a space `" '`.

### Op Codes ##

1.  `CHAR` takes two operands: the start of the character range, the end of the
    character range (inclusive). The operands are given as the ascii decimal
    encoding of the character.

    eg. `1 CHAR 97 97` Matches `a`

    eg. `1 CHAR 97 98` Matches `a` or `b`

    In this way, the CHAR operand could really be called CHARRANGE. But, CHAR is
    shorter and having a single operand CHAR operator is redundant.

2.  `JMP` takes one operand: the instruction index of the jump target.

    eg. `7 JMP 5`

3.  `SPLIT` takes two operands: the instruction indices of the jump targets.

    eg. `5 SPLIT 6 8`

4.  `MATCH` takes no operands.

## Where is the Source Code ##
The source code for the lexer can be found in directory `kalesh-pr01`.

You can change into this directory by running the following command:

`cd /home/codio/workspace/kalesh-pr01`

*NOTE:* The commands for comipling and running the lexer and the tests expect that you are in this working directory.

## Compiling the Lexer ##

To compile the engine, run the `make` command from your shell.

## Running Unit Tests ##

The unit tests for this lexer require the Google Test framework.

On Linux environments the framework can be setup by running the `test_setup.sh` script, by running the following commands:
```bash
chmod +x test_setup.sh
sh test_setup.sh
```

The tests can be compiled and executed with the following commands:
```bash
make tests
./tests
```

## Running the Student Grader ##

Once the lexer has been compiled the student grader can be run using command:

`bin/student-grader ./pr01`

from the `kalesh-pr01` directory.

## Running the program ##

The lexer can be run be running the following command:

`./pr01 [NFA program pathname`

in which case the string to be parsed is expected from the keyboard.


A nicer way of automating the input is to run the lexer as follow:

`cat [InputString.txt] | ./pr01 [NFA program pathname]`

in this case the lexer expects an extra piece of input - the pathname of the file containing the string to be tokenized.




