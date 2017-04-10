
function [ Y ] = Register( device, address)

    function [ value ] = get ( addr )
        rv = device.call_reg(addr);
        value = rv.return_value;
    end

    function [ value ] = set ( addr, value)
        rv = device.call_reg( [addr, '=', value] );
        value = rv.return_value;
    end

    if nargin < 2
        Y.get = @(addr) get(addr);
        Y.get = @(addr, value) get(addr);
    else
        Y.get = @() get(address);
        Y.set = @(value) set(address, value);
    end

end
