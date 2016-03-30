function [im] = update_plot_trilat_img(im,field2im_params,ballpos,dronepos,b_outpitch)
    % Convert point to ij matrix coordinates
    [dronei,dronej] = xy2ij(dronepos(1),dronepos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    [balli,ballj]   = xy2ij(ballpos(1),ballpos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    
    radius_plot=20;
    
    im = insertShape(im,'FilledCircle',[dronej dronei 1.2*radius_plot],'color','black','Opacity', 1);    
    im = insertShape(im,'FilledCircle',[ballj  balli  0.8*radius_plot],'color','red','Opacity', 1);
    
    im = insertText(im,[10 90],'DRONE POSITION','BoxOpacity',0);
    im = insertText(im,[10 110],['X: ' num2str(dronepos(1),'%0.1f') ' Y: ' num2str(dronepos(2),'%0.1f') ' YAW: ' num2str(180/pi*dronepos(3),'%0.1f')],'BoxOpacity',0);
    
    im = insertText(im,[10 150],'BALL POSITION','BoxOpacity',0);
    if abs(abs(ballpos(1))-0.5*field2im_params(1)) < 2
        im = insertText(im,[10 170],['X: ' num2str(ballpos(1),'%0.1f') ' Y: ' num2str(ballpos(2),'%0.1f')],'BoxOpacity',0);
    else
        im = insertText(im,[10 170],'BALL NOT DETECTED','BoxOpacity',0);
    end
    
    if b_outpitch == 0
        im = insertText(im,[10 210],'BALL IN PITCH','BoxColor','Blue','BoxOpacity',1,'TextColor','White');
    elseif b_outpitch == 1
        im = insertText(im,[10 210],'BALL OUT OF PITCH','BoxColor','Red','BoxOpacity',1);
    else
        im = insertText(im,[10 210],'BALL POSITION UNKNOWN','BoxColor','White','BoxOpacity',1);
    end
end