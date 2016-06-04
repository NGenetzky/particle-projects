
trap 'echo ">> $BASH_COMMAND"' DEBUG
if [ "$1" ]; then
    master=$1 # First argument should be nice to flash.
else
    exit 1;
fi

if [ "$2" ]; then
    slave=$2 # First argument should be nice to flash.
else
    exit 1;
fi

# insure that niether device is already connected to the i2c bus
particle call $master "do" "reset"
particle call $slave "do" "reset"

particle call $master "do" "i2c_scan"

sleep 1s;

particle call $slave "do" "i2c_slave2"

sleep 3s;

particle call $master "do" "i2c_scan"