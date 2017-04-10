function [ Y ] = Freenove( device )

    reg.pot1 = Register(device, 2);
    reg.pot2 = Register(device, 3);
    reg.joyy = Register(device, 4);
    reg.joyx = Register(device, 5);

    function [x,y] = get_joystick_pos()
        Analog12bit = @(a12) (a12/(2.^12));
        x12b = reg.joyx.get();
        y12b = reg.joyy.get();
        xfloat = Analog12bit( x12b );
        yfloat = Analog12bit( y12b );
        x = xfloat - 0.5;
        y = yfloat - 0.5;

        % Calibration
        % xcenter = 0.5; %0.7039;
        % ycenter = 0.5; %0.4751;
        % x = ((0.5+1) + (1-0.5)*((2*xfloat - (xcenter+1.0))/(1.0-xcenter)))/2;
        % y = ((0.5+1) + (1-0.5)*((2*yfloat - (ycenter+1.0))/(1.0-ycenter)))/2;
        %xcenter = 0.7039;
        %ycenter = 0.4751;
        %x = (xfloat<xcenter)*(xfloat*0.5/xcenter) + (xcenter<xfloat)*(xcenter + (xfloat-xcenter)*0.5/(1-xcenter));
        %y = (yfloat<ycenter)*(yfloat*0.5/ycenter) + (ycenter<yfloat)*(ycenter + (yfloat-ycenter)*0.5/(1-ycenter));
    end
    Y.get_joystick_pos = @get_joystick_pos

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
            [joystick.x joystick.y] = get_joystick_pos();
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
