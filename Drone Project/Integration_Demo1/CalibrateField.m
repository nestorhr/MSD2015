addpath('E:\ASD\Module 2\Referee Drone\Integration\Trilateration\')
addpath('E:\ASD\Module 2\Referee Drone\Integration\Trilateration\Trilateration_algorithm')

%% Initialize Coordinate System and Anchor System
% SET UP PORT 
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
fscanf(s); % Get init mc out of the way

% INITIALIZE COORDINATE SYSTEM
disp('Setting up Anchor coordinate system')
ref_anch = set_reference(s); % Set up anchor coord system
pause(0.1);

% Calibrate field
[CR1,CR2,CR3,CR4,ref]  = Field_Calib(50,ref_anch,s);

% Create set of plot items
items = [CR1;CR2;CR3;CR4];

% Estimate field sizes
field_x_vec = (CR2 - CR1 + CR3 - CR4)/2;
field_y_vec = (CR4 - CR1 + CR3 - CR2)/2;

field_x = sqrt(field_x_vec(1)^2 + field_x_vec(2)^2);
field_y = sqrt(field_y_vec(1)^2 + field_y_vec(2)^2);

% Save configuration for reuse
save('Config.mat','ref','items','CR1','CR2','CR3','CR4','field_x','field_y');

%% Plot measured coordinate system
%% Initialize Field Plot
% Image loading
field = imread('field.png');
field = field(9:end,5:end,:);
ioffs = 32;
joffs = 37; % Trim edges to only have the field
field = field(ioffs+2:end-ioffs,joffs:end-joffs,:);

% Coordinate system conversion preparation
[nrows,ncols,colval] = size(field); % Get matrix size
field2im_params = [field_x,field_y,nrows,ncols];

% Call init function
fign = init_plot_trilat(field, items, field2im_params);
