function [CR1,CR2,CR3,CR4,ref_n]  = Field_Calib(Samples,ref,s)
% Function to calibrate the field. By measuring the four corners the center is found. 
% Then, a new right-handed coordinate system is built around the center with 
% the positive direction going from C1 to C2 and C1 to C4.    
%
% C4----------C3
% |           |
% |           |
% |           |
% C1----------C2
%
% Finally, all points and the anchor positions are transformed to this new
% coordinate system and returned
%
% INPUT
% Samples -> Number of samples taken to measure a corner
% ref     -> Positions of the anchors in the init coordinate system
% s       -> Serial port to UWB anchor 0
%
% OUTPUT
% CR1     -> Corner 1 in field coordinate system
% CR2     -> Corner 2 in field coordinate system
% CR3     -> Corner 3 in field coordinate system
% CR4     -> Corner 4 in field coordinate system
% ref_n   -> Positions of the anchors in the field coordinate system

    % Clarify Corner Conventions
    fprintf('Field Configuration\n')
    fprintf('\t4--------------3\n\t|--------------|\n\t1--------------2\n');
    
    % Measure all four corners
    C = [];
    for i = 1:4
       fprintf('\nField Calibration -> Put Drone in Corner %i and press enter\n',i)
       pause;
       fprintf('\nReceiving....\n')
        
       % Get corner samples
       [X,Y] = getSamples(ref,s,Samples);
       
       % At corner to array
       C(end+1,:) = [X,Y];
       
       %Print to screen
       fprintf('Corner %i: %.3f\t%.3f\n',i,C(end,1),C(end,2));
    end
    % Rename variables
    C1 = C(1,:); C2 = C(2,:); C3 = C(3,:); C4 = C(4,:);

    % Check whether coordinate system is left-handed or right-handed
    vec = cross([C2 0]-[C1 0],[C4 0]-[C1 0]);
    if vec(3) < 0 % Left-Handed Coordinate System
        % Flip y-axis
        ref(:,2) = -ref(:,2);
        C(:,2) = -C(:,2);
        
        % Rename variables
        C1 = C(1,:); C2 = C(2,:); C3 = C(3,:); C4 = C(4,:);
    end
    
    % Calculate Center by averaging corners
    Center=(C4+C3+C2+C1)/4;

    % Set up vectors for rotation of coordinate system
    R1= (C2-C1+C3-C4)/2;
    R2= [1 0];
    
    % Calculate theta in degrees
    %theta = atan2(det([R1' R2']),dot(R1,R2));
    thetad = atan2d(det([R1' R2']),dot(R1,R2));
    
    % Set up rotation matrix
    RotMatrix = rotz(thetad);
    RotMatrix = RotMatrix(1:2,1:2);
     
    % Move and rotate all corner points
    % Move origin of init coordinate system to center
    CR4=C4-Center;
    CR3=C3-Center;
    CR2=C2-Center;
    CR1=C1-Center;
    
    %Rotate
    CR1 = (RotMatrix*CR1')';
    CR2 = (RotMatrix*CR2')';
    CR3 = (RotMatrix*CR3')';
    CR4 = (RotMatrix*CR4')';
    
    % Move and Rotate anchor positions
    ref_n = [];
    for i = 1:3
        ref_n(i,:) = (RotMatrix*(ref(i,1:2)-Center)')';
    end   
    ref_n(:,3) = 0;
end
 
function [X,Y] = getSamples(ref,s,Samples)
    % Function to get corner measurements
    
    % Set up counters
    X = 0; Y = 0;
    
    % Clear buffer
    flushinput(s);
    
    % Take Samples
    for i=1:Samples
        % Get measurement
        dist = GetMC(s,'mc');
        
        % Trilaterate
        P = Trilateration(ref',dist(1:3),eye(3));
        
        % Count up
        X = X + P(2);
        Y = Y + P(3);
    end
    
    % Take average of samples
    X = X/Samples;
    Y = Y/Samples;
end