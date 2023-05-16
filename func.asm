section .data
    q1 dd 2.0
    q2 dd 1.0
    q3 dd 3.0

section .text

global f1
f1: ; exp(x)+2
    push ebp
    mov ebp,esp
    finit
    fldl2e      
    fld dword[ebp+8]
    fmulp   
    fld1
    fldl2e      
    fld dword[ebp+8]
    fmulp
    fprem  
    fsub st2, st0
    f2xm1 
    faddp 
    fscale
    fld dword[q1]
    faddp     
    leave
    ret
        
global f2
f2: ; -1/x
    push ebp
    mov ebp,esp
    finit
    fld1
    fld dword[ebp+8]  
    fdivp
    fchs
    leave
    ret

global f3
f3: ; -2(x+1)/3
    push ebp
    mov ebp,esp
    finit
    fld dword[ebp+8]
    fld dword[q2]
    faddp
    fld dword[q1]
    fmulp
    fld dword[q3]
    fdivp
    fchs
    leave
    ret
