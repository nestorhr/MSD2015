function [im] = update_plot_trilat_img(im,field2im_params,ballpos,dronepos)
    % Convert point to ij matrix coordinates
    [dronei,dronej] = xy2ij(dronepos(1),dronepos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    [balli,ballj]   = xy2ij(ballpos(1),ballpos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    
    radius_plot=20;
    
    im = insertShape(im,'FilledCircle',[dronej dronei radius_plot],'color','black');    
    im = insertShape(im,'FilledCircle',[ballj  balli  radius_plot],'color','red');
end