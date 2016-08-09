#!/usr/bin/env bash

set -e

include_file=${1?"Arg 1 should be particle include."}

# List files in firmware
firmware=$(find ../../firmware)

# List current files
# current=$(find -type f)


# IFS=$'\n' read -d '' -r -a includes < $include_file
OIFS="$IFS"; IFS=$'\n'; includes=($(<$include_file)); IFS="$OIFS"
# readarray includes < $include_file
# mapfile -t includes < $include_file

# printf "includes:line 1: %s\n" "${includes[0]}"
# printf "firmware:line 1: %s\n" "${firmware[0]}"
# echo $(grep "/$var$" <<< "$firmware")

for var in "${includes[@]}"
do
    # echo "$var"
    # if [ ! -f $link_from  ]; then
        link_from="./$var"
        files=()
        # echo "find ../../firmware -name $var -print0"
        while IFS=  read -r -d $'\0'; do
            link_to="$REPLY"
            echo "ln -rs  $link_to $link_from"
        done < <(find ../../firmware -name $var -print0)
    # fi
done
