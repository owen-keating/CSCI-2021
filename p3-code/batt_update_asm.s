.text
.global     set_batt_from_ports

set_batt_from_ports:
        movw    BATT_VOLTAGE_PORT(%rip), %ax    # ax = BATT_VOLTAGE_PORT

.ERROR_CHECK:
        cmp     $0, %ax                         # compare voltage reading to 0
        jge     .SET_MILLIVOLTS                 # if greater or equal, goto set_millivolts

.PORTS_ERROR:
        movl    $1, %eax                        # eax = 1
        ret                                     # return eax

.SET_MILLIVOLTS:
        sarw    $1, %ax                         # ax /= 2
        movw    %ax, (%rdi)                     # batt->mlvolts = ax

.SET_PERCENTAGE:
        cmp     $3000, %ax                      # compare mlvolts to 3000
        jl      .BATTERY_EMPTY                  # if less, goto battery_empty
        subw    $3000, %ax                      # ax -= 3000
        sarw    $3, %ax                         # ax /= 8
        cmp     $100, %ax                       # compare ax to 100
        jg      .BATTERY_FULL                   # if greater, goto battery_full
        movw    %ax, 2(%rdi)                    # batt->percent = ax
        jmp     .SET_MODE                       # goto set_mode

.BATTERY_EMPTY:
        movw    $0, 2(%rdi)                     # batt->percent = 0
        jmp     .SET_MODE                       # goto set_mode

.BATTERY_FULL:
        movw    $100, 2(%rdi)                   # batt->percent = 100

.SET_MODE:
        movb    BATT_STATUS_PORT(%rip), %al     # al = BATT_STATUS_PORT
        andb    $16, %al                        # al & 0b10000
        sarb    $4, %al                         # al >> 4
        cmp     $1, %al                         # compare al to 1
        je      .PORTS_SUCCESS                  # if equal, goto ports_success
        addb    $2, %al                         # batt->mode = 2

.PORTS_SUCCESS:
        movb    %al, 3(%rdi)                    # batt->mode = al
        movl    $0, %eax                        # eax = 0
        ret                                     # return eax

.data

digits:
        .int 0b0111111                          # zero digit
        .int 0b0000110                          # one digit
        .int 0b1011011                          # two digit
        .int 0b1001111                          # three digit
        .int 0b1100110                          # four digit
        .int 0b1101101                          # five digit
        .int 0b1111101                          # six digit
        .int 0b0000111                          # seven digit
        .int 0b1111111                          # eight digit
        .int 0b1101111                          # nine digit

.text
.global     set_display_from_batt

set_display_from_batt:
        movl    $0, %r10d                       # r10d register represents display bitstring
        movl    %edi, %eax                      # eax = batt.mlvolts
        sarl    $16, %eax                       # 16-bit shift, eax = batt.percent
        andl    $0xFF, %eax                     # eax & 0xFF

.FIVE_BARS:
        cmp     $90, %eax                       # compare percent to 90
        jl      .FOUR_BARS                      # if less, goto four_bars
        orl     $0b11111, %r10d                 # r10d |= 0b11111
        jmp     .MODE_CHECK                     # goto mode_check

.FOUR_BARS:
        cmp     $70, %eax                       # compare percent to 70
        jl      .THREE_BARS                     # if less, goto three_bars
        orl     $0b1111, %r10d                  # r10d |= 0b1111
        jmp     .MODE_CHECK                     # goto mode_check

.THREE_BARS:
        cmp     $50, %eax                       # compare percent to 50
        jl      .TWO_BARS                       # if less, goto two_bars
        orl     $0b111, %r10d                   # r10d |= 0b111
        jmp     .MODE_CHECK                     # goto mode_check

.TWO_BARS:
        cmp     $30, %eax                       # compare percent to 30
        jl      .ONE_BAR                        # if less, goto one_bar
        orl     $0b11, %r10d                    # r10d |= 0b11
        jmp     .MODE_CHECK                     # goto mode_check

.ONE_BAR:
        cmp     $5, %eax                        # compare percent to 5
        jl      .MODE_CHECK                     # if less, goto mode_check
        orl     $0b1, %r10d                     # r10d |= 0b1

.MODE_CHECK:
        movl    %edi, %ecx                      # ecx = batt.mlvolts
        sarl    $24, %ecx                       # 24-bit shift, ecx = batt.mode
        andl    $0xFF, %ecx                     # ecx & 0xFF
        sall    $7, %r10d                       # r10d << 7
        cmp     $2, %ecx                        # compare mode to 2
        je      .VOLTAGE_MODE                   # if equal, goto voltage_mode

.PERCENTAGE_MODE:
        movl    $0, %r8d                        # r8d register represents ones
        movl    $0, %edx                        # edx = 0, used as the remainder
        movl    $10, %ecx                       # ecx = 10, used as the divisor
        divl    %ecx, %eax                      # edx = eax % 10, eax /= 10
        movl    %edx, %r8d                      # r8d = edx

        movl    $0, %r9d                        # r9d register represents tens
        movl    $0, %edx                        # edx = 0, used as the remainder
        divl    %ecx, %eax                      # edx = eax % 10, eax /= 10
        movl    %edx, %r9d                      # r9d = edx
        leaq    digits(%rip), %r11              # r11 initialized to array pointer

.CHECK_HUNDREDS:
        cmp     $0, %eax                        # compare hundreds to 0
        je      .CHECK_TENS                     # if equal, goto check_tens

.SET_HUNDREDS:
        movl    (%r11,%rax,4), %ecx             # ecx = digits[hundreds]
        orl     %ecx, %r10d                     # r10d |= ecx
        sall    $7, %r10d                       # r10d << 7
        jmp     .SET_TENS                       # goto set_tens

.CHECK_TENS:
        sall    $7, %r10d                       # r10d << 7
        cmp     $0, %r9d                        # compare tens to 0
        je      .SET_ONES                       # if equal, goto set_ones

.SET_TENS:
        movl    (%r11,%r9,4), %ecx              # ecx = digits[tens]
        orl     %ecx, %r10d                     # r10d |= ecx

.SET_ONES:
        sall    $7, %r10d                       # r10d << 7
        movl    (%r11,%r8,4), %ecx              # ecx = digits[ones]
        orl     %ecx, %r10d                     # r10d |= ecx
        sall    $3, %r10d                       # r10d << 3
        orl     $0b001, %r10d                   # r10d |= 0b001
        jmp     .UPDATE                         # goto update

.VOLTAGE_MODE:
        movl    %edi, %eax                      # eax = batt.mlvolts
        andl    $0xFFFF, %eax                   # eax & 0xFFFF
        movl    $0, %edx                        # edx = 0, used as the remainder
        movl    $10, %ecx                       # ecx = 10, used as the divisor
        divl    %ecx, %eax                      # edx = eax % 10, eax /= 10
        cmp     $5, %edx                        # compare thousandths to 5
        jl      .ROUND_DOWN                     # if less than, goto round_down
        addl    $1, %eax                        # eax += 1

.ROUND_DOWN:
        movl    $0, %r8d                        # r8d register represents hundredths
        movl    $0, %edx                        # edx = 0, used as the remainder
        divl    %ecx, %eax                      # edx = eax % 10, eax /= 10
        movl    %edx, %r8d                      # r8d = edx

        movl    $0, %r9d                        # r9d register represents tenths
        movl    $0, %edx                        # edx = 0, used as the remainder
        divl    %ecx, %eax                      # edx = eax % 10, eax /= 10
        movl    %edx, %r9d                      # r9d = edx
        leaq    digits(%rip), %r11              # r11 initialized to array pointer

.SET_ONES_VOLTS:
        movl    (%r11,%rax,4), %ecx             # ecx = digits[ones]
        orl     %ecx, %r10d                     # r10d |= ecx

.SET_TENTHS:
        sall    $7, %r10d                       # r10d << 7
        movl    (%r11,%r9,4), %ecx              # ecx = digits[tenths]
        orl     %ecx, %r10d                     # r10d |= ecx

.SET_HUNDREDTHS:
        sall    $7, %r10d                       # r10d << 7
        movl    (%r11,%r8,4), %ecx              # ecx = digits[hundredths]
        orl     %ecx, %r10d                     # r10d |= ecx
        sall    $3, %r10d                       # r10d << 3
        orl     $0b110, %r10d                   # r10d |= 0b110

.UPDATE:
        movl    %r10d, (%rsi)                   # pointer to r10d bitstring updated
        movl    $0, %eax                        # eax = 0
        ret                                     # return eax

.text
.global         batt_update

batt_update:
        subq    $8, %rsp                        # offsetting the stack by 8
        movq    $0, (%rsp)                      # initializing a new batt struct
        leaq    (%rsp), %rdi                    # rdi initialized to struct pointer
        call    set_batt_from_ports             # calling set_batt_from_ports
        cmp     $0, %eax                        # compare return value to 0
        je      .UPDATE_SUCCESS                 # if equal, goto update_success

.UPDATE_ERROR:
        addq    $8, %rsp                        # resetting the stack
        movl    $1, %eax                        # eax = 1
        ret                                     # return eax

.UPDATE_SUCCESS:
        leaq    BATT_DISPLAY_PORT(%rip), %rsi   # rsi initialized to variable pointer
        movq    (%rdi), %rdi                    # dereferencing rdi
        call    set_display_from_batt           # calling set_display_from_batt
        addq    $8, %rsp                        # resetting the stack
        movl    $0, %eax                        # eax = 0
        ret                                     # return eax
