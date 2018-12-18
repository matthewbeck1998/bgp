# "I am the Alpha and Omega, the first and the last, the beginning and the end." - Revelation 22:13

import sys

RAT = [{"name": "$t" + str(i), "val": 0, "free": True} for i in range(10)]

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

def handleLoad(inst):
    inst[1] = assignTemp(inst[1])
    return inst

def handleStore(inst):
    inst[1] = searchTemp(inst[1])
    return inst

def handleAdd(inst):
    inst[1] = assignTemp(inst[1])
    inst[2] = searchTemp(inst[2])
    inst[3] = searchTemp(inst[3])
    return inst

"""
filepath = sys.argv[1]
with open(filepath) as fp:
    for line in fp:
        sl = line.split()
        translate(sl)
"""

li = ["LW", "$t3", "8($sp)"]
ret = handleLoad(li)
print(ret)

li = ["LW", "$t4", "0($sp)"]
ret = handleLoad(li)
print(ret)

li = ["ADD", "$t5", "$t3", "$t4"]
ret = handleAdd(li)
print(ret)

li = ["SW", "$t5", "0($sp)"]
ret = handleStore(li)
print(ret)

print(RAT)
