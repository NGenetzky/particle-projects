function [ Y ] = Particle( ACCESS_TOKEN )
%Particle provides access the particle devices through web api.
%   ...
    API = 'https://api.particle.io/v1/';
    DEVICES = [API, 'devices/'];
    
    opt = weboptions('Timeout', 30);
    P.call = @(device, fx, args) webwrite([device.url, fx], 'arg', args, 'access_token', ACCESS_TOKEN, opt);
    P.get = @(device, var) webread([device.url, var], 'access_token', ACCESS_TOKEN, opt);


    %% Get info about Devices
    devices = webread(DEVICES, 'access_token', ACCESS_TOKEN );
    % Create a named field for each device in output struct.
    for k=1:length(devices) % iterate over devices ownd by access token
        name = devices{k}.name;
        % Create field for all infomation that particle offers.
        Y.(name).info = devices{k}; % Start with what particle defines for each device
        
        % Pull important information down into device field
        Y.(name).name = Y.(name).info.name;
        Y.(name).id = Y.(name).info.id;
        Y.(name).connected = Y.(name).info.connected;
        
        % Construct the url for device
        Y.(name).url = [DEVICES, Y.(name).id, '/']; % URL of device
    end
    clear name k
    %notclear devices
    
    %% Get more info about device's exposed commands.
    for k=1:length(devices) % iterate over devices ownd by access token
        name = devices{k}.name;
        if(Y.(name).connected == 0)
            continue
        end
        info = webread(Y.(name).url, 'access_token', ACCESS_TOKEN );
        infofields = fieldnames(info);
        for i = 1:numel(infofields)
            Y.(name).info.(infofields{i}) = info.(infofields{i});
        end
    end
    
    %% Define anon function to determine if variable or function is defined.
    for k=1:length(devices) % iterate over devices ownd by access token
        name = devices{k}.name;
        if(Y.(name).connected == 0)
            continue
        end
        Y.(name).has_fx = @(fx) any(strcmp(Y.(name).info.functions, fx));
        Y.(name).has_var = @(var) any(strcmp(fieldnames(Y.(name).info.variables), var));
    end
    
    %% Expose variables with get_ and functions with call_
    % I am assuming all variable and function names are valid field names.
    % If they are not then "matlab.lang.makeValidName" should be used but
    % it would require more code below.
    for k=1:length(devices) % iterate over devices ownd by access token
        name = devices{k}.name;
        if(Y.(name).connected == 0)
            continue
        end
        for i = 1:numel(Y.(name).info.functions)
            fx = Y.(name).info.functions{i};
            Y.(name).(['call_', fx]) = @(args) P.call(Y.(name), fx, args);
        end
        var_fieldnames = fieldnames(Y.(name).info.variables);
        for i = 1:numel(var_fieldnames)
            var = var_fieldnames{i};
            Y.(name).(['get_', var]) = @(args) P.get(Y.(name), var);
        end
    end
      
    %% Enable access to commands defined by 'cmds' through 'do' function.
    for k=1:length(devices) % iterate over devices ownd by access token
        name = devices{k}.name;
        if(Y.(name).connected == 0)
            continue
        end
        if(~any(strcmp(Y.(name).info.functions, 'do')))
            continue; % No do function
        end
        if(~any(strcmp(fieldnames(Y.(name).info.variables), 'cmds')))
            continue; % No cmds variable
        end
        try % The function could possibly fail. If it does just move to next device.
            P.call(Y.(name), 'do', '1'); % Call do(1) to update 'cmds' variable.
        catch
            break;
        end
        reply = P.get(Y.(name), 'cmds');

        % Separate reply into different commands
        Y.(name).cmds = [];
        idx_commas = strfind(reply.result, '"');
        idx_colons = strfind(reply.result, ':');
        for i = 1:length(idx_commas)/2
            cmd.uid = reply.result( idx_commas(i*2-1)+1: idx_colons(i)-1 );
            cmd.name = reply.result( idx_colons(i)+1: idx_commas(i*2)-1 );
            cmd.f = @() P.call(Y.(name), 'do', cmd.uid);
            Y.(name).cmds = [Y.(name).cmds cmd]; % append the new cmd
        end
        
        for i=1:length(Y.(name).cmds)
            % makeValidName will ensure that it is valid field name
            cmd_name = matlab.lang.makeValidName(Y.(name).cmds(i).name);
            Y.(name).do.(cmd_name) = Y.(name).cmds(i).f;
        end
    end

end

