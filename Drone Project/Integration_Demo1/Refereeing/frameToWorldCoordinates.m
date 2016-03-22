% Author: Nestor Hernandez Rodriguez
% Last Update: 15-03-2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee

function ballWorldPosition =frameToWorldCoordinates(yawAngleDrone, thetaCamX, frameSizeX, thetaCamY, frameSizeY, height, ballPosition)

% This function carries out the ball position conversion from pixel frame
% coordinates to world model coordinates in meters
% 
% Inputs:
% ballPosition - 2x1 vector containing the center of the ball in the frame
%
% yawAngleDrone - yaw angle of the drone referenced to the world model coordinate system in radians
%
% thetaCamX, thetaCamY - angle in radians of the FOV of the camera used for both axis
%
% frameSizeX, frameSizeY - resolution in pixels for both axis
% 
% height - height of the drone in meters
%
% Outputs:
% ballWorldPosition - 2x1 vector containing the center of the ball in the
% frame referenced to the world model coordinate system orientation in
% meters



% Calculate Rotation matrix between the frame reference system and the
% world reference system
if ballPosition(1) == -100 && ballPosition(2) == -100
    ballWorldPosition = [-999 -999];
else    
    %syms t;

    %x_Rot = [1 0 0; 0 cos(t) -sin(t); 0 sin(t) cos(t)];
    %z_Rot = [cos(t) -sin(t) 0; sin(t) cos(t) 0; 0 0 1];

    Rx=rotx(-180);%eval(subs(x_Rot, t, -pi));
    Rz=rotz(yawAngleDrone*180/pi);%eval(subs(z_Rot, t, yawAngleDrone));


    % Calculate ball position with respect to the center of the frame

    ballPosition2=[ballPosition(1)-frameSizeX/2; ballPosition(2)-frameSizeY/2; 0];

    % Calculate vector in the local reference system with the same orientation
    % as the absolute reference system

    ballPosition3=Rx*Rz*ballPosition2;

    % Translate pixel distance into meters for both axis (Using two thetas is
    % more accurate)

    pixelDistanceX = (height*tan(thetaCamX/2))/(frameSizeX/2);
    pixelDistanceY = (height*tan(thetaCamY/2))/(frameSizeY/2);

    % Calculating ball position in meters

    ballWorldPosition=[ballPosition3(1)*pixelDistanceX ballPosition3(2)*pixelDistanceY];
end
