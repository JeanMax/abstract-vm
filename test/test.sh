#!/bin/bash

# FATAL=t

CLR_GREEN="\033[32;01m"
CLR_RED="\033[31;01m"
CLR_RESET="\033[0m"


TEST_LOG_FILE=/tmp/test_abstract-vm.log
CTRL_LOG_FILE=/tmp/ctrl_abstract-vm.log

function success_msg() {
	echo -ne "$CLR_GREEN$1$CLR_RESET"
}

function error_msg() {
    echo -e "$CLR_RED$1$CLR_RESET"
}

function fail() {
	input="$1"
    exit_status="$2"

    error_msg "\nInput:"
    echo "$input"

    if test "$exit_status"; then
        error_msg "\nExit-status:"
        echo "$exit_status"
    else
        error_msg "\nTest:"
        cat $TEST_LOG_FILE

        error_msg "\nControl:"
        cat $CTRL_LOG_FILE

        error_msg "\nDiff:"
        diff --color=always $TEST_LOG_FILE $CTRL_LOG_FILE
    fi

    test $FATAL && exit 1
}

function test_vm() {
	input="$1"
	ctrl="$2"

	echo -n "$ctrl" > $CTRL_LOG_FILE

    ./abstractvm << EOF > $TEST_LOG_FILE 2>&1
$input
EOF

    ret=$?
    test $ret == 0 || fail "$input" "$ret"
    diff $TEST_LOG_FILE $CTRL_LOG_FILE > /dev/null || fail "$input"

    success_msg "."
}



test_vm "zboub" "'zboub': nop.
"

test_vm "$(< ./data/bobo.avm)" "20.2
"

test_vm "$(< ./data/example.avm)" "42
42.42
3341.25
"

test_vm "$(< ./data/zero_divide_error.avm)" "zero divide error
"

test_vm "$(< ./data/overflow_error.avm)" "overflow error
"

test_vm "$(< ./data/syntax_error.avm)" "syntax error
"

test_vm "$(< ./data/empty_stack_error.avm)" "empty stack error
"

test_vm "$(< ./data/assert_error.avm)" "assert error
"

test_vm "$(< ./data/missing_operand_error.avm)" "missing operand error
"

test_vm "$(< ./data/plop.avm)" "p
l
o
p
!
"

# TODO: Testez un programme de votre invention. Par exemple, faites des operations avec croisement de types avec de tres grands et de tres petits nombres (hors overflow/underflow).

# TODO: Essayez de tester un programme difficile de votre invention (genre vicieux quoi)

# TODO: test stdin vs file

# TODO: underflow error

# TODO: no exit instruction

# TODO: modulo zero error





# \n after dots
echo
