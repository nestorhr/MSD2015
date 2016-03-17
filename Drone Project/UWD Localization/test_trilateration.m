%% Script Purpose
% Script used to demonstrate 

%% Initialize serial bus
clear all; close all; clc;
% Config exists? -> Init = 0, if Init required -> Init = 1;
init = 0;
% Clear any existing serial ports in the system
ports = instrfind;
if ~isempty(ports)
    fclose(ports);
    delete(ports);
end

% Establish new connection
s = serial('COM33','BaudRate',9600,'Parity','None');

% Open connection
fopen(s);
a = fscanf(s); % Get init mc out of the way

%% Import functions
addpath('E:\ASD\Module 2\Referee Drone\DecaWave\Matlab Files\Trilateration\');

%% Initialize Coordinate System
if init % Initialization is required
    disp('Setting up Anchor coordinate system')
    ref_anch = set_reference(s); % Set up anchor coord system
    pause(0.1);
    
    % Calibrate field
    [CR1,CR2,CR3,CR4,ref]  = Field_Calib(100,ref_anch,s);
    
    % Create set of plot items
    items = {CR1, 'Corner 1;';CR2, 'Corner 2';CR3, 'Corner 3';CR4, 'Corner 4'};
    
    % Save configuration for reuse
    save('Config.mat','ref','items','CR1','CR2','CR3','CR4');
else % Initialization is not required, an existing Config.mat is suitable
   load('Config.mat') 
end

%% Initialize Field Plot
% Image loading
field = imread('field.png');
field = field(9:end,5:end,:);
ioffs = 32;
joffs = 37; % Trim edges to only have the field
field = field(ioffs+2:end-ioffs,joffs:end-joffs,:);

% Coordinate system conversion preparation
[nrows,ncols,colval] = size(field); % Get matrix size

field_x = abs(CR1(1) - CR2(1) + CR4(1) - CR3(1))/2; % Estimate field sizes
field_y = abs(CR4(2) - CR1(2) + CR3(2) - CR2(2))/2;
field2im_params = [field_x,field_y,nrows,ncols];

% Call init function
fign = init_plot_trilat(field, items, fign, field2im_params);

% Set up plot variables to plot location
k = 1;
plots = [];
nrplots = 10;
pause
disp('Press enter to continue to Trilateration');

%% Trilateration
for i = 1:1000
    % Get Measurement
    dist = GetMC(s,'mc');
    
    % Trilaterate
    P = Trilateration(ref',dist(1:3),eye(3));
    
    % Plot and print results
    [plots, k] = update_plot_trilat(plots, k, fign, P(2:3), field2im_params, nrplots);
    fprintf('%.2f\t%.2f\t%.5f\n',P(2),P(3),P(1)-(P(2)^2+P(3)^2+P(4)^2))
end

%% Close serial bus
fclose(s);
delete(s)

