#!/usr/bin/env bash

# Must be run from within "firmware" directory of project.
# Will bash commands that need to be run to create symlink.
# Pipe the output to bash to create symlinks.

# Example:
# └─> ../../scripts/find_and_link_includes.bash ./particle.include                                                                                                                                                                           
# ln -rs  ../../firmware/global/global.h ./global.h
# ln -rs  ../../firmware/logger/logger.h ./logger.h
# ┌──{ubuntu@ngenetzky-cpp-particle-dev-vim-3554998}──{/home/ubuntu/workspace/particle-projects/template/firmware}───────────────────────────────────────────────────────────────────────────────────────────────{master}──{26 Nov 19:11:52}
# └─> ../../scripts/find_and_link_includes.bash ./particle.include | bash
# ln: failed to create symbolic link ‘./global.h’: File exists

set -e

include_file=./particle.include
[ -f $include_file ] || { echo "Can't find ./particle.include"; exit 1; }

firmware_dir=../../firmware
[ -d $firmware_dir ] || { echo "Can't find ../../firmware"; exit 1; }

# List files in firmware
# firmware=$(find ../../firmware)
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
        done < <(find $firmware_dir -name $var -print0)
    # fi
done
