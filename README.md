# Lab-1
You are to implement a two-pass linker and submit the source code, which we will compile and run. Please do not submit inputs or outputs. Your program must take one input parameter which will be the name of an input file to be processed. 
All output should go to standard output. The languages of choice for this first lab are C/C++ only. Note, when you work on linserv1 the default GCC/G++ compiler is v4.4.7. 
We realize you code on your own machine and transferring to linserv1 machine exposes occasionally some linker errors. In that case use static linking (such as not finding the appropriate libraries at runtime), though hopefully that is now resolved with the “module” approach discussed at the end.

In general, a linker takes individually compiled code/object modules and creates a single executable by resolving external symbol references (e.g. variables and functions) and module relative addressing by assigning global addresses after placing the modules’ object code at global addresses.

The input to the linker is a file containing a sequence of tokens (symbols and integers and instruction type characters). Don’t assume tokens that make up a section to be on one line, don’t make assumptions about how much space separates tokens or that lines are non-empty for that matter or that each input conforms syntactically. Symbols always begin with alpha characters followed by optional alphanumerical characters, i.e.[a-Z][a-Z0-9]*. Valid symbols can be up to 16 characters. Integers are decimal based. Instruction type characters are (I, A, R, E). Token delimiters are ‘ ‘, ‘\t’ or ‘\n’.

The input file to the linker is structured as a series of “object module” definitions.
Each “object module” definition contains three parts (in fixed order): definition list, use list, and program text.

1.definition list consists of a count defcount followed by defcount pairs (S, R) where S is the symbol being defined and R is the relative word address (offset) to which the symbol refers in the module.

2.use list consists of a count usecount followed by usecount symbols that are referred to in this module. These could include symbols defined in the definition list of any module (prior or subsequent or not at all).

3.program text consists of a count codecount followed by codecount pairs (type, instr), where instr is an upto 4-digit instruction (integer) and type is a single character indicating Immediate, Absolute, Relative, or External. codecount is thus the length of the module.

An instruction is composed of an integer that is separated into an opcode (op/1000) and an operand (op mod 1000). The opcode always remains unchanged by the linker. (Since the instruction value is supposed to be 4 or less digits, read an integer and ensure opcode < 10, see errorcodes below). The operand is modified/retained based on the instruction type in the program text as follows:

(I) an immediate operand is unchanged;

(A) operand is an absolute address which will never be changed in pass2; however it can’t be “>=” the machine size (512); 

(R) operand is a relative address which is relocated by replacing the relative address with the absolute address of that relative address after the modules global address has been determined.

(E) operand is an external address which is represented as an index into the uselist. For example, a reference in the program text with operand K represents the Kth symbol in the use list, using 0-based counting, e.g., if the use list is ‘‘2 f g’’, then an instruction ‘‘E 7000’’ refers to f, and an instruction ‘‘E 5001’’ refers to g. You must identify to which global address the symbol is assigned and then replace the address.

The linker must process the input twice (that is why it is called two-pass).Pass One parses the input and verifies the correct syntax and determines the base address for each module and the absolute address for each defined symbol, storing the latter in a symbol table. The first module has base address zero; the base address for module X+1 is equal to the base address of module X plus the length of module X. The absolute address for symbol S defined in module M is the base address of M plus the relative address of S within M. After
pass one print the symbol table (including errors related to it (see rule2 later)). Do not store parsed tokens, only store meta data (e.g. deflist, uselist, num-instructions) and of course the symboltable.

Pass Two again parses the input and uses the base addresses and the symbol table entries created in pass one to generate the actual output by relocating relative addresses and resolving external references.
You must clearly mark your two passes in the code through comments and/or proper function naming.

To start off, write a token parser that simply parses the input, prints the token and the position in the file found and finally prints the final position in the file (as you will need that for error reporting) and verify it correctly recognizes tokens and line and lineoffsets. The functions you need to study for this are getline() or fgets() (reads a full line into a buffer) or C++ equivalent and strtok(), which tokenizes input buffers. Please use Linux’s build in help : “man strtok” and understand how a new line is seeded and continued in subsequent calls.
Once you have the getToken() function written, then layer the readInt(), readSymbol() , readIAER() functions on top of it and build your real parser. Once you have the first pass written, reset the input file, copy the pass1() to pass2() and rewrite. Note, in pass2 certain error checking doesn’t have be done anymore. Instead you are now rewriting the instructions.
