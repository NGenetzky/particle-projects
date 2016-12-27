classdef SerialHandle < handle
properties(Access=public)
    data; % Serial Object
    name;
end
properties(Access=private)
    s; % Serial Object
end

methods(Access=public)
%% Constructor
    function this = SerialHandle(com,varargin)
        if(length(varargin) ==1)
            this.name = varargin{1};
        else
            this.name = 'SerialHandle';
        end
        this.s = serial(com,'BaudRate',9600, 'Tag', this.name);
        this.data = [];
        this.s.RecordDetail = 'verbose';
        this.s.RecordName = ['serial-',com,'.txt'];

        % Attach callbacks
        % Bytes-Available Event
        % A bytes-available event is generated immediately after a predetermined number of bytes are available in the input buffer or a terminator is read, as determined by the BytesAvailableFcnMode property.
        % If BytesAvailableFcnMode is byte, the bytes-available event executes the callback function specified for the BytesAvailableFcn property every time the number of bytes specified by BytesAvailableFcnCount is stored in the input buffer. If BytesAvailableFcnMode is terminator, the callback function executes every time the character specified by the Terminator property is read.
        % This event can be generated only during an asynchronous read operation.
        this.s.BytesAvailableFcnMode = 'terminator';
        this.s.terminator = 10; % '\n' = LF = 10
        % this.s.BytesAvailableFcnCount = 64;
        this.s.BytesAvailableFcn = @this.on_recieve;

        fopen(this.s);
        record(this.s,'on');
    end

%% Callbacks
function on_recieve(this, obj, ~)
    BytesAvailable = obj.BytesAvailable;
    if(this.BytesAvailable)
        this.data = [this.data; {fscanf(obj)}];
    end 
    fprintf('%s received %d bytes\n', this.name, BytesAvailable);
end

%% Accessors
function n = BytesAvailable(this)
    n = this.s.BytesAvailable;
end
function A = view(this)
    A = strjoin(this.data,'');
    disp(A);
end
       
%% Passthru functions
    % delete (serial)	Remove serial port object from memory
    % fclose (serial)	Disconnect serial port object from device
    % fgetl (serial)	Read line of ASCII text from device and discard terminator
    % fgets (serial)	Read line of text from device and include terminator
    % fopen (serial)	Connect serial port object to device
    % fprintf (serial)	Write text to device
    function fprintf(this,varargin)
        fprintf(this.s,varargin{:});
    end
    % fread (serial)	Read binary data from device
    % fscanf (serial)	Read ASCII data from device, and format as text
    function A = fscanf(this,varargin)
        A = fscanf(this.s,varargin{:});
    end
    % fwrite (serial)	Write binary data to device
    function fwrite(this,varargin)
        fwrite(this.s,varargin{:});
    end
    % get (serial)	Serial port object properties
    % isvalid (serial)	Determine whether serial port objects are valid
    % readasync	Read data asynchronously from device
    % record	Record data and event information to file
    % serial	Create serial port object
    % serialbreak	Send break to device connected to serial port
    % set (serial)	Configure or display serial port object properties
    % stopasync	Stop asynchronous read and write operations

%% Deconstructor
    function delete(this) % Called automatically by Matlab.
        %fclose(this.s);
        delete(this.s);
    end
end
% methods (Static)
% end
end

