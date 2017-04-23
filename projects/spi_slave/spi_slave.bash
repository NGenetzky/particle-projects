
## *****************************************************************************
## Configure
## *****************************************************************************
# set -x
set -e
repo=$(git rev-parse --show-cdup)
project="${repo}/projects/spi_slave"
[ -d $project ] || project=$(pwd) # backup project.

## *****************************************************************************
## Files
## *****************************************************************************
# Internal
ln -f "${project}/src/spi_slave.cpp" "${project}/workspace/spi_slave.cpp"

## *****************************************************************************
## Program
## *****************************************************************************
device=${1?"Specify the device as first arg."}
particle flash $device ${project}/workspace