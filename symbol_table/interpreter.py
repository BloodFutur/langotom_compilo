lines = open("asm.txt", "r").readlines()
asm = [l.split(" ") for l in lines]
asm = [[l[0]] + [int(x) for x in l[1:]] for l in asm]
mem = [0] * 255

# print(asm)

ip = 0
while ip < len(asm):
    if asm[ip][0] == "AFC":
        mem[asm[ip][1]] = asm[ip][2]
        ip += 1
    elif asm[ip][0] == "COP":
        mem[asm[ip][1]] = mem[asm[ip][2]]
        ip += 1
    elif asm[ip][0] == "ADD":
        mem[asm[ip][1]] = mem[asm[ip][2]] + mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "SOU":
        mem[asm[ip][1]] = mem[asm[ip][2]] - mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "MUL":
        mem[asm[ip][1]] = mem[asm[ip][2]] * mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "DIV":
        mem[asm[ip][1]] = mem[asm[ip][2]] // mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "EQU":
        mem[asm[ip][1]] = mem[asm[ip][2]] == mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "NEQ":
        mem[asm[ip][1]] = mem[asm[ip][2]] != mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "LT":
        mem[asm[ip][1]] = mem[asm[ip][2]] < mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "GT":
        mem[asm[ip][1]] = mem[asm[ip][2]] > mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "GE":
        mem[asm[ip][1]] = mem[asm[ip][2]] >= mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "NOT":
        mem[asm[ip][1]] = not mem[asm[ip][1]]
        ip += 1
    elif asm[ip][0] == "AND":
        mem[asm[ip][1]] = mem[asm[ip][2]] and mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "OR":
        mem[asm[ip][1]] = mem[asm[ip][2]] or mem[asm[ip][3]]
        ip += 1
    elif asm[ip][0] == "JMP":
        ip = asm[ip][1]
    elif asm[ip][0] == "JMF":
        if not mem[asm[ip][1]]:
            ip = asm[ip][2]
        else:
            ip += 1
    elif asm[ip][0] == "PRI":
        print(mem[asm[ip][1]])
        ip += 1
    else:
        print("Unknown instruction: " + asm[ip][0])
        break

print("\nMemory at the end:")
print(mem)    

