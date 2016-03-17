function ref = set_reference(s, ref_in)
% Ref is the reference for the anchors
% Ref = [Xa Ya; Xb Yb; Xc Yc]
% The Z coordinate of the anchors should be the same
% If Ref is empty, this function constructs one from the MA data
% s is the serial connection to Anchor 0
    
    if nargin == 2 & (size(ref_in) == [3 3])
        %Check if a reference is given and if it is of valid size
        ref = ref_in;
    else
        %Else, construct from 'ma' messages
        %Gather messages
        ranges = [];
        flushinput(s);
        for i = 1:100
            % Save range information in matrix
            ranges(end+1,:) = GetMC(s,'ma');
        end
        
        % Get anchor distances from ranges
        a0_a1 = ranges(:,2);
        a0_a2 = ranges(:,3);
        a1_a2 = ranges(:,4);
        
        % Get average distances
        a0_a1_avg = mean(a0_a1);
        a0_a2_avg = mean(a0_a2);
        a1_a2_avg = mean(a1_a2);
        
        % Calculate reference coordinates
            % Coordinates for anchor 3
        xc = (a0_a1_avg^2 + a0_a2_avg^2 - a1_a2_avg^2)/(2*a0_a1_avg);
        yc = sqrt(a0_a2_avg^2 - xc^2);
            % Reference Matrix
        ref = [0 0 0; a0_a1_avg 0 0; xc yc 0];
        
        % Print distances + confidence interval
        fprintf('Distances between anchors with 95%% confidence\n')
        fprintf('Distance A0 to A1: %.1f +- %.1f\n',a0_a1_avg,2*std(a0_a1));
        fprintf('Distance A0 to A2: %.1f +- %.1f\n',a0_a2_avg,2*std(a0_a2));
        fprintf('Distance A1 to A2: %.1f +- %.1f\n',a1_a2_avg,2*std(a1_a2));
    end
    
    % Print anchor coordinates
    fprintf('Reference:\t(%.2f, %.2f)\t(%.2f, %.2f)\t(%.2f, %.2f)\n',ref(1,1),ref(1,2),ref(2,1),ref(2,2),ref(3,1),ref(3,2))

    % Plot reference 
    figure, hold on
    for i = 1:3
        plot(ref(i,1),ref(i,2),'*','markersize',15)
    end
    x = axis;
    axis([x(1)-0.5 x(2)+0.5 x(3)-0.5 x(4)+0.5]);
    legend('A0','A1','A2','location','eastoutside')
end