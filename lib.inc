section .text 


; ��������� ��� �������� � ��������� ������� �������
exit:
  mov rax, 60
  syscall 



; ��������� ��������� �� ����-��������������� ������, ���������� � �����
string_length:
  xor rax, rax
  .counter:
    inc rax
    cmp byte[rdi+rax-1], 0
    jne .counter
  dec rax
  ret



; ��������� ��������� �� ����-��������������� ������, ������� � � stdout
print_string:
  push rdi
  call string_length
  pop rsi ; pointer
  mov  rdx, rax ; length
  mov  rax, 1
  mov  rdi, 1
  syscall
  ret




; ��������� ������ (������� ������ � ����� 0xA)
print_newline:
  mov rdi, '\n'




; ��������� ��� ������� � ������� ��� � stdout
print_char:
  push rdi
  mov  rsi, rsp 
  mov  rdx, 1
  mov  rax, 1
  mov  rdi, 1
  syscall
  pop rdi
  ret





; ������� �������� 8-�������� ����� � ���������� ������� 
print_int:
    cmp rdi, 0
    jl .negative
.positive:
    jmp print_uint
.negative:
    push rdi
    mov rdi, '-'
    call print_char
    pop rdi
    neg rdi
    jmp print_uint



; ������� ����������� 8-�������� ����� � ���������� ������� 
; �����: �������� ����� � ����� � ������� ��� ���������� �������
; �� �������� ��������� ����� � �� ASCII ����.

print_uint:
    mov rax, rdi
    mov r9, rsp
    push 0            
    mov rdi, rsp     
    sub rsp, 20       
    mov r10, 10       
.loop:
    xor rdx, rdx      
    div r10           
    add dl, 0x30      
    dec rdi           
    mov [rdi], dl     
    test rax, rax
    jnz .loop
    
    call print_string
    mov rsp, r9
    ret





; ��������� ��� ��������� �� ����-��������������� ������, ���������� 1 ���� ��� �����, 0 �����
string_equals:
    push r12
    push r13
    xor rax, rax ; �� ����� ������ 0
    xor rcx, rcx
    .loop:
        mov r13b, byte[rdi+rcx] ; ������� ������ 1 ����
        mov r12b, byte[rsi+rcx] ; ������� ������ 2 ����
        inc rcx ; +1 � ��������� �� ����. ������
        cmp r13, r12 ; ���������� �������
        je .check_null ; ����� ������?
        pop r13
        pop r12
        ret ; ���� ������� ������ �������� 0
    .check_null:
        test r13, r12 ; ��������� �� ���� 
        jnz .loop
        inc rax
        pop r13
        pop r12
        ret





; ������ ���� ������ �� stdin � ���������� ���. ���������� 0 ���� ��������� ����� ������
read_char:
    xor rax, rax
    xor rdi, rdi
    mov rdx, 1
    push 0
    mov rsi, rsp
    syscall
    pop rax
    ret





; ���������: ����� ������ ������, ������ ������
; ������ � ����� ����� �� stdin, ��������� ���������� ������� � ������, .
; ���������� ������� ��� ������ 0x20, ��������� 0x9 � ������� ������ 0xA.
; ��������������� � ���������� 0 ���� ����� ������� ������� ��� ������
; ��� ������ ���������� ����� ������ � rax, ����� ����� � rdx.
; ��� ������� ���������� 0 � rax
; ��� ������� ������ ���������� � ����� ����-����������

read_word:
        push    r14
        push    r15
        xor    r14, r14
        mov    r15, rsi
       
        dec    r15

        cmp    rsi, 1
        jle    .exception

        .white:
            push    rdi
            call    read_char
            pop    rdi           
            cmp    al, ' '
            je    .white
            cmp    al, 10
            je    .white
            cmp    al, 13
            je    .white
            cmp    al, 9
            je    .white
            test    al, al
            jz    .success

        .chars:
            mov    byte[ rdi + r14 ], al
            inc     r14
            push    rdi
            call    read_char
            pop    rdi   
            cmp    al, ' '
            je    .success
            cmp    al, 10
            je    .success
            cmp    al, 13
            je    .success
            cmp    al, 9
            je    .success
            test    al, al
            jz    .success
            cmp    r14, r15
            je    .exception

            jmp    .chars

        .exception:
            xor    rax, rax
            jmp    .end
           
        .success:
            mov    byte[ rdi + r14 ], 0
            mov    rax, rdi
            mov    rdx, r14
           
        .end:
            pop    r15
            pop     r14
            ret




; ��������� ��������� �� ������, ��������
; ��������� �� � ������ ����������� �����.
; ���������� � rax: �����, rdx : ��� ����� � ��������
; rdx = 0 ���� ����� ��������� �� �������


parse_uint:
    xor rdx, rdx 
    xor rax, rax
    xor r8, r8 
    .first_number:             
        mov r8b, byte[rdi]
        cmp r8b, '0'
        jb .no
        cmp r8b, '9'
        ja .no
        sub r8b, '0'
        mov al, r8b
        inc rdx
    .other_numbers:              
        mov r8b, byte[rdi+rdx]
        cmp r8b, '0'
        jb .ok
        cmp r8b, '9'
        ja .ok
        inc rdx
        imul rax, 0xA ; rax*10
        sub r8b, '0'
        add rax, r8
        jmp .other_numbers
    .no:                
        mov rdx, 0
    .ok:                
        ret





; ��������� ��������� �� ������, ��������
; ��������� �� � ������ �������� �����.
; ���� ���� ����, ������� ����� ��� � ������ �� ���������.
; ���������� � rax: �����, rdx : ��� ����� � �������� (������� ����, ���� �� ���) 
; rdx = 0 ���� ����� ��������� �� �������
parse_int:
    cmp byte [rdi], '-'
    jne .positive
    inc rdi
    call parse_uint
    neg rax
    inc rdx
    ret
.positive:
    call parse_uint
    ret 




; ��������� ��������� �� ������, ��������� �� ����� � ����� ������
; �������� ������ � �����
; ���������� ����� ������ ���� ��� ��������� � �����, ����� 0

string_copy:
    push rbx
    xor rax, rax
    .loop:
    	cmp rax, rdx 
    	je .notfit
    	mov bl, [rdi + rax]
    	mov byte[rsi + rax], bl
    	cmp byte[rdi + rax], 0
    	je .fit
    	inc rax
    	jmp .loop
    .notfit:
    	xor rax, rax
    .fit:
    	pop rbx
    	ret
