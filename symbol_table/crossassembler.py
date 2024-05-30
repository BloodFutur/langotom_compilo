from typing import List, Tuple, Dict

# Define the instruction set
opCodeMap = {
    "NOP": 0,
    "ADD": 1,
    "MUL": 2,
    "SOU": 3,
    "DIV": 4,
    "EQU": 5,
    "NEQ": 6,
    "LT": 7,
    "LE": 8,
    "GT": 9,
    "GE": 10,
    "NOT": 11,
    "AND": 12,
    "OR": 13,
    "JMP": 14,
    "JMF": 15,
    "PRI": 16,
    "PUSH": 17,
    "POP": 18,
    "CALL": 19,
    "RET": 20,
    "AFC": 21,
    "LOAD": 22,
    "STORE": 23,
    "COP" : 24,
}

def print_header() -> None:
    """
    Print the header of the program
    """
    print("CROSS ASSEMBLER")
    print("---------------")
    print("")

def read_asm(filename: str) -> List[Tuple[str, int, int, int]]:
    """
    Read the assembly code from a file.
    
    It reads the file line by line, removes comments, empty lines and labels,
    and returns the assembly code as a list of tuples.

    :param filename: The name of the file to read
    :return: The assembly code as a list of tuples
    """
    lines = open(filename, "r").readlines()
    asm_raw = [l.split() for l in lines]
    asm_clean = [e for e in asm_raw if e and not e[0].startswith(("#", "\n", "."))]
    asm = [tuple([str(l[0])] + [int(x) for x in l[1:]]) for l in asm_clean]
    return asm # type: ignore

def initialize_registers(nb_reg: int) -> Dict[int, List[int]]:
    """
    Initialize the registers with -1 and 0 values.

    For each register, we store the address and the date of the last access.

    :param nb_reg: The number of registers to initialize
    """
    addr_in_register = {i: [-1, 0] for i in range(nb_reg)}
    return addr_in_register

def locate_register(addr: int, addr_in_register: Dict[int, List[int]], nb_reg: int) -> int:
    """
    Find the register that contains the address.
    
    If the address is not in a register, return -1.

    :param addr: The address to find
    :param addr_in_register: The dictionary with the addresses in the registers
    :param nb_reg: The number of registers
    :return: The register that contains the address, or -1 if the address is not in a register
    """
    for i in range(1, nb_reg):
        if addr_in_register[i][0] == int(addr):
            return i
    return -1

def find_oldest_register(addr_in_register: Dict[int, List[int]], nb_reg: int) -> int:
    """
    Find the oldest register that is not used.
    
    If all registers are used, return the oldest one.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param nb_reg: The number of registers
    :return: The oldest register that is not used, or the oldest one if all registers are used
    """
    # If there is an empty register, return it
    for j in range(1, nb_reg):
        if addr_in_register[j][0] == -1:
            return j
    
    # Otherwise, find the oldest register
    oldest = -1
    date = -1
    for i in range(1, nb_reg):
        if addr_in_register[i][1] > date:
            oldest = i
            date = addr_in_register[i][1]
    invalidate_register(addr_in_register, oldest)
    return oldest

def invalidate_address(addr_in_register: Dict[int, List[int]], addr: int, nb_reg: int) -> None:
    """
    Unvalidate the address in the registers.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param addr: The address to unvalidate
    :param nb_reg: The number of registers
    """
    for i in range(1, nb_reg):
        if addr_in_register[i][0] == int(addr):
            addr_in_register[i][0] = -1
            addr_in_register[i][1] = 0

def invalidate_register(addr_in_register: Dict[int, List[int]], reg: int) -> None:
    """
    Unvalidate the register.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param reg: The register to unvalidate
    """
    addr_in_register[reg][0] = -1
    addr_in_register[reg][1] = 0

def increase_register_dates(addr_in_register: Dict[int, List[int]], nb_reg: int) -> None:
    """
    Add one to the date of the registers.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param nb_reg: The number of registers
    """
    for i in range(1, nb_reg):
        if addr_in_register[i][0] != -1:
            addr_in_register[i][1] += 1

def update_register_address(addr_in_register: Dict[int, List[int]], addr: int, reg: int) -> None:
    """
    Update the address in the register with the given address.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param addr: The address to update
    """
    addr_in_register[reg][0] = int(addr)
    addr_in_register[reg][1] = 0

def print_registers(addr_in_register: Dict[int, List[int]], nb_reg: int) -> None:
    """
    Print the addresses in the registers.

    :param addr_in_register: The dictionary with the addresses in the registers
    :param nb_reg: The number of registers
    """
    print("[", end='', flush=True)
    for i in range(1, nb_reg):
        print(str(addr_in_register[i][0]) + ",", end='', flush=True)
    print("]")

def get_new_address(addr_r_to_addr_m: Dict[int, int], old_addr: int, current_addr_r: int) -> int:
    """
    Get the new address for the given old address.
    
    :param addr_r_to_addr_m: The dictionary with the mapping between the registers and the memory addresses
    :param old_addr: The old address to find
    """
    for i in range(1, current_addr_r):
        if addr_r_to_addr_m[i] == old_addr:
            return i
    return -1

def loadreg(reg: int, addr: int) -> Tuple[str, int, int, int]:
    """
    Load instruction line. 

    :param reg: The register to load the value
    :param addr: The address to load the value from
    """
    return ("LOAD", int(reg), int(addr), int(0))

def storereg(reg: int, addr: int) -> Tuple[str, int, int, int]:
    """
    Store instruction line.

    :param reg: The register to store the value
    :param addr: The address to store the value to
    """
    return ("STORE", int(addr), int(reg), 0)


def handle_instruction(
    lines_r: List[Tuple[str, int, int, int]], line: Tuple[str, int, int, int], num: int, addr_in_register: Dict[int, List[int]], 
    addr_r_to_addr_m: Dict[int, int], current_addr_r: int, nb_reg: int
) -> int:
    """
    Handle the instruction line.

    Registers are managed using a Least Recently Used (LRU) policy.

    :param lines_r: The list of instructions
    :param line: The current instruction line
    :param num: The current instruction number
    :param addr_in_register: The dictionary with the addresses in the registers
    :param addr_r_to_addr_m: The dictionary with the mapping between the registers and the memory addresses
    :param current_addr_r: The current address in the registers
    :param nb_reg: The number of registers
    :return: The new current address in the registers
    """

    
    if line[0] in ["ADD", "SOU", "MUL", "DIV"]:
        r1 = locate_register(int(line[1]), addr_in_register, nb_reg)
        r2 = locate_register(int(line[2]), addr_in_register, nb_reg)

        # If the address is not in a register, load it
        if r1 == -1:
            r1 = find_oldest_register(addr_in_register, nb_reg)
            lines_r.append(loadreg(r1, int(line[2])))
            addr_r_to_addr_m[current_addr_r] = num
            current_addr_r += 1

        if r2 == -1:
            r2 = find_oldest_register(addr_in_register, nb_reg)
            lines_r.append(loadreg(r2, int(line[3])))
            addr_r_to_addr_m[current_addr_r] = num
            current_addr_r += 1

        # Find the oldest register to store the result
        r3 = find_oldest_register(addr_in_register, nb_reg)

        # Update the registers with the new addresses
        update_register_address(addr_in_register, int(line[2]), r1)
        update_register_address(addr_in_register, int(line[3]), r2)

        # Add the instruction to the list
        lines_r.append((line[0], r3, r2, r1))
        lines_r.append(storereg(r3, int(line[1])))

        # Update the address in the registers
        addr_r_to_addr_m[current_addr_r] = num
        addr_r_to_addr_m[current_addr_r+1] = num
        current_addr_r += 2

        invalidate_address(addr_in_register, int(line[1]), nb_reg)
        update_register_address(addr_in_register, int(line[1]), r3)

    elif line[0] == "COP":
        r1 = locate_register(int(line[2]), addr_in_register, nb_reg)
        if r1 == -1:
            r1 = find_oldest_register(addr_in_register, nb_reg)
            lines_r.append(loadreg(r1, int(line[2])))
            addr_r_to_addr_m[current_addr_r] = num
            current_addr_r += 1

        lines_r.append(storereg(r1, int(line[1])))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

        invalidate_address(addr_in_register, int(line[1]), nb_reg)
        update_register_address(addr_in_register, int(line[1]), r1)

    elif line[0] == "AFC":
        r1 = find_oldest_register(addr_in_register, nb_reg)
        lines_r.append((line[0], r1, int(line[2]), 0))
        lines_r.append(storereg(r1, int(line[1])))

        addr_r_to_addr_m[current_addr_r] = num
        addr_r_to_addr_m[current_addr_r+1] = num
        current_addr_r += 2

        invalidate_address(addr_in_register, int(line[1]), nb_reg)
        update_register_address(addr_in_register, int(line[1]), r1)

    elif line[0] == "LOAD":
        invalidate_register(addr_in_register, int(line[2]))
        lines_r.append((line[0], int(line[1]), int(line[2]), 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1
        update_register_address(addr_in_register, int(line[3]), int(line[2]))

    elif line[0] == "STORE":
        invalidate_address(addr_in_register, int(line[3]), nb_reg)
        lines_r.append((line[0], int(line[1]), int(line[2]), 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

    elif line[0] == "NOP":
        lines_r.append((line[0], 0, 0, 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

    elif line[0] == "JMP":
        lines_r.append((line[0], int(line[1]), 0, 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

    elif line[0] == "JMF":
        lines_r.append(loadreg(1, int(line[2])))
        lines_r.append((line[0], 1, int(line[2]), 0))
        addr_r_to_addr_m[current_addr_r] = num
        addr_r_to_addr_m[current_addr_r+1] = num
        current_addr_r += 2

    elif line[0] == "PRI":
        lines_r.append((line[0], int(line[1]), 0, 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

    elif line[0] == "RET":
        lines_r.append((line[0], 0, 0, 0))
        addr_r_to_addr_m[current_addr_r] = num
        current_addr_r += 1

    else:
        print(f"[!] Unrecognized command: {line[0]}")

    increase_register_dates(addr_in_register, nb_reg)
    print(f"[+] Processed: {line}. Registers: ", end='', flush=True)
    print_registers(addr_in_register, nb_reg)

    return current_addr_r

def print_final_instructions(lines_r: List[Tuple[str, int, int, int]], addr_r_to_addr_m: Dict[int, int],
                             current_addr_r: int, target_file: str|None) -> None:
    """
    Print the final instructions.

    :param lines_r: The list of instructions
    :param addr_r_to_addr_m: The dictionary with the mapping between the registers and the memory addresses
    :param current_addr_r: The current address in the registers
    """
    
    print("[+] New generated instructions:")
    for i in range(1, current_addr_r):
        print(f"[{addr_r_to_addr_m[i]}] : {lines_r[i]}")

    # Write the assembly code to a file
    if target_file != None:
        f = open(target_file, "w")
        f.write("constant ROM : memory := (\n")
        for instr in lines_r:
            f.write("(x\"%02x%02x%02x%02x\"),\n" % (opCodeMap[instr[0]], instr[1], instr[2], instr[3])) 
        f.write("others => (x\"00000000\"));\n")
        f.close()



# Main function to perform cross-assembly
def cross_assemble(source_file: str, target_file: str):
    """
    Perform the cross-assembly.

    It reads the assembly code from the source file, processes the instructions,
    and writes the binary code to the target file. The binary is actually a VHDL
    constant array with the instructions.
    
    :param source_file: The source file with the assembly code
    :param target_file: The target file to write the binary code (optional)
    
    """
    print_header()

    # Set up the registers and the memory
    asm = read_asm(source_file)
    nb_reg = 8
    addresses_in_register = initialize_registers(nb_reg)
    lines_r = []
    addr_r_to_addr_m = {}
    current_addr_r = 0

    # Process the instructions
    for num, line in enumerate(asm):
        current_addr_r = handle_instruction(lines_r, line, num, addresses_in_register, addr_r_to_addr_m, current_addr_r, nb_reg)

    # Print the final instructions to the console and write them to a file
    print_final_instructions(lines_r, addr_r_to_addr_m, current_addr_r, target_file)

source_file = "asm.txt"
target_file = "asm.bin"
cross_assemble(source_file, target_file)

