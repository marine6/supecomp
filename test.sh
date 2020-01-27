#!/bin/bash

DIR=$1

say_ok(){
    echo -ne "\t\x1b[32mOK\x1b[0m"
}

say_ko(){
    echo -ne "\t\x1b[31mKO\x1b[0m"
}

say_ok_or_ko(){
    R=$1
	  if [[ "0" -eq $R ]]; then
        say_ok
	  else
		    say_ko
    fi
}

test_comp(){
    F=$1
    P1=$2
    P2=$3
    LANG=$4
	  OUT=`$DIR/supecomp $F -$LANG-run $P1 $P2 | diff "$F.expect_${P1}_${P2}" ->/dev/null`
    say_ok_or_ko "$?"

}
test_asm(){
    F=$1
    P1=$2
    P2=$3
    TARGET=$4
    OPTS=$5
    EXE=`mktemp`
    chmod u+x $EXE
    $DIR/supecomp $F -target $TARGET $OPTS -libdir $DIR/runtime_$TARGET/ -o $EXE 1>/dev/null 2>&1
    ($EXE $P1 $P2 | diff "$F.expect_${P1}_${P2}" -)  1>/dev/null 2>&1
    say_ok_or_ko "$?"
    rm $EXE
}

test_x86_64_asm(){
    test_asm $1 $2 $3 x86-64 ""
}
test_x86_64_asm2(){
    test_asm $1 $2 $3 x86-64 "-clever-regalloc 9"
}
test_x86_32_asm(){
    test_asm $1 $2 $3 x86-32 ""
}
test_riscv_asm(){
    test_asm $1 $2 $3 riscv ""
}

test_riscv_asm2(){
    test_asm $1 $2 $3 riscv "-clever-regalloc 15"
}

printf "%-30s: \telang \telang \tcfg \tcfg \trtl \trtl \tx86-32 \tx86-32 \tx86-64 \tx86-64 \tx86-64 \tx86-64 \trv \trv \trv2 \trv2\n" "File"

for f in tests/*.e; do
    printf "%-30s: " $f
	  test_comp "$f" 1 5 "elang"
    test_comp "$f" 12 14 "elang"
    test_comp "$f" 1 5 "cfg"
    test_comp "$f" 12 14 "cfg"
    test_comp "$f" 1 5 "rtl"
    test_comp "$f" 12 14 "rtl"
    test_x86_32_asm "$f" 12 14
    test_x86_32_asm "$f" 1 5
    test_x86_64_asm "$f" 12 14
    test_x86_64_asm "$f" 1 5
    test_x86_64_asm2 "$f" 12 14
    test_x86_64_asm2 "$f" 1 5
    test_riscv_asm "$f" 12 14
    test_riscv_asm "$f" 1 5
    test_riscv_asm2 "$f" 12 14
    test_riscv_asm2 "$f" 1 5
    echo ""
done



