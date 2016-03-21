function [im] = update_plot_trilat_img(im,field2im_params,ballpos,dronepos)
    % Convert point to ij matrix coordinates
    [dronei,dronej] = xy2ij(dronepos(1),dronepos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    [balli,ballj]  = xy2ij(ballpos(1),ballpos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    radius_plot=20;
    im = insertShape(im,'Circle',[dronej dronei radius_plot],'color','black','linewidth',5);
    
    if abs(ballpos(1)) < 0.5*field2im_params(1) || abs(ballpos(2)) < 0.5*field2im_params(2)
        % Plot new measurement in red
        im = insertShape(im,'Circle',[ballj balli 35],'color','red','linewidth',5);
    end
end