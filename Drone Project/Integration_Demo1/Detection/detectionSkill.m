% Author: Nestor Hernandez Rodriguez
% Last Update: 16-03-2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee

function [ballPosition, selectedLines, outputFrame]=detectionSkill(ballSelectionMode, lineDetectionEnabled, ReferenceImage, inputFrame)

% This function carries out the ball and line detection skill and gives as
% output the ballPosition X and Y coordinates within the current frame, the
% selectedLines found in a matrix, the status flag regarding the ball and
% line detection ('0' - not detected, '1' - detected) and an output frame
% with the ball detection
% 
% ballSelectionMode - Integer
% 
% '0' or any other input different from '1' or '2'- Detection is not enabled
% '1' - Detection based on Cascade Detector
% '2' - Detection based on Color and Shape
%
% lineDetectionEnabled - flag that enables '1' or disables '0' line
% detection

% Load Camera Parameters
persistent cameraParams

if isempty(cameraParams)
   cameraParams = AR_Drone_CamCalibration_fcn(); 
end



% Create the ball cascade detector object.
detector = vision.CascadeObjectDetector('SoccerBallDetectorV2.xml');

% Create the point tracker object.
pointTracker = vision.PointTracker('MaxBidirectionalError', 1);

% if ballSelectionMode==1
%     % Take Reference Image
%     preview(cam);
%     prompt = 'Press any key to take reference image of the ball to track';
%     inputkey = input(prompt);
%     ReferenceFrame = snapshot(cam);
%     ReferenceImage = imresize (ReferenceFrame,0.75,'bilinear');
%     prompt = 'Press any key to continue execution';
%     inputkey2 = input(prompt);
%     closePreview(cam);
% end

% Capture one frame to get its size.
Frame1= inputFrame;
Frame3= rgb2gray(Frame1);
% Frame3 = imresize (Frame2,0.65,'bilinear');
frameSize = size(Frame3);

numPts = 0;


% Ball and Line Detection

switch ballSelectionMode

    case 1 % Using Cascade Detector

        % Process frame.
        videoFrame = inputFrame;
%         videoFrame = imresize (videoFrame,0.65,'bilinear');
        videoFrameLines = videoFrame;
        videoFrameGray = rgb2gray(videoFrame);

        if numPts < 10
            % Detection mode.
            bbox = detector.step(videoFrame);

            if ~isempty(bbox)

                % Selecting the best candidate based on color
                
                [zbbox] = selectBestCandidate(bbox,videoFrame,ReferenceImage);

                if zbbox>0
%                 ballStatusFlag=1;
                % Find corner points inside the detected region for the good candidate.
                points = detectMinEigenFeatures(videoFrameGray, 'ROI', bbox(zbbox, :));
                % Estimate center of ball position
                ballPosition=[bbox(zbbox,1)+bbox(zbbox,3)/2,bbox(zbbox,1)+bbox(zbbox,3)/2];
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

                % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4]
                % format required by insertShape.
                bboxPolygon = reshape(bboxPoints', 1, []);

                % Display a bounding box around the detected ball.
                videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);

                % Display detected corners.
                videoFrame = insertMarker(videoFrame, xyPoints, '+', 'Color', 'white');

                else
                    ballPosition=[-100 -100];
                end
            else
                ballPosition=[-100 -100];
%                 ballStatusFlag = 0;
%                 lineStatusFlag = 0;
            end

        else
                % Tracking mode.
                [xyPoints, isFound] = step(pointTracker, videoFrameGray);
                visiblePoints = xyPoints(isFound, :);
                oldInliers = oldPoints(isFound, :);

                numPts = size(visiblePoints, 1);

                if numPts >= 10
                    % Estimate the geometric transformation between the old points
                    % and the new points.
                    [xform, oldInliers, visiblePoints] = estimateGeometricTransform(...
                        oldInliers, visiblePoints, 'similarity', 'MaxDistance', 4);

                    % Apply the transformation to the bounding box.
                    bboxPoints = transformPointsForward(xform, bboxPoints);

                    % Convert the box corners into the [x1 y1 x2 y2 x3 y3 x4 y4]
                    % format required by insertShape.
                    bboxPolygon = reshape(bboxPoints', 1, []);
                    
                    % Display a bounding box around the face being tracked.
                    videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);

                    % Display tracked points.
                    videoFrame = insertMarker(videoFrame, visiblePoints, '+', 'Color', 'white');
                    

                    % Reset the points.
                    oldPoints = visiblePoints;
                    setPoints(pointTracker, oldPoints);

               end
        end

        % Display the annotated video frame using the video player object.
        outputFrame=videoFrame;
        
        % Line Detection

        if lineDetectionEnabled==1

%             [image,newOrigin] = undistortImage(videoFrameLines,cameraParams); % Correct image based on camera calibration
            I=im2bw(videoFrameLines,0.5);
            imBW= bwmorph(I,'thin',10);
            % Detect lines
            [H,T,R] = hough(imBW);
            P  = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:))));
            lines = houghlines(imBW,T,R,P,'FillGap',5,'MinLength',7);
            
            if ~isempty(lines)
                
                % Read lines structure and extract points
%                 lineStatusFlag=1;
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
                SumCandidates=1;
                LinesCandidates(1,:)=TRmatrix(1,:);
                
                if ~isempty(TRmatrix)
                    sizeTRmatrix=size(TRmatrix);
                    for i = 1:sizeTRmatrix(1)
                        if TRmatrix(i,2) < 0
                            TRmatrix(i,1) = TRmatrix(i,1) + 180;
                            TRmatrix(i,2) = -TRmatrix(i,2);
                        end
                    end
                end
                
                ThetaTH=10; % Threshold defined for theta difference
                RhoTH=90; % Threshold defined for rho difference

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

                idx=kmeans(TRmatrix, SumCandidates); % Get the index of the clustered lines based on the real number of lines detected

                % Select candidates based on the longest one

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

                    [maxLenght,maxIdx]=max(longestLine);   
                    selectedLines(i,1)= px1(maxIdx);
                    selectedLines(i,2)= py1(maxIdx);
                    selectedLines(i,3)= px2(maxIdx);
                    selectedLines(i,4)= py2(maxIdx);
                    selectedLines(i,5)= ptheta(maxIdx);
                    selectedLines(i,6)= prho(maxIdx);

                end
            else
                selectedLines=zeros(1,6);
            end
        else
            selectedLines=zeros(1,6);
%             lineStatusFlag=0;            
        end
       
        
    case 2 % Using Color Based Detector
            
            % Process frame.
            videoFrame = inputFrame;
%             videoFrame = imresize (videoFrame,0.65,'bilinear');
            videoFrameGray = rgb2gray(videoFrame);
            videoFrameLines = videoFrame;
            
            if numPts < 10

                % Color Detection
                [BW,maskedI]=createHsvRedMask(videoFrame); % Edit the color mask function if needed
                % figure; imshow(maskedI);
                I=im2bw(maskedI,0.005);
                % figure;imshow(I);
                [centers, radii, metric] = imfindcircles(I,[15 50], 'Sensitivity',0.95);

                if ~isempty(centers)

                    centerS = centers(1:1,:);
                    radiiS = radii(1:1);
                    metricS = metric(1:1);
                    bboxTH=5; % Threshold for drawing the boundary box 
                    bbox=[centerS(1)-radiiS,centerS(2)-radiiS,2*radiiS,2*radiiS];
                    if bbox(1)+2*radiiS>frameSize(2)||bbox(2)+2*radiiS>frameSize(1)||bbox(1)-bboxTH<0||bbox(2)-bboxTH<0
                        zbbox=0;
                        ballPosition=[-100 -100];
                    elseif bbox(1)>=0&&bbox(2)>=0
                        zbbox = 1; 
%                         ballStatusFlag=1;
                        ballPosition=[centerS(1), centerS(2)];
                    else
                        zbbox=0;
                        ballPosition=[-100 -100];

                    end

                    if zbbox>0    
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
                    
                    if bboxPolygon(1)>0&&bboxPolygon(2)>0&&bboxPolygon(3)>0&&bboxPolygon(4)>0&&bboxPolygon(5)>0&&bboxPolygon(6)>0&&bboxPolygon(7)>0&&bboxPolygon(8)>0 
                        
                        % Display a bounding box around the detected ball.
                        videoFrame = insertShape(videoFrame, 'Polygon', bboxPolygon, 'LineWidth', 3);

                        % Display detected corners.
                        videoFrame = insertMarker(videoFrame, xyPoints, '+', 'Color', 'white');
                    end

                    end
                else
                ballPosition=[-100 -100];
%                 ballStatusFlag = 0;
%                 lineStatusFlag = 0;
                end

            else
                    % Tracking mode.
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

            % Display the annotated video frame using the video player object.
            outputFrame=videoFrame;
            
            % Line Detection

        if lineDetectionEnabled==1

%             [image,newOrigin] = undistortImage(videoFrameLines,cameraParams); % Correct image based on camera calibration
            I=im2bw(videoFrameLines,0.5);
            imBW= bwmorph(I,'thin',10);
            % Detect lines
            [H,T,R] = hough(imBW);
            P  = houghpeaks(H,5,'threshold',ceil(0.3*max(H(:))));
            lines = houghlines(imBW,T,R,P,'FillGap',5,'MinLength',7);
            
            if ~isempty(lines)
                
                % Read lines structure and extract points
%                 lineStatusFlag=1;
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
                SumCandidates=1;
                LinesCandidates(1,:)=TRmatrix(1,:);
                
                if ~isempty(TRmatrix)
                    sizeTRmatrix=size(TRmatrix);
                    for i = 1:sizeTRmatrix(1)
                        if TRmatrix(i,2) < 0
                            TRmatrix(i,1) = TRmatrix(i,1) + 180;
                            TRmatrix(i,2) = -TRmatrix(i,2);
                        end
                    end
                end
                
                ThetaTH=10; % Threshold defined for theta difference
                RhoTH=90; % Threshold defined for rho difference

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

                idx=kmeans(TRmatrix, SumCandidates); % Get the index of the clustered lines based on the real number of lines detected

                % Select candidates based on the longest one

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

                    [maxLength,maxIdx]=max(longestLine);   
                    selectedLines(i,1)= px1(maxIdx);
                    selectedLines(i,2)= py1(maxIdx);
                    selectedLines(i,3)= px2(maxIdx);
                    selectedLines(i,4)= py2(maxIdx);
                    selectedLines(i,5)= ptheta(maxIdx);
                    selectedLines(i,6)= prho(maxIdx);

                end
            else
                selectedLines=zeros(1,6);
            end
        else
            selectedLines=zeros(1,6);
        end

        
    otherwise
        
        ballPosition  = [-100 -100];
        selectedLines=zeros(1,6);
        outputFrame=inputFrame;
%         ballStatusFlag = 0;
%         lineStatusFlag = 0;
end           
            
            