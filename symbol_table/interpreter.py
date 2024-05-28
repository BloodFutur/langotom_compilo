lines = open("asm.txt", "r").readlines()
asm = [l.split(" ") for l in lines]
asm = [[l[0]] + [int(x) for x in l[1:]] for l in asm]
mem = [0] * 255

mem[0]  = -1

import time

# print(asm)
debug = False
memoryOffset = 0
ip = 0
max_iter = 35
iter = 0
while ip < len(asm) and iter < max_iter:
    iter += 1
    if debug:
        print("\n")
        print("ip: " + str(ip))
        print("memoryOffset: " + str(memoryOffset))
        print("mem: " + str(mem))
        print("asm[ip]: " + str(asm[ip]))
    # Sleep for 0.1 seconds
    # time.sleep(0.05)  
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
        if not mem[asm[ip][1]]:
            ip = asm[ip][2]
        else:
            ip += 1
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

