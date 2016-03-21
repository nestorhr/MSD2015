function fign = init_plot_trilat(im, items, field2im_params)
% Function to initiate plot of field
%
% INPUT
% im              -> Image of field in RGB matrix form
% items           -> Set of plot items, {[x y], 'label'; ....}
% field2im_params -> Field and image size in a vector ([lx ly ni nj])

% Plot field picture
fign = figure; hold on;
fign = fign.Number; hold on;
imshow(im)
axis image

% Plot corners
hold on
plots = [];
for i = 1:4
    [xi,xj] = xy2ij(items(i,1),items(i,2),field2im_params(1),field2im_params(2),field2im_params(3),field2im_params(4));
    xin(i) = xi; xjn(i) = xj;
    plots(i) = plot(xj,xi,'*','markersize',20);   
end

% Plot field lines between corners
for i = 1:4
    if i <= 3
        b = i+1;
    else
        b = 1;
    end
    plot([xjn(i) xjn(b)],[xin(i) xin(b)],'k')
end

% Set up legend
legend(plots,'C1','C2','C3','C4','location','eastoutside')
end