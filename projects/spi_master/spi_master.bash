
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
ln -f "${project}/include/JtagTapState.h" "${project}/workspace/JtagTapState.h"
ln -f "${project}/include/BinaryLiteral.h" "${project}/workspace/BinaryLiteral.h"
ln -f "${project}/include/JtagTap.h" "${project}/workspace/JtagTap.h"
ln -f "${project}/include/jtag_tap_route.h" "${project}/workspace/jtag_tap_route.h"
ln -f "${project}/include/JtagDevice.h" "${project}/workspace/JtagDevice.h"
ln -f "${project}/include/ParticleSpi.h" "${project}/workspace/ParticleSpi.h"

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