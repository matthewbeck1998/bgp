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
    return "$t10"

def searchTemp(temp):
    for reg in RAT:
        if reg["val"] == temp:
            reg["free"] = True
            return reg["name"]

def handleFunc(inst):
    label = [inst[0] + ":"]
    allocate = ["subiu", "$sp", "$sp", inst[2]]
    raOffset = str(int(inst[2]) - 4) + "($sp)"
    saveReturn = ["sw", "$ra", raOffset]
    return [label, allocate, saveReturn]

def handleRet(inst):
    return inst

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

def translate(inst):
    kjv = {
        "func": handleFunc,
        "ret": handleRet,

        "add": handleMath,
        "addi": handleMath,
        "addiu": handleMath,

        "sub": handleMath,
        "subi": handleMath,
        "subiu": handleMath,

        "mul": handleMath,
        "div": handleMath,

        "li": handleLoad,
        "lw": handleLoad,

        "sw": handleStore,
    }

    cmd = inst[0]
    translatedList = kjv[cmd](inst)
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
            insts = handleFunc(inst)
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
    for line in output:
        fp.write(line)
