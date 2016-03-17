% Author: Nestor Hernandez Rodriguez
% Last Update: 16-03-2016
% Technical University of Eindhoven
% Mechatronic Systems Design PDEng trainee

function [OutOfPitchFlag] = refereeingOutOfPitch(yawAngleDrone,ballPosition,lineWidth,selectedLines,numOutOfBoundLines,frameProperties,droneInPitch,thetaCamX,height,worldModelOuterLines)

% This function updates the OutOfPitchFlag ('0'- inside the pitch, '1'-
% out of the pitch or '-1' not known)
% 
% Inputs:
% yawAngleDrone - yaw angle with respect to the field. Should be calibrated
%   so that the outer lines have the initial value as stated in default.
% 
%   Default: goal line yaw angle = pi/2 rad
%            side lines yaw angle = 0 rad
% 
% ballMdl - Object that contains position of the center, diameter and
%   relative position to the selected lines with respect to the frame and
%   taking into account the height of the drone.
% 
% lineWidth - Width of the lines with respect to the frame and taking into
%   account the height of the drone
% 
% selectedLines - Matrix containing the selected lines points, theta and
%   rho [x1_vector y1_vector x2_vector y2_vector theta_vector rho_vector]
% 
% numOutOfBoundLines - Integer that contains the number of outer lines that
%   the frame should contain
%
% frameProperties - [height width] Size of the frame used after pre-process
%
% dronInPitch - Flag '1' - Inside; '0' outside
%
% worldModelOuterLines - Matrix 4x5 containing ID, InFrameFlag, SideOrGoal
% line identification, rho and theta for the 4 outer lines.
%
% The position of the drone within the frame it is assumed to be in the
% center of the frame as it is a top view camera with a pitch angle of 
% pi/2 rad.



mReferenceSideLine = tan(yawAngleDrone+pi/2); % slope of the side lines
mReferenceGoalLine = tan(yawAngleDrone); % slope of the goal lines
mSlopeTH =abs(mReferenceSideLine-mReferenceGoalLine)*0.6; % Threshold slope matching
sizeSelectedLines=size(selectedLines);
rhoDistanceTH=0.75; % rho threshold in meters

dronePosition=[frameProperties(2)/2 frameProperties(1)/2];

% Calculate pixel to meters conversion factor

pixelDistance = (height*tan(thetaCamX/2))/(frameProperties(2)/2);


outOfBoundsDetector=zeros(sizeSelectedLines(1),1); % Create mask for outer lines

auxCntSide=0;
auxCntGoal=0;
auxCnt=0;

% Calculate mask based on slope comparison
if numOutOfBoundLines == 0
    if ballPosition == [-100 -100]
        OutOfPitchFlag = -1;
    elseif droneInPitch
        OutOfPitchFlag = 0;
    else
        OutOfPitchFlag = 1;
    end        
else
    for i=1:sizeSelectedLines(1)

        mSlope=(selectedLines(i,4)-selectedLines(i,2))/(selectedLines(i,3)-selectedLines(i,1))*(-1); % Y-axis is flipped in the frame

        if mSlope>0
            if mSlope<mReferenceSideLine+mSlopeTH && mSlope>mReferenceSideLine-mSlopeTH
                auxCntSide=auxCntSide+1;
                outOfBoundsDetector(i)=1; % '1' for a correct side line matching
            elseif mSlope<mReferenceGoalLine+mSlopeTH && mSlope>mReferenceGoalLine-mSlopeTH
                    auxCntGoal=auxCntGoal+1;
                    outOfBoundsDetector(i)=2; % '2' for a correct goal line matching
            else
                outOfBoundsDetector(i)=0; % '0' for no matching                    
            end
        else if mSlope>mReferenceSideLine-mSlopeTH && mSlope<mReferenceSideLine+mSlopeTH
                auxCntSide=auxCntSide+1;
                outOfBoundsDetector(i)=1; 
            elseif mSlope>mReferenceGoalLine-mSlopeTH && mSlope<mReferenceGoalLine+mSlopeTH
                    auxCntGoal=auxCntGoal+1;
                    outOfBoundsDetector(i)=2;            
            else
                outOfBoundsDetector(i)=0; % '0' for no matching
            end
        end            

    end 

    % Filter possible parallel lines selected as outer lines based on rho provided as input

    selectedFilteredLines=zeros(2,6); % First row for possible side line and Second row for possible goal line
    auxSideLines=selectedLines(outOfBoundsDetector==1,:);
    sizeAuxSideLines=size(auxSideLines);
    auxGoalLines=selectedLines(outOfBoundsDetector==2,:);
    sizeAuxGoalLines=size(auxGoalLines);

    if sizeAuxSideLines(1)>0
        for j=1:sizeAuxSideLines(1)
        %     if auxCntSide>1

            auxWMSideLines=worldModelOuterLines(worldModelOuterLines(:,2)==1,:); % Filter by the InFrameFlag equal to '1'
            auxWMSideLines1=auxWMSideLines(auxWMSideLines(:,3)==2,:); % Filter by the SideOrGoal flag equal to '1' - Side

                if auxSideLines(j,6)*pixelDistance>auxWMSideLines1(1,5)-rhoDistanceTH && auxSideLines(j,6)*pixelDistance<auxWMSideLines1(1,5)+rhoDistanceTH
                    selectedFilteredLines(1,:)=auxSideLines(j,:); % Side line stored in the first row
                    auxCntSide=1;
                end
        end
    else
       auxCntSide=0;
    end

    if sizeAuxGoalLines(1)>0
        for j=1:sizeAuxGoalLines(1)
        %     if auxCntSide>1

            auxWMGoalLines=worldModelOuterLines(worldModelOuterLines(:,2)==1,:); % Filter by the InFrameFlag equal to '1'
            auxWMGoalLines1=auxWMGoalLines(auxWMGoalLines(:,3)==1,:); % Filter by the SideOrGoal flag equal to '2' - Side

                if auxGoalLines(j,6)*pixelDistance>auxWMGoalLines1(1,5)-rhoDistanceTH && auxGoalLines(j,6)*pixelDistance<auxWMGoalLines1(1,5)+rhoDistanceTH
                    selectedFilteredLines(2,:)=auxGoalLines(j,:); % Goal line stored in the second row
                    auxCntGoal=1;
                end   

        end 
    else
       auxCntGoal=0;
    end

    auxCnt=auxCntSide+auxCntGoal;

    % Calculate relative position for ball and drone respect to the filtered outer lines

    % Calculate Relative Ball Position
    syms x_v2;
    sizeFilteredLines=size(selectedFilteredLines);
    relativeBallPosition=zeros(sizeFilteredLines(1),1);
    relativeDronePosition=zeros(sizeFilteredLines(1),1);

    for k=1:sizeFilteredLines(1) % The size of the filtered selected lines

        a_p=(selectedFilteredLines(k,4)-selectedFilteredLines(k,2))/(selectedFilteredLines(k,3)-selectedFilteredLines(k,1));
        b_p=(-selectedFilteredLines(k,1)*a_p+selectedFilteredLines(k,2));    
        Fline=symfun(a_p*x_v2+b_p,x_v2);

        % Check position with respect to the lines

        if ballPosition(2)>Fline(ballPosition(1))
            relativeBallPosition(k)= 1; % True (x grows -> right; y grows -> down)
        else
            relativeBallPosition(k)= 0; % False      
        end
    end

    % Calculate Relative Drone Position

    for k=1:sizeFilteredLines(1) % The size of the filtered selected lines

        a_p=(selectedFilteredLines(k,4)-selectedFilteredLines(k,2))/(selectedFilteredLines(k,3)-selectedFilteredLines(k,1));
        b_p=(-selectedFilteredLines(k,1)*a_p+selectedFilteredLines(k,2));    
        Fline=symfun(a_p*x_v2+b_p,x_v2);

        % Check position with respect to the lines

        if dronePosition(2)>Fline(dronePosition(1))
            relativeDronePosition(k)= 1; % True (x grows -> right; y grows -> down)
        else
            relativeDronePosition(k)= 0; % False      
        end
    end

    % Update OutOfBounds flag

    switch numOutOfBoundLines

        case 2 % Two outer lines can be found (1 Side line and 1 Goal line -> Corner)

            if auxCnt==2 % If this does not match then the refereeing is not done                

               if droneInPitch==1

                   if relativeDronePosition(1)==relativeBallPosition(1) && relativeDronePosition(2)==relativeBallPosition(2) % Compare to the 2 outer lines

                       OutOfPitchFlag=0; % Not out of pitch

                   else

                       OutOfPitchFlag=1; % Out of pitch
                   end
               end

            else
                OutOfPitchFlag=-1; % Not known

            end


        case 1 % One outer line can be found

            if auxCnt==1
                if auxCntSide==1
                   if droneInPitch==1

                       if relativeDronePosition(1)==relativeBallPosition(1) % Compare to the only outer line

                           OutOfPitchFlag=0; % Not out of pitch

                       else

                           OutOfPitchFlag=1; % Out of pitch
                       end
                   end
                else
                    if droneInPitch==1

                       if relativeDronePosition(2)==relativeBallPosition(2) % Compare to the only outer line

                           OutOfPitchFlag=0; % Not out of pitch

                       else

                           OutOfPitchFlag=1; % Out of pitch
                       end
                    end
                end

            else
                OutOfPitchFlag=-1; % Not known

            end

        otherwise

            OutOfPitchFlag=-1; % Not known

    end
end


    
    