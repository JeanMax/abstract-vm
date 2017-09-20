#!/bin/bash

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

    exit 1
}

function test_vm() {
	input="$1"
	ctrl="$2"

	cat << EOF > $CTRL_LOG_FILE
$ctrl
EOF

    ./abstractvm << EOF >& $TEST_LOG_FILE
$input
EOF

    ret=$?
    test $ret == 0 || fail "$input" "$ret"
    diff $TEST_LOG_FILE $CTRL_LOG_FILE > /dev/null || fail "$input"

    success_msg "."
}



test_vm "zboub" "'zboub': nop."

test_vm "$(< ./data/example.avm)" "42
42.42
3341.25"

test_vm "$(< ./data/bobo.avm)" "20.2"


echo
