%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Author: Nestor Hernandez Rodriguez
% Project: Robotic Referee Drone
% Date: March 2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [ballPosition, selectedLines, outputFrame]=detectionSkill(ballSelectionMode, lineDetectionEnabled, ReferenceImage, inputFrame)

% This function carries out the ball and line detection skill and gives as
% output the ballPosition X and Y coordinates in pixels within the current 
% frame, theselectedLines found in a matrix, the status flag regarding the 
% ball and line detection ('0' - not detected, '1' - detected) and an 
% output frame with the ball detection
%
% Inputs:
% lineDetectionEnabled - flag that enables '1' or disables '0' line detection
%
% inputFrame - input frame used by the detection skill

%% Load Camera Parameters
persistent cameraParams

if isempty(cameraParams)
   cameraParams = AR_Drone_CamCalibration_fcn(); % Change the calibration function if needed
end


%% Create the point tracker object.
pointTracker = vision.PointTracker('MaxBidirectionalError', 1);

% Initialize number of tracking points
numPts = 0;


%% Ball Color Based detection
            
% Pre-process and categorize frames
videoFrame = inputFrame; % Input frame used for color detection and displaying the results
videoFrameGray = rgb2gray(videoFrame); % Pre-processed  gray frame used for tracking
videoFrameLines = videoFrame; % RGB frame used for line detection

if numPts < 10 % If not enough tracking points found (Pre-defined minimum number of 10)

    % Start color detection
    [~,maskedI]=createHsvRedMask(videoFrame); % Filter frame by color / Edit the color mask function if needed
    I=im2bw(maskedI,0.005); % Black and White image conversion with '0.005' level threshold
    [centers, radii] = imfindcircles(I,[20 60], 'Sensitivity',0.95); % Find circular forms with the defined pixel radius and with a non-aggresive acceptance criteria (0.95)

    if ~isempty(centers) % If some circles are found

        centerS = centers(1:1,:); % Pick the best candidate (the one with the strongest metric)
        radiiS = radii(1:1); % Store the radius of the selected circle       
        bboxTH=5; % Threshold for drawing the boundary box (in order to not plot it near the edges of the frame)
        bbox=[centerS(1)-radiiS,centerS(2)-radiiS,2*radiiS,2*radiiS]; % Define the boundary box around the ball
        
        % Plot the boundary box only if the whole ball is inside the field
        if bbox(1)+2*radiiS>frameSize(2)||bbox(2)+2*radiiS>frameSize(1)||bbox(1)-bboxTH<0||bbox(2)-bboxTH<0 
            zbbox=0; % Set use the bbox flag to '0' - don't do anything, no ball is found 
            ballPosition=[-100 -100]; % pre-defined ball position output when no ball is found
        elseif bbox(1)>=0&&bbox(2)>=0 % The bbox is inside the frame
            zbbox = 1;  % Set use the bbox flag to '1' - start the tracking, a ball is found 
            ballPosition=[centerS(1), centerS(2)];
        else
            zbbox=0;
            ballPosition=[-100 -100];

        end

        if zbbox>0 % If use the bbox flag is greater than 0 - Set to '1' 
            
            % Find corner points inside the detected region for the good candidate.
            points = detectMinEigenFeatures(videoFrameGray, 'ROI', bbox(zbbox, :));
            % Re-initialize the point tracker.
            xyPoints = points.Location;
            numPts = size(xyPoints,1);
            release(pointTracker);
            initialize(pointTracker, xyPoints, videoFrameGray);

            % Save a copy of the points.
            oldPoints = xyPoints;

            % Convert the rectangle represented as [x, y, w, h] into an
            % M-by-2 matrix of [x,y] coordinates of the four corners. This
            % is needed to be able to transform the bounding box to display
            % the orientation of the face.
            bboxPoints = bbox2points(bbox(zbbox, :));

            % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4]  format required by insertShape.
            bboxPolygon = reshape(bboxPoints', 1, []);

            % Check that the transformed bbox is still inside the frame
            if bboxPolygon(1)>0&&bboxPolygon(2)>0&&bboxPolygon(3)>0&&bboxPolygon(4)>0&&bboxPolygon(5)>0&&bboxPolygon(6)>0&&bboxPolygon(7)>0&&bboxPolygon(8)>0

                % Display a bounding box around the detected ball.
                videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);
            end

        end
    else
    ballPosition=[-100 -100];
    end

else
        % Tracking mode enabled. Enough tracking points
        [xyPoints, isFound] = step(pointTracker, videoFrameGray);
        visiblePoints = xyPoints(isFound, :);
        oldInliers = oldPoints(isFound, :);

        numPts = size(visiblePoints, 1);

        if numPts >= 10
            % Estimate the geometric transformation between the old points and the new points.

            [xform, oldInliers, visiblePoints] = estimateGeometricTransform(...
                oldInliers, visiblePoints, 'similarity', 'MaxDistance', 4);

            % Apply the transformation to the bounding box.
            bboxPoints = transformPointsForward(xform, bboxPoints);

            % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4] format required by insertShape.
            bboxPolygon = reshape(bboxPoints', 1, []);

            if bboxPolygon(1)>0&&bboxPolygon(2)>0&&bboxPolygon(3)>0&&bboxPolygon(4)>0&&bboxPolygon(5)>0&&bboxPolygon(6)>0&&bboxPolygon(7)>0&&bboxPolygon(8)>0                         

                % Display a bounding box around the face being tracked.
                videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);

                % Display tracked points.
                videoFrame = insertMarker(videoFrame, visiblePoints, '+', 'Color', 'white');
            end

            % Reset the points.
            oldPoints = visiblePoints;
            setPoints(pointTracker, oldPoints);

       end
end

% Set the output frame with the original frame and the detected boundary box if found 
outputFrame = videoFrame;

%% Line Detection

if lineDetectionEnabled==1 % Start line detection if enabled
    
    % Frame pre-process for line detection
%   [image,newOrigin] = undistortImage(videoFrameLines,cameraParams);% Correct image based on camera calibration if it is needed
    I=im2bw(videoFrameLines,0.5); % Black and White image conversion with '0.5' level threshold
    imBW= bwmorph(I,'thin',10); % Thin BW image in order to get better lines candidates ('10' thinning iterations)
    % Detect lines (Parameters values can be checked at MATLAB's help)
    [H,T,R] = hough(imBW);
    P  = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:)))); 
    lines = houghlines(imBW,T,R,P,'FillGap',5,'MinLength',7); 

    if ~isempty(lines) % If some lines are detected

        % Read lines structure and extract points and values into vectors
        P1matrix=zeros(length(lines),2);
        P2matrix=zeros(length(lines),2);
        ThetaVector=zeros(length(lines),1);
        RhoVector=zeros(length(lines),1);

        for i=1:length(lines)

            for j=1:2
            P1matrix(i,j)=lines(i).point1(1,j);
            P2matrix(i,j)=lines(i).point2(1,j);
            end

            ThetaVector(i)=lines(i).theta;
            RhoVector(i)=lines(i).rho;

        end

        Pmatrix=[P1matrix P2matrix]; % Matrix of lines
        sizeLines=size(Pmatrix(:,1)); % Size of lines structure

        % Filter candidate lines by comparison of theta and rho

        TRmatrix=[ThetaVector RhoVector]; % Matrix of theta and rho
        LinesCandidates=zeros(sizeLines(1),2);
        SumCandidates=1; % At least there is 1 candidate if the lines structure is not empty
        % Convert negative rho's candidates into positive ones with the corresponding theta conversion
        sizeTRmatrix=size(TRmatrix);
            for z = 1:sizeTRmatrix(1)
                if TRmatrix(z,2) < 0
                    TRmatrix(z,1) = TRmatrix(z,1) + 180;
                    TRmatrix(z,2) = -TRmatrix(z,2);
                end
            end
            
        LinesCandidates(1,:)= TRmatrix(1,:);

        ThetaTH=10; % Threshold defined for theta difference in degrees
        RhoTH=90; % Threshold defined for rho difference in pixels
        
        % Find the real number of different lines (SumCandidates)
        for i=1:sizeLines(1)-1

            auxCandidates=0;

            for j=1:SumCandidates

                if abs(TRmatrix(i+1,1)-LinesCandidates(j,1))>ThetaTH || abs(TRmatrix(i+1,2)-LinesCandidates(j,2))>RhoTH
                        auxCandidates=auxCandidates+1;
                end           
            end
            if auxCandidates==SumCandidates
                LinesCandidates(SumCandidates+1,:)=TRmatrix(i+1,:);
                SumCandidates=SumCandidates+1; 
            end
        end

        if sizeTRmatrix(1) > 1 % Cluster lines into groups (number of clusters = SumCandidates) only if we have more than 1 line to cluster
            idx=kmeans(TRmatrix, SumCandidates, 'Distance','cityblock'); % Get the index of the clustered lines based on the real number of lines detected
        else
            idx = [1]; % If we only have 1 line
        end

        % Select the best candidate within a cluster based on the longest segment      

        selectedLines=zeros(SumCandidates,6); % Should include the coordinates for both points and the theta and rho value

        for i=1:SumCandidates

            auxMatrix=[Pmatrix TRmatrix];
            sortVector=idx;
            sortVector1=sortVector==i;
            auxMatrix=auxMatrix(sortVector1==1,:);
            px1=auxMatrix(:,1);    
            py1=auxMatrix(:,2);    
            px2=auxMatrix(:,3);    
            py2=auxMatrix(:,4);    
            ptheta=auxMatrix(:,5);    
            prho=auxMatrix(:,6);    

            sizeCandidatesLines=size(px1);
            longestLine=zeros(sizeCandidatesLines(1),1);

            % Calculate which is the longest candidate line
            for j=1:sizeCandidatesLines(1);

                lineLenght=sqrt((py2(j)-py1(j))^2+(px2(j)-px1(j))^2);
                longestLine(j)=lineLenght;
            end

            % Select candidate

            [~,maxIdx]=max(longestLine);   
            selectedLines(i,1)= px1(maxIdx);
            selectedLines(i,2)= py1(maxIdx);
            selectedLines(i,3)= px2(maxIdx);
            selectedLines(i,4)= py2(maxIdx);
            selectedLines(i,5)= ptheta(maxIdx);
            selectedLines(i,6)= prho(maxIdx);

        end
    else
        selectedLines=zeros(1,6); % No lines were detected so return an empty line of size 1x6 with zeros
    end
else
    selectedLines=zeros(1,6); % Detection is not enabled so return an empty line of size 1x6 with zeros
end
end           
            
            