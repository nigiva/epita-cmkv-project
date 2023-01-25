#!/bin/bash
# This script is used to run the testsuite for the project.

execute_solve() {
    local name=$1
    stdouterr=$(./solver "data/input/$name.txt" "export/$name.txt" 2>&1)
    local return_value=$?
    if [ $return_value -eq 0 ]; then
        echo -e "> $name    \033[32m[SUCCESS]\033[0m"
    else
        echo -e "> $name       \033[31m[FAIL]\033[0m"
    fi
    
    if [ -n "$stdouterr" ]; then
        echo "  $stdouterr"
    fi
}

mkdir -p export
echo "Running testsuite..."
echo "===================="

echo " --  Grids  2x2  -- "
execute_solve "s2-01"
execute_solve "s2-02"
execute_solve "s2-03"
execute_solve "s2-04"
execute_solve "s2-05"
execute_solve "s2-06"
execute_solve "s2-07"
execute_solve "s2-08"
execute_solve "s2-09"

echo " --  Grids  3x3  -- "
execute_solve "s3-01"
execute_solve "s3-02"
execute_solve "s3-03"
execute_solve "s3-04"
execute_solve "s3-05"
execute_solve "s3-06"
execute_solve "s3-07"
execute_solve "s3-08"
execute_solve "s3-09"

echo " --  Grids  4x4  -- "
execute_solve "s4-01"
execute_solve "s4-02"
execute_solve "s4-03"
execute_solve "s4-04"
execute_solve "s4-05"
execute_solve "s4-06"
execute_solve "s4-07"
execute_solve "s4-08"
execute_solve "s4-09"

echo " --  Grids  5x5  -- "
execute_solve "s5-01"
execute_solve "s5-02"
execute_solve "s5-03"
execute_solve "s5-04"
execute_solve "s5-05"
execute_solve "s5-06"
execute_solve "s5-07"
execute_solve "s5-08"
execute_solve "s5-09"

echo " --  Grids  6x6  -- "
execute_solve "s6-01"
execute_solve "s6-02"
execute_solve "s6-03"
execute_solve "s6-04"
execute_solve "s6-05"
execute_solve "s6-06"
execute_solve "s6-07"
execute_solve "s6-08"
execute_solve "s6-09"

echo "===================="
echo "Testsuite finished."