function [plots, k] = update_plot_trilat(plots, k, fign, pos, field2im_params, nrplots)
    % Function to plot last ten positions measurements on field
    %
    % INPUT
    % plots             -> vector of plots
    % k                 -> counter
    % fign              -> figure number
    % pos               -> measured position
    % field2im_params   -> field and image size in a vector ([lx ly ni nj])
    % nrplots           -> number of past measurements to be shown
    %
    % OUTPUT
    % plots             -> updated plot vector
    % k                 -> updated counter       
     
    % Select correct figure
    figure(fign); hold on
    
    % Only delete a plot after full plots array is initialized
    % If so, delete the last plot to make room for a new one
    if k <= length(plots)
        delete(plots(k))
    end
    
    % Convert point to ij matrix coordinates
    [i,j] = xy2ij(pos(1),pos(2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    
    % Plot new measurement in red
    plots(k) = plot(j,i,'*k','markersize',10);
    
    % Change color of previous plot to black
%     if k > 1
%         plots(k-1).Color = 'k';
%     elseif k == 0 && length(plots) >= NrPlots
%         plots(end).Color = 'k';
%     end
    
    % Force matlab to pause, draw graph and show plot
    drawnow
    shg
    
    % Count up for k
    k = k + 1;
    if k >= nrplots
        k = 1;
    end
end