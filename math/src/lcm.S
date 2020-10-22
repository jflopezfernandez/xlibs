.global least_common_multiple
.func least_common_multiple,least_common_multiple
least_common_multiple:
    pushq %rbp
    movq %rbp,%rsp

    xor %eax,%eax

    movq %rsp,%rbp
    popq %rbp
    ret
.endfunc
