.file   "sseTest.c"
        .intel_syntax noprefix
        .section        .rodata.str1.1,"aMS",@progbits,1
.LC6:
        .string "|%g %g| * |%g %g| = |%g %g|\n"
.LC7:
        .string "|%g %g|   |%g %g|   |%g %g|\n"
        .section        .text.unlikely,"ax",@progbits
.LCOLDB8:
        .section        .text.startup,"ax",@progbits
.LHOTB8:
        .p2align 4,,15
        .globl  main
        .type   main, @function
main:
.LFB4883:
        .cfi_startproc
        sub     rsp, 104
        .cfi_def_cfa_offset 112
        pxor    xmm7, xmm7
        movsd   xmm0, QWORD PTR .LC0[rip]     #set c1 = 0
        mov     esi, OFFSET FLAT:.LC6
        movsd   xmm1, QWORD PTR .LC1[rip]     #set c2 = 0
        mov     edi, 1
        movsd   QWORD PTR [rsp+16], xmm0
        pxor    xmm6, xmm6
        movsd   QWORD PTR [rsp+24], xmm1
        movsd   xmm5, QWORD PTR .LC3[rip]
        movsd   QWORD PTR [rsp+48], xmm6
        movupd  xmm2, XMMWORD PTR [rsp+16]
        mov     rax, QWORD PTR fs:40
        mov     QWORD PTR [rsp+88], rax
        xor     eax, eax
        movapd  xmm3, XMMWORD PTR .LC5[rip]
        mov     eax, 6
        mulpd   xmm3, xmm2                    #first mul: first iteration _mm_mul_pd(a, b1) _mm_mul_pd(a, b2)
        movsd   QWORD PTR [rsp+56], xmm6      #c1 = _mm_add_pd(c1, _mm_mul_pd(a, b1));   qword= 4 words(2 doubles)
        movsd   QWORD PTR [rsp+40], xmm5      #c2 = _mm_add_pd(c2, _mm_mul_pd(a, b2));
        mulpd   xmm2, xmm7                    #second mul: second iteration
        movsd   QWORD PTR [rsp+64], xmm6
        movsd   QWORD PTR [rsp+72], xmm6
        movsd   xmm1, QWORD PTR .LC2[rip]
        movsd   QWORD PTR [rsp+8], xmm6
        movsd   QWORD PTR [rsp+32], xmm1
        movupd  xmm5, XMMWORD PTR [rsp+48]
        addpd   xmm5, xmm3
        movapd  xmm3, xmm2
        movupd  xmm2, XMMWORD PTR [rsp+32]
        movupd  xmm4, XMMWORD PTR [rsp+64]
        mulpd   xmm7, xmm2                    #three mul
        addpd   xmm2, xmm2
        addpd   xmm3, xmm4
        movapd  xmm4, xmm7
        addpd   xmm2, xmm3
        movapd  xmm3, xmm6
        addpd   xmm4, xmm5
        movups  XMMWORD PTR [rsp+64], xmm2    #outside for loop???
        movapd  xmm2, xmm1
        movups  XMMWORD PTR [rsp+48], xmm4
        movsd   xmm5, QWORD PTR [rsp+64]
        movsd   xmm4, QWORD PTR [rsp+48]
        call    __printf_chk                  #outside for loop
        movsd   xmm6, QWORD PTR [rsp+8]
        mov     esi, OFFSET FLAT:.LC7
        movsd   xmm5, QWORD PTR [rsp+72]
        mov     edi, 1
        movsd   xmm4, QWORD PTR [rsp+56]
        mov     eax, 6
        movsd   xmm3, QWORD PTR .LC1[rip]
        movapd  xmm2, xmm6
        movsd   xmm1, QWORD PTR [rsp+40]
        movsd   xmm0, QWORD PTR [rsp+24]
        call    __printf_chk
        mov     rdx, QWORD PTR [rsp+88]
        xor     rdx, QWORD PTR fs:40
        jne     .L5
        xor     eax, eax
        add     rsp, 104
        .cfi_remember_state
        .cfi_def_cfa_offset 8
        ret
.L5:
        .cfi_restore_state
        call    __stack_chk_fail
        .cfi_endproc
.LFE4883:
        .size   main, .-main
        .section        .text.unlikely
.LCOLDE8:file   "sseTest.c"
        .sectionyntax no.text.startup
.LHOTE8:.section        .rodata.str1.1,"aMS",@progbits,1
.LC6:   .section        .rodata.cst8,"aM",@progbits,8
        .align 8"|%g %g| * |%g %g| = |%g %g|\n"
.LC0:
        .long   0|%g %g|   |%g %g|   |%g %g|\n"
        .long   1072693248ext.unlikely,"ax",@progbits
.LCOLDB8.align 8
.LC1:   .section        .text.startup,"ax",@progbits
.LHOTB8:.long   0
        .long   1073741824
        .align 8main
.LC2:   .type   main, @function
main:   .long   0
.LFB4883.long   1074266112
        .align 8rtproc
.LC3:   sub     rsp, 104
        .long   0cfa_offset 112
        .long   1074790400
        .sectionxmm0, QW.rodata.cst16,"aM",@progbits,16
        .align 16si, OFFSET FLAT:.LC6
.LC5:   movsd   xmm1, QWORD PTR .LC1[rip]
        .long   0di, 1
        .long   1074266112[rsp+16], xmm0
        .long   0mm6, xmm6
        .long   1074266112[rsp+24], xmm1
        .ident  "GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.10) 5.4.0 20160609"
        .sectionQWORD PT.note.GNU-stack,"",@progbits
