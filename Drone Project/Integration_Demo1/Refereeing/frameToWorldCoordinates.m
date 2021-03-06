%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author: Nestor Hernandez Rodriguez
% Project: Robotic Referee Drone
% Date: March 2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function ballWorldPosition =frameToWorldCoordinates(yawAngleDrone, thetaCamX, frameSizeX, thetaCamY, frameSizeY, height, ballPosition)

% This function carries out the ball position conversion from pixel frame
% coordinates to world model coordinates in meters
% 
% Inputs:
% ballPosition - 2x1 vector containing the center of the ball in the frame
%
% yawAngleDrone - yaw/psi angle of the drone referenced to the world model coordinate system in radians
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



%% Calculate Rotation matrix between the frame reference system and the world reference system
if ballPosition(1) == -100 && ballPosition(2) == -100 % Filter predefined not-known ball position and assign a predefined value
    ballWorldPosition = [-999 -999];
else   

    Rx=rotx(-180); % Rotation matrix for the x-axis (fliping the y-axis from the frame reference to the world model reference)
    Rz=rotz(yawAngleDrone*180/pi); % Rotation matrix for the z-axis based on the yaw/psi angle estimated

    %% Calculate ball position with respect to the center of the frame

    ballPosition2=[ballPosition(1)-frameSizeX/2; ballPosition(2)-frameSizeY/2; 0];

    %% Calculate vector in the local reference system with the same orientation as the absolute reference system

    ballPosition3=Rx*Rz*ballPosition2; % Apply concatenation of rotations to change from frame reference to the world model system reference

    %% Translate pixel distance into meters for both axis (Using two thetas is more accurate)

    pixelDistanceX = (height*tan(thetaCamX/2))/(frameSizeX/2);
    pixelDistanceY = (height*tan(thetaCamY/2))/(frameSizeY/2);

    %% Calculating ball position in meters

    ballWorldPosition=[ballPosition3(1)*pixelDistanceX ballPosition3(2)*pixelDistanceY];
end
end
