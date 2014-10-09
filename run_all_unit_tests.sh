#!/bin/bash

function usage() {
cat << EOF
Synopsis
	`basename $0` <directory>

Will run all executable binaries found in the directory provided by <directory> whose name ends with "tests"
EOF

  exit 1
}

unit_test_result=0
failing_test_suites=""

if [ $# -eq 1 ] ; then
  TEST_PROGRAMS=`find $1 -name *tests`

  for test_suite in $TEST_PROGRAMS ; do
    $test_suite
    returncode=$?
    if [[ $returncode != 0 ]] ; then
      unit_test_result=$returncode
      failing_test_suites="$failing_test_suites $test_suite"
    fi
  done
else
  usage
fi

if [ $unit_test_result -ne 0 ] ; then
  echo ""
  echo "*** Failing tests ***"
  
  for suite in $failing_test_suites ; do
    echo "$suite:"
    $suite | grep FAIL
    echo ""
  done
fi

exit $unit_test_result

