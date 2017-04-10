function [ Y ] = Freenove( device )

    reg.pot1 = Register(device, 2);
    reg.pot2 = Register(device, 3);
    reg.joyy = Register(device, 4);
    reg.joyx = Register(device, 5);

    function [x,y] = get_joystick()
        Analog12bit = @(a12) (a12/(2.^12));
        x12b = reg.joyx.get();
        y12b = reg.joyy.get();
        x = Analog12bit( x12b )-0.5;
        y = Analog12bit( y12b )-0.5;
    end

    function [h] = plot_joystick()
        figure;
        hold on;
        joystick.plot = plot(0,0);
        grid on
        title('Joystick on Freenove board');
        xlim([-0.5 0.5]);
        ylim([-0.5 0.5]);

        % Keep running until plot is closed.
        while( isvalid(joystick.plot) )
            [joystick.x joystick.y] = get_joystick();
            % joystick.x = [0, jx ];
            % joystick.y = [0, jy ];
            set(joystick.plot,          ...
                'XData',[0 joystick.x], ...
                'YData',[0 joystick.y] );
            drawnow
        end
    end
    Y.plot_joystick = @plot_joystick

    Y.reg = reg;

end
