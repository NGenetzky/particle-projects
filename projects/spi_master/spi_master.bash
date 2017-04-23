
## *****************************************************************************
## Configure
## *****************************************************************************
# set -x
set -e
repo=$(git rev-parse --show-cdup)
project="${repo}/projects/spi_master"
[ -d $project ] || project=$(pwd) # backup project.

## *****************************************************************************
## Files
## *****************************************************************************
# Internal
ln -f "${project}/src/spi_master.cpp" "${project}/workspace/spi_master.cpp"
ln -f "${project}/include/SpiMaster.h" "${project}/workspace/SpiMaster.h"

# External (EE491)
# ln -f "${repo}/ee491/firmware/Pin.h" "${project}/workspace/Pin.h"
# ln -f "${repo}/ee491/firmware/Function.h" "${project}/workspace/Function.h"
# ln -f "${repo}/ee491/firmware/File.h" "${project}/workspace/File.h"
# ln -f "${repo}/ee491/firmware/ParticleSPI.h" "${project}/workspace/ParticleSPI.h"

## *****************************************************************************
## Program
## *****************************************************************************
device=${1?"Specify the device as first arg."}
particle flash $device ${project}/workspace