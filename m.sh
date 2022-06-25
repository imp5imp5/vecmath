rm a.out
clang -O1 m.cpp -lm -lstdc++
./a.out
objdump -d a.out > m_disasm.txt