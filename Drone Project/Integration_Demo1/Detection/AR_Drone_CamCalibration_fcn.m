% Auto-generated by cameraCalibrator app on 09-Mar-2016
%-------------------------------------------------------

function cameraParams = AR_Drone_CamCalibration_fcn()
% Define images to process
imageFileNames = {'c1.png','c2.png','c3.png','c4.png','c5.png','c6.png','c7.png','c8.png','c9.png','c10.png','c11.png','c12.png','c13.png','c14.png'};

% Detect checkerboards in images
[imagePoints, boardSize, imagesUsed] = detectCheckerboardPoints(imageFileNames);
imageFileNames = imageFileNames(imagesUsed);

% Generate world coordinates of the corners of the squares
squareSize = 30;  % in units of 'mm'
worldPoints = generateCheckerboardPoints(boardSize, squareSize);

% Calibrate the camera
[cameraParams, imagesUsed, estimationErrors] = estimateCameraParameters(imagePoints, worldPoints, ...
    'EstimateSkew', false, 'EstimateTangentialDistortion', false, ...
    'NumRadialDistortionCoefficients', 2, 'WorldUnits', 'mm');
end
