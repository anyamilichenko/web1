section .text 


; Принимает код возврата и завершает текущий процесс
exit:
  mov rax, 60
  syscall 



; Принимает указатель на нуль-терминированную строку, возвращает её длину
string_length:
  xor rax, rax
  .counter:
    inc rax
    cmp byte[rdi+rax-1], 0
    jne .counter
  dec rax
  ret



; Принимает указатель на нуль-терминированную строку, выводит её в stdout
print_string:
  push rdi
  call string_length
  pop rsi ; pointer
  mov  rdx, rax ; length
  mov  rax, 1
  mov  rdi, 1
  syscall
  ret




; Переводит строку (выводит символ с кодом 0xA)
print_newline:
  mov rdi, '\n'




; Принимает код символа и выводит его в stdout
print_char:
  push rdi
  mov  rsi, rsp 
  mov  rdx, 1
  mov  rax, 1
  mov  rdi, 1
  syscall
  pop rdi
  ret





; Выводит знаковое 8-байтовое число в десятичном формате 
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



; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.

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





; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
string_equals:
    push r12
    push r13
    xor rax, rax ; по умолч вернет 0
    xor rcx, rcx
    .loop:
        mov r13b, byte[rdi+rcx] ; считали символ 1 стрк
        mov r12b, byte[rsi+rcx] ; считали символ 2 стрк
        inc rcx ; +1 к указателю на след. символ
        cmp r13, r12 ; сравниваем символы
        je .check_null ; конец строки?
        pop r13
        pop r12
        ret ; если символы разные вернется 0
    .check_null:
        test r13, r12 ; проверяем на ноль 
        jnz .loop
        inc rax
        pop r13
        pop r12
        ret





; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    xor rax, rax
    xor rdi, rdi
    mov rdx, 1
    push 0
    mov rsi, rsp
    syscall
    pop rax
    ret





; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор

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




; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось


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





; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
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




; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0

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
