# "I am the Alpha and the Omega, the First and the Last, the Beginning and the End." - Revelation 22:13

import sys

RAT = [{"name": "$t" + str(i), "val": 0, "free": True} for i in range(10)]

def isTemp(val):
    return val[0:2] == "$t"

def isOffset(val):
    return val.find("($t") != -1

def makeOffset(offset, reg):
    return offset + '(' + reg + ')'

def assignTemp(val):
    for reg in RAT:
        if reg["free"]:
            reg["val"] = val
            reg["free"] = False
            return reg["name"]

def searchTemp(temp):
    for reg in RAT:
        if reg["val"] == temp:
            #print("Freed:", temp)
            reg["free"] = True
            return reg["name"]

def handleFunction(inst):
    label = [inst[1] + ":"]
    allocate = ["subiu", "$sp", "$sp", inst[2]]
    raOffset = str(int(inst[2]) - 4) + "($sp)"
    storeReturn = ["sw", "$ra", raOffset]
    return [label, allocate, storeReturn]

def handleReturn(inst):
    reg = searchTemp(inst[1]) if isTemp(inst[1]) else inst[1]
    return ["move", "$v0", reg]

def handleEnd(inst):
    raOffset = str(int(inst[2]) - 4) + "($sp)"
    loadReturn = ["lw", "$ra", raOffset]
    deallocate = ["addiu", "$sp", "$sp", inst[2]]
    jump = ["jr", "$ra"]
    return [loadReturn, deallocate, jump]

def handleLoad(inst):
    if isTemp(inst[1]):
        inst[1] = assignTemp(inst[1])
    if isOffset(inst[2]):
        idx = inst[2].find("($t")
        offset = inst[2][0:idx]
        temp = inst[2][idx+1:-1]
        reg = searchTemp(temp)
        inst[2] = makeOffset(offset, reg)
    return inst

def handleStore(inst):
    if isTemp(inst[1]):
        inst[1] = searchTemp(inst[1])
    if isOffset(inst[2]):
        idx = inst[2].find("($t")
        offset = inst[2][0:idx]
        temp = inst[2][idx+1:-1]
        reg = searchTemp(temp)
        inst[2] = makeOffset(offset, reg)
    return inst

def handleMove(inst):
    inst[1] = assignTemp(inst[1]) if isTemp(inst[1]) else inst[1]
    inst[2] = searchTemp(inst[2]) if isTemp(inst[2]) else inst[2]

    return inst

def handleMath(inst):
    inst[1] = assignTemp(inst[1]) if isTemp(inst[1]) else inst[1]
    inst[2] = searchTemp(inst[2]) if isTemp(inst[2]) else inst[2]
    inst[3] = searchTemp(inst[3]) if isTemp(inst[3]) else inst[3]
    return inst

def handleDiv(inst):
    first = [inst[0], inst[2], inst[3]]
    second = ["mflo", inst[1]]
    return [first, second]

def handleMod(inst):
    first = [inst[0], inst[2], inst[3]]
    second = ["mfhi", inst[1]]
    return [first, second]

def handleJump(inst):
    return inst

def handleBranch(inst):
    inst[1] = searchTemp(inst[1]) if isTemp(inst[1]) else inst[1]
    inst[2] = searchTemp(inst[2]) if isTemp(inst[2]) else inst[2]
    return inst

def handleLabel(inst):
    return [inst[1] + ":"]

def handleSyscall(inst):
    return inst

def handleFree(inst):
    searchTemp(inst[1])
    return []

def translate(inst):
    #print("Before:", inst)
    kjv = {
        "func": handleFunction,
        "end": handleEnd,
        "ret": handleReturn,

        "add": handleMath,
        "addi": handleMath,
        "addiu": handleMath,
        "addu": handleMath,

        "sub": handleMath,
        "subi": handleMath,
        "subiu": handleMath,
        "subu": handleMath,

        "mul": handleMath,
        "div": handleMath,
        "mod": handleMath,

        "li": handleLoad,
        "lw": handleLoad,

        "sw": handleStore,

        "move": handleMove,

        "j": handleJump,
        "jal": handleJump,

        "beq": handleBranch,
        "bne": handleBranch,
        "bgt": handleBranch,
        "bge": handleBranch,
        "blt": handleBranch,
        "ble": handleBranch,

        "label": handleLabel,
        "syscall": handleSyscall,
        "free": handleFree
    }

    cmd = inst[0]
    translatedList = kjv[cmd](inst)
    #print("After:", translatedList)
    return translatedList

def stringify(li):
    cmdStr = li[0] + "\t"
    ops = li[1:]
    opsStr = ', '.join(ops) + "\n"
    instStr = cmdStr + opsStr
    return instStr


inputFile = sys.argv[1]
with open(inputFile, 'r') as fp:
    output = []
    for line in fp:
        inst = line.split()
        translated = translate(inst)

        if inst[0] == "func":
            insts = handleFunction(inst)
            for inst in insts:
                instStr = stringify(inst)
                output.append(instStr)
        elif inst[0] == "end":
            insts = handleEnd(inst)
            for inst in insts:
                instStr = stringify(inst)
                output.append(instStr)
        elif inst[0] == "div":
            insts = handleDiv(translated)
            for inst in insts:
                instStr = stringify(inst)
                output.append(instStr)
        elif inst[0] == "mod":
            insts = handleMod(translated)
            for inst in insts:
                instStr = stringify(inst)
                output.append(instStr)
        elif inst:
            translatedStr = stringify(translated)
            output.append(translatedStr)

outputFile = sys.argv[2]
with open(outputFile, 'w') as fp:
    startASM = [
        ["start:"],
        ["jal", "main"],
        ["li", "$v0", "10"],
        ["syscall"]
    ]
    startStr = [stringify(line) for line in startASM]
    for line in startStr:
        fp.write(line)
    for line in output:
        fp.write(line)
