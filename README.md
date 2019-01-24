# AbstractVM

AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.

The assembly language

Example
As an example is still better that all the possible explanations in the world, this is an
example of an assembly program that the machine is able to compute:

Before you test the programme, run the command line: "make re", the programme will create an executable file called avm. You can follow the steps bellow to test the example bellow:

1 ; -------------
2 ; ./avm
3 ; -------------
4
5 push int32(42)
6 push int32(33)
7
8 add
9
10 push float(44.55)
11
12 mul
13
14 push double(42.42)
15 push int32(42)
16
17 dump
18
19 pop
20
21 assert double(42.42)
22
23 exit

Description
As for any assembly language, the language of AbstractVM is composed of a series of
instructions, with one instruction per line. However, AbstractVM’s assembly language
has a limited type system, which is a major difference from other real world assembly
languages.
• Comments: Comments start with a ’;’ and finish with a newline. A comment can
be either at the start of a line, or after an instruction.
• push v: Pushes the value v at the top of the stack. The value v must have one of
the following form:
◦ int8(n) : Creates an 8-bit integer with value n.
◦ int16(n) : Creates a 16-bit integer with value n.
◦ int32(n) : Creates a 32-bit integer with value n.
◦ float(z) : Creates a float with value z.
◦ double(z) : Creates a double with value z.
• pop: Unstacks the value from the top of the stack. If the stack is empty, the
program execution must stop with an error.
• dump: Displays each value of the stack, from the most recent one to the oldest
one WITHOUT CHANGING the stack. Each value is separated from the next one
by a newline.
• assert v: Asserts that the value at the top of the stack is equal to the one passed
as parameter for this instruction. If it is not the case, the program execution must
stop with an error. The value v has the same form that those passed as parameters
to the instruction push.
• add: Unstacks the first two values on the stack, adds them together and stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.
• sub: Unstacks the first two values on the stack, subtracts them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.
• mul: Unstacks the first two values on the stack, multiplies them, then stacks the
result. If the number of values on the stack is strictly inferior to 2, the program
execution must stop with an error.
• div: Unstacks the first two values on the stack, divides them, then stacks the result.
If the number of values on the stack is strictly inferior to 2, the program execution
must stop with an error. Moreover, if the divisor is equal to 0, the program execution
must stop with an error too. Chatting about floating point values is relevant a this
point. If you don’t understand why, some will understand. The linked question is
an open one, there’s no definitive answer.
• mod: Unstacks the first two values on the stack, calculates the modulus, then
stacks the result. If the number of values on the stack is strictly inferior to 2, the
program execution must stop with an error. Moreover, if the divisor is equal to 0,
the program execution must stop with an error too. Same note as above about fp
values.
• print: Asserts that the value at the top of the stack is an 8-bit integer. (If not,
see the instruction assert), then interprets it as an ASCII value and displays the
corresponding character on the standard output.
• exit: Terminate the execution of the current program. If this instruction does not
appears while all others instruction has been processed, the execution must stop
with an error.

When a computation involves two operands of different types, the value returned has
the type of the more precise operand. Please do note that because of the extensibility of
the machine, the precision question is not a trivial one. This is covered more in details
later in this document.

Grammar
The assembly language of AbstractVM is generated from the following grammar (# corresponds to the end of the input, not to the character ’#’):
1 S := INSTR [SEP INSTR]* #
2
3 INSTR :=
4 push VALUE
5 | pop
6 | dump
7 | assert VALUE
8 | add
9 | sub
10 | mul
11 | div
12 | mod
13 | print
14 | exit
15
16 VALUE :=
17 int8(N)
18 | int16(N)
19 | int32(N)
20 | float(Z)
21 | double(Z)
22
23 N := [-]?[0..9]+
24
25 Z := [-]?[0..9]+.[0..9]+
26
27 SEP := '\n'+

Errors
When one of the following cases is encountered, AbstractVM will raise an exception
and stop the execution of the program cleanly. It is forbidden to raise scalar exceptions.
Moreover the exception classes inherit from std::exception.
• The assembly program includes one or several lexical errors or syntactic errors.
• An instruction is unknown
• Overflow on a value
• Underflow on a value
• Instruction pop on an empty stack
• Division/modulo by 0
• The program doesn’t have an exit instruction
• An assert instruction is not true
• The stack is composed of strictly less that two values when an arithmetic instruction
is executed.
Perhaps there are more errors cases. However, the machine will never crash (segfault,
bus error, infinite loop, unhandled exception, ...).

Execution
The machine is able to run programs from a file passed as a parameter and from
the standard input. When reading from the standard input, the end of the program is
indicated by the special symbol ";;" otherwise absent.

Now let see some examples of execution:
1 $>./avm
2 push int32(2)
3 push int32(3)
4 add
5 assert int32(5)
6 dump
7 exit
8 ;;
9 5
10 $>
1 $>cat sample.avm
2 ; -------------
3 ; sample.avm -
4 ; -------------
5
6 push int32(42)
7 push int32(33)
8 add
9 push float(44.55)
10 mul
11 push double(42.42)
12 push int32(42)
13 dump
14 pop
15 assert double(42.42)
16 exit
17 $>./avm ./sample.avm
18 42
19 42.42
20 3341.25
21 $>
1 $>./avm
2 pop
3 ;;
4 Line 1 : Error : Pop on empty stack
5 $>
