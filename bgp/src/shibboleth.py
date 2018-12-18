# "I am the Alpha and Omega, the first and the last, the beginning and the end." - Revelation 22:13

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
    return inst

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
        "div": handleMath,  # NEED TO LOOK AT THIS

        "li": handleLoad,
        "lw": handleLoad,

        "sw": handleStore,
    }

    cmd = inst[0]
    translatedList = kjv[cmd](inst)

    cmdStr = translatedList[0] + "\t"
    ops = translatedList[1:]
    opsStr = ', '.join(ops) + "\n"

    instStr = cmdStr + opsStr
    return instStr


inputFile = sys.argv[1]
with open(inputFile, 'r') as fp:
    output = []
    for line in fp:
        inst = line.split()
        if inst:
            output.append(translate(inst))

outputFile = sys.argv[2]
with open(outputFile, 'w') as fp:
    for line in output:
        fp.write(line)

#
# fullList = []
#
# li = ["addiu", "$t0", "$sp", "16"]
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ["subiu", "$t1", "$t0", "8"]
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['li', '$t2', '1']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['sw', '$t2', '0($t1)']
# ret = handleStore(li)
#
# fullList.append(li)
#
# li = ['addiu', '$t3', '$sp', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['subiu', '$t4', '$t3', '12']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['li', '$t5', '2']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['sw', '$t5', '0($t4)']
# ret = handleStore(li)
#
# fullList.append(li)
#
# li = ['addiu', '$t6', '$sp', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['subiu', '$t7', '$t6', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['li', '$t8', '3']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['sw', '$t8', '0($t7)']
# ret = handleStore(li)
#
# fullList.append(li)
#
# li = ['addiu', '$t9', '$sp', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['subiu', '$t10', '$t9', '8']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['lw', '$t11', '0($t10)']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['addiu', '$t12', '$sp', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['subiu', '$t13', '$t12', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['lw', '$t14', '0($t13)']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['add', '$t15', '$t11', '$t14']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['addiu', '$t16', '$sp', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['subiu', '$t17', '$t16', '16']
# ret = handleMath(li)
#
# fullList.append(li)
#
# li = ['sw', '$t15', '0($t17)']
# ret = handleStore(li)
#
# fullList.append(li)
#
# li = ['li', '$t18', '0']
# ret = handleLoad(li)
#
# fullList.append(li)
#
# li = ['ret', '$t18']
#
# for x in fullList:
#     s1 = x[0] + "\t"
#     ops = x[1:]
#     print("\t" + s1 + ', '.join(ops))

# func    main    16
# addiu   $t0     $sp     FS
# subiu   $t1     $t0     getOffset(x)
# li      $t2     1
# sw      $t2     0($t1)
#
# addiu   $t3     $sp     FS
# subiu   $t4     $t3     getOffset(y)
# li      $t5     2
# sw      $t5     0($t4)
#
# addiu   $t6     $sp     FS
# subiu   $t7     $t6     getOffset(z)
# li      $t8     3
# sw      $t8     0($t7)
#
# addiu   $t9     $sp     FS
# subiu   $t10    $t9     getOffset(x)
# addiu   $t11    $sp     FS
# subiu   $t12    $t11    getOffset(z)
# lw      $t13    0($10)
# lw      $t14    0($12)
# add     $t15    $t13    $t14            # $t15 = x + z
#
# addiu   $t16    $sp     FS
# subiu   $t17    $t16    getOffset(z)
# sw      $t15    0($t17)
#
# li      $t18    0
# ret     $t18
