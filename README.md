# ABSTRACT VM

A c++ project, AbstractVM is a machine that uses a stack to compute simple arithmetic expressions.
These arithmetic expressions are provided to the machine as basic assembly programs.

# Usage
```bash
make
./avm [input_file]
```

# Grammar of the pseudo assembly

```
S := INSTR [SEP INSTR]* #

INSTR := push VALUE
| pop
| dump
| assert VALUE
| add
| sub
| mul
| div
| mod
| print
| exit

VALUE := int8(N)
| int16(N)
| int32(N)
| float(Z)
| double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
```

# Bonus
- Binary operator: and ('&'), or ('|'), xor ('^')
- Drop the stack entirely.
- Sort from smallest to biggest operand.
- Reverse the stack, can be combine to sort to have it both ways.
- Display the instructions parsed.