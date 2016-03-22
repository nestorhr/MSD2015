function [im,field2im_params] = init_plot_trilat_img(items,field_x,field_y)
% Function to initiate plot of field
%
% INPUT
% im              -> Image of field in RGB matrix form
% items           -> Set of plot items, {[x y], 'label'; ....}
% field2im_params -> Field and image size in a vector ([lx ly ni nj])

% Image loading
im = imread('field.png');
im = im(9:end,5:end,:);
ioffs = 32;
joffs = 37; % Trim edges to only have the field
im = im(ioffs+2:end-ioffs,joffs:end-joffs,:);

% Coordinate system conversion preparation
[nrows,ncols,~] = size(im); % Get matrix size
field2im_params = [field_x,field_y,nrows,ncols];

% Plot corners
for i = 1:4
    [xi,xj] = xy2ij(items(i,1),items(i,2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    xin(i) = xi; xjn(i) = xj;
    im = insertShape(im,'circle',[xj xi 5],'color','black');   
end

% Plot field lines between corners
linepos = [];
for i = 1:4
    linepos(end+1) = xjn(i);
    linepos(end+1) = xin(i);
end
im = insertShape(im,'line',linepos,'color','black');

im = insertText(im,[10 10],'LEGEND','BoxOpacity',0);
im = insertText(im,[10 30],'Drone: Black','BoxOpacity',0);
im = insertText(im,[10 50],'Ball:     Red','BoxOpacity',0);
end