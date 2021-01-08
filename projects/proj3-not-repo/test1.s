First:addi t0, x0, 3  #t0=3
addi t1, x0, 2  #t1=2
add t2, t0, t1  #t2=5
or a0, t1, t2   #a0=7
add s0, a0, t2  #s0=c
sll s1, t0, t1  #s1=c
jal ra, First
#lui t0, 0xfffff #t0=fffff000
#beq s0, s1, First
