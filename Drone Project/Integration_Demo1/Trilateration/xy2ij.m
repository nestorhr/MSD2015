function [i,j] = xy2ij(x,y,xm,ym,ni,nj)
% Function to convert a symmetrical x,y axis coordinate system to a
% row, column based matrix coordinate system
% x, y      = coordinates
% xm, ym    = max axis
% ni, nj    = number of rows/colums
    i = round(ni*(0.5 - y/ym));
    j = round(nj*(0.5 + x/xm));
    