
.code

bitscanr proc

mov rdx,rcx

bsr rax,rdx
inc rax
ret

bitscanr endp


zeromem proc

xor rax,rax
mov rdi,rcx
mov rcx,rdx
rep stosq 
ret

zeromem endp

end
