% Author: Nestor Hernandez Rodriguez
% Last Update: 9-03-2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee

function [ROIindex] = selectBestCandidate(pointMatrix,videoFrame,ReferenceImage)

% This function carries out the selection within a given candidate matrix
% (1 row per candidate) of the best candidate based on color comparison.
% The ouput is the row index (integer) of the matrix which contains the best candidate
% 
% Inputs:
% pointMatrix - Matrix containing the candidates. (1 per row)
% 
% videoFrame - frame used to detect the lines candidates
% 
% ReferenceImage - image used to make the color based comparison


sizebbox=size(pointMatrix);

for j=1:sizebbox(1,:)
    % Crop by ROI
    positive = imcrop(videoFrame,pointMatrix(j, :));
    % Filter by color
    [BW,framehist] = createHsvRedMask(positive); % This function can be edited based on the color mask wanted
    % Split into RGB Channels
    Red = framehist(:,:,1);
    Green = framehist(:,:,2);
    Blue = framehist(:,:,3);
    % Get histValues for each channel
    [yRed, x] = imhist(Red);
    [yGreen, x] = imhist(Green);
    [yBlue, x] = imhist(Blue);
    HistSum=nnz(yRed)+nnz(yGreen)+nnz(yRed);

    if HistSum>100 % Minimum number for a good candidate to be considered
       [BW,framehist] = createHsvRedMask(ReferenceImage);
        % Split into RGB Channels
        Red2 = framehist(:,:,1);
        Green2 = framehist(:,:,2);
        Blue2 = framehist(:,:,3);
        % Get histValues for each channel
        [yRed2, x] = imhist(Red2);
        [yGreen2, x] = imhist(Green2);
        [yBlue2, x] = imhist(Blue2);
        % Compare pixels means
        deltaR = abs(double(mean2(Red) - double(mean2(Red2))));
        deltaG = abs(double(mean2(Green) - double(mean2(Green2))));
        deltaB = abs(double(mean2(Blue) - double(mean2(Blue2))));
        if and(deltaR<35,and(deltaG<35,deltaB<35)) %Threshold defined to filter good candidate
        ROIindex=j;break;
        else
        ROIindex=0;    
        end
    else                
    ROIindex=0;
    break;
end
end
