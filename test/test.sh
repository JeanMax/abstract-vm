#!/bin/bash -e

CLR_GREEN="\033[32;01m"
CLR_RED="\033[31;01m"
CLR_RESET="\033[0m"


function success() {
	echo -ne "$CLR_GREEN$1$CLR_RESET"
}

function test_vm() {
	input="$1"
	ctrl="$2"

	test_log_file=/tmp/test_abstract-vm.log
	ctrl_log_file=/tmp/ctrl_abstract-vm.log

	./abstractvm << EOF >& $test_log_file
$input
EOF

	cat << EOF > $ctrl_log_file
$ctrl
EOF

	diff --color=always $test_log_file $ctrl_log_file || \
		(echo -e "\nInput: \n$input"; exit 42)
	echo -ne "$CLR_GREEN.$CLR_RESET"
}


test_vm "zboub" "'zboub': nop."
