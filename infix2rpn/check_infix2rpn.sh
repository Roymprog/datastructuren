#!/usr/bin/env bash

get_expr() {
    local to_convert="$1" ignore_whitespace="$2" got ret

    got="$($PROG "$to_convert")"
    ret="$?"

    if [[ -n "$ignore_whitespace" ]]; then
        got="$(echo "$got" | sed -e 's/\s\+/ /g' | sed -e 's/^\s\+//g' | sed -e 's/\s\+$//g' )"
        :;
    fi

    echo "$got"
    return "$ret"
}
export -f get_expr

source check_lib.sh

export PROG=./infix2rpn
header "Simple exprs" "checking simple expressions"
check_equal /dev/stdin bash -c "get_expr '3+3' true" <<< '3 3 +'
check_equal /dev/stdin bash -c "get_expr '3+4*5' true" <<< '3 4 5 * +'
check_equal /dev/stdin bash -c "get_expr '3*8' true" <<< '3 8 *'

header "Grouping exprs" "checking precedence levels"
check_equal /dev/stdin bash -c "get_expr '(1 + 2) + 3' true" <<< '1 2 + 3 +'
check_equal /dev/stdin bash -c "get_expr '1 + (2 + 3)' true" <<< '1 2 3 + +'
check_equal /dev/stdin bash -c "get_expr '1 + (2 + 3) + 4' true" <<< '1 2 3 + + 4 +'

header "Hard exprs" "Checking difficult expressions"
check_equal /dev/stdin bash -c "get_expr '100 * 10 / 20' true" <<< '100 10 * 20 /'
check_equal /dev/stdin bash -c "get_expr '1 + 2 * 3' true" <<< '1 2 3 * +'

header "Wrong exprs" "Checking if wrong expressions are handled."
check_error ./infix2rpn '((1 + 2)'
check_error ./infix2rpn '(1*2))'
check_error ./infix2rpn '('

header "Left ops" "Checking if left associative ops"
check_equal /dev/stdin bash -c "get_expr '4 * 1 ^ 2 ^ 3' true" <<< '4 1 2 ^ 3 ^ *'

header "Functions" "Checking if functions work"
check_equal /dev/stdin bash -c "get_expr '3 ^ (4+2)F' true" <<< '3 4 2 + F ^'
check_equal /dev/stdin bash -c "get_expr '1 + 2 G' true" <<< '1 2 G +'

header "Tilde" "Checking if tilde operator works"
check_equal /dev/stdin bash -c "get_expr '~2' true" <<< '2 ~'
check_equal /dev/stdin bash -c "get_expr '~2^3' true" <<< '2 ~ 3 ^'

header "Stats" "Checking stack stats"
check_equal_err /dev/stdin bash -c "get_expr '' true" <<< 'stats 0 0 0'
check_equal_err /dev/stdin bash -c "get_expr '2 + 2' true" <<< 'stats 1 1 1'
check_equal_err /dev/stdin bash -c "get_expr '1+2+3+4+5' true" <<< 'stats 4 4 1'
