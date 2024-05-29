"""
    @Author: Anna & Ronan
    @Date: 05/2024
    @Description: 
    
    This script interprets the assembly code stored in the file "asm.txt"
                  and executes the corresponding instructions.

    List of instructions:
      - AFC: Assign a value to a memory location
      - COP: Copy a value from one memory location to another
      - ADD: Add two values and store the result in a memory location
      - SOU: Subtract two values and store the result in a memory location
      - MUL: Multiply two values and store the result in a memory location
      - DIV: Divide two values and store the result in a memory location
      - EQU: Check if two values are equal and store the result in a memory location
      - NEQ: Check if two values are not equal and store the result in a memory location
      - LT: Check if a value is less than another and store the result in a memory location
      - LE: Check if a value is less or equal to another and store the result in a memory location
      - GT: Check if a value is greater than another and store the result in a memory location
      - GE: Check if a value is greater or equal to another and store the result in a memory location
      - NOT: Negate a value and store the result in a memory location
      - AND: Compute the logical AND of two values and store the result in a memory location
      - OR: Compute the logical OR of two values and store the result in a memory location
      - JMP: Jump to a specific instruction
      - JMF: Jump to a specific instruction if a condition is met
      - PRI: Print a value
      - PUSH: Increase the memory offset / move the stack frame
      - POP: Decrease the memory offset / move the stack frame
      - CALL: Call a function
      - RET: Return from a function
      - NOP: Do nothing
"""
import time

# Read the assembly code from the file
filename = "asm.txt"
lines = open(filename, "r").readlines()
asm_raw = [l.split(" ") for l in lines]

# Convert the assembly code to a list of tuples of the form
# (instruction, arg1, arg2, arg3)
asm: list[tuple[str, int, int, int]] = [[l[0]] + [int(x) for x in l[1:]] for l in asm_raw]

# Initialize the memory, its size is 256 bytes
# if the memory is too small, the program will crash
mem = [0] * 256 


# Initialize the interpreter
debug: bool = False     # Set to True to print debug information
memoryOffset: int = 0   # The memory offset, used to simulate the stack pointer
ip: int = 0             # The instruction pointer
max_iter: int = 5000    # The maximum number of iterations before stopping the program
iter: int = 0           # The current iteration


# Execute the program
while ip < len(asm) and iter < max_iter:
    iter += 1

    # Print debug information
    if debug:
        print("\n")
        print("ip: " + str(ip))
        print("memoryOffset: " + str(memoryOffset))
        print("mem: " + str(mem))
        print("asm[ip]: " + str(asm[ip]))
    
    # Sleep for 0.05 seconds, to slow down the execution
    # time.sleep(0.05)  

    # Execute the instruction
    # The compiler is memory based, so the memory is used to store the values
    # The memory offset allows to simulate the stack pointer

    if asm[ip][0] == "AFC":
        mem[asm[ip][1] + memoryOffset] = asm[ip][2]
        ip += 1
    elif asm[ip][0] == "COP":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "ADD":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] + mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "SOU":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] - mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "MUL":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] * mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "DIV":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] // mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "EQU":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] == mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "NEQ":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] != mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "LT":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] < mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "LE":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] <= mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "GT":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] > mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "GE":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] >= mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "NOT":
        mem[asm[ip][1] + memoryOffset] = not mem[asm[ip][1] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "AND":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] and mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "OR":
        mem[asm[ip][1] + memoryOffset] = mem[asm[ip][2] + memoryOffset] or mem[asm[ip][3] + memoryOffset]
        ip += 1
    elif asm[ip][0] == "JMP":
        ip = asm[ip][1]
    elif asm[ip][0] == "JMF":
        if not mem[asm[ip][1] + memoryOffset]:
            ip = asm[ip][2]
            if debug:
                print(mem[asm[ip][1] + memoryOffset])
                print("Jumping to " + str(ip) + "because of: " + str(mem[asm[ip][1]]))
        else:
            ip += 1
            if debug:
                print("Not jumping")
    elif asm[ip][0] == "PRI":
        print(mem[asm[ip][1]] + memoryOffset)
        ip += 1
    elif asm[ip][0] == "PUSH":
        memoryOffset += asm[ip][1]
        ip += 1
    elif asm[ip][0] == "POP":
        memoryOffset -= asm[ip][1]
        ip += 1
    elif asm[ip][0] == "CALL":
        mem[memoryOffset] = ip + 1
        ip = asm[ip][1]
    elif asm[ip][0] == "RET":
        ip = mem[memoryOffset]

    elif asm[ip][0] == "NOP":
        break
    else:
        print("Unknown instruction: " + asm[ip][0])
        break

print("\nMemory at the end:")
print(mem)    

