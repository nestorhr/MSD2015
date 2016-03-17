function dist = GetMC(s,id) 
    % Input: Serial Port to A0
    %        
    % Output: Raw data for triangulation
    %
    % Message syntax is explained in the Decawave documentation
    % DecaRangeRTLS_PC_Source_Code_Guide.pdf  - Section 2.3.2
    % DecaRangeRTLS_ARM_Source_Code_Guide.pdf - Section 2.6

    % Make sure to get a measurement with the correct identifier
    Ms = fscanf(s); % DO...WHILE, so do first measurement first
    count = 1;      % Set counter
    while ~strcmp(Ms(1:2),id) % Compare Measurement ID with given ID
        Ms = fscanf(s);        % Get new message
        count = count + 1;     % Increment count
        if count > 10          % If counter expires -> Error
            error('Identifier not found in first 10 messages')
        end
    end
    
    Ms_spl = strsplit(Ms); % Split message in separate fields by ' '
    
    dist = [];
    for i = 3:6
       % Transform each field to decimals
       % Transform each field to meters
       % Get all 4 range identifiers
       % Output variable -> dist
       dist(end+1) =  hex2dec(Ms_spl{i})/1000;
    end
end
    
    