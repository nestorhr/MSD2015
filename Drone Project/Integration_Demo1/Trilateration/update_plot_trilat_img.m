function [im] = update_plot_trilat_img(im,field2im_params,ballpos,dronepos,b_outpitch)
    % Convert point to ij matrix coordinates
    [dronei,dronej] = xy2ij(dronepos(1),dronepos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    [balli,ballj]   = xy2ij(ballpos(1),ballpos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    
    radius_plot=20;
    
    im = insertShape(im,'FilledCircle',[dronej dronei radius_plot],'color','black','Opacity', 1);    
    im = insertShape(im,'FilledCircle',[ballj  balli  radius_plot],'color','red','Opacity', 1);
    
    im = insertText(im,[10 90],'DRONE POSITION','BoxOpacity',0);
    im = insertText(im,[10 110],['X: ' num2str(dronepos(1),'%0.1f') ' Y: ' num2str(dronepos(2),'%0.1f')],'BoxOpacity',0);
    
    im = insertText(im,[10 150],'BALL POSITION','BoxOpacity',0);
    im = insertText(im,[10 170],['X: ' num2str(ballpos(1),'%0.1f') ' Y: ' num2str(ballpos(2),'%0.1f')],'BoxOpacity',0);
    
    if ~b_outpitch
        im = insertText(im,[10 210],'BALL IN PITCH','BoxColor','Blue','BoxOpacity',1,'TextColor','White');
    else
        im = insertText(im,[10 210],'BALL OUT OF PITCH','BoxColor','Red','BoxOpacity',1);
    end
end