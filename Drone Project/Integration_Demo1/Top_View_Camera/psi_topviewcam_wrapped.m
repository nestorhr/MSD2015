function [epsi,img] = psi_topviewcam_wrapped(backim, drone1)
    
    persistent camObj height width
    
    if isempty(camObj)
%         define camObj
        camObj = gigecam;
        set(camObj,'PixelFormat','RGB8Packed','Timeout',20)
    
%         camObj = webcam;
        [height,width,~] = size(snapshot(camObj));
    end

% define number of drones
N = 1;

% load template_drones1
% % pattern drone
 [n1,n2,~] = size(drone1);
 size_pattern = [n1 n2];
% drone{1} = drone1;
% drone{2} = drone2;
% 
% % Xm = 0;
% % Ym = 0;
% 
% drawArrow1 = @(x,y) quiver( x(1),y(1),x(2)-x(1),y(2)-y(1),0,'linewidth',2,'color','y','MaxHeadSize',15) ;
% drawArrow2 = @(x,y) quiver( x(1),y(1),x(2)-x(1),y(2)-y(1),0,'linewidth',2,'color','b','MaxHeadSize',15) ;


% load background
% while runLoop
    % variable initialization
    numFrames = 1;
    xc = zeros(N,numFrames);
    yc = zeros(N,numFrames);
    phi = zeros(N,numFrames);
    cleanim = zeros(height,width,3,numFrames);
    img = zeros(height,width,3,numFrames);
    
    % back = median(backim,4);
    for k = 1:numFrames
        img = snapshot(camObj);
        cleanim = img - backim;
        
        % conversion in black-white picture
        bw_clean = im2bw(uint8(cleanim),0.09);
        
        % identify the regions and their properties in the bw picture
        stat = regionprops(logical(bw_clean),'Centroid','Area','Orientation','BoundingBox');
        
        if ~isempty(stat)
            clear all_corr,
            all_corr = zeros(length(stat),2,N);
            for ir = 1:length(stat)
                
                if stat(ir).Area > 200
                    %%% drone identification %%%
                    
                    % bounding box
                    xb = stat(ir).BoundingBox(1);
                    yb = stat(ir).BoundingBox(2);
                    xb_width = stat(ir).BoundingBox(3);
                    yb_width = stat(ir).BoundingBox(4);
                    
                    end_yb = round(yb+yb_width);
                    if end_yb > height
                        end_yb = height;
                    end
                    
                    end_xb = round(xb+xb_width);
                    if end_xb > width
                        end_xb = width;
                    end
                    
                    droneIm = cleanim(round(yb):end_yb, ...
                        round(xb):end_xb,:);
                    
                    rotIm1 = imrotate(droneIm,90-stat(ir).Orientation);
                    rotIm1 = imresize(rotIm1,size_pattern);
                    rotIm2 = imrotate(rotIm1,180);
                    
                    % Correlation coefficient
                    C = zeros(N,2);
                    numDrone = 1; %added line
%                     for numDrone = 1:N
                        template = drone1;
                        corr = corrcoef(double(rotIm1),double(template));
                        C(numDrone,1) = corr(2,1);
                        corr = corrcoef(double(rotIm2),double(template));
                        C(numDrone,2) = corr(2,1);
%                     end
                    
                    [i,direction] = find(C==(max(max(C))));
                    all_corr(ir,:,i) = [direction,C(i,direction)];
                    
                end
            end
            
            
            for i = 1:N
                
                [~,sortI] = sort(all_corr(:,2,i),'descend');
                ir = sortI(1);
                direction = all_corr(ir,1,i);
                
                % centroid
%                 xc(i,k) = stat(ir).Centroid(1);
%                 yc(i,k) = stat(ir).Centroid(2);
                
                % orientation
                if direction == 1
                    phi(i,k) = -stat(ir).Orientation;
                elseif direction == 2
                    phi(i,k) = -stat(ir).Orientation + 180;
                end
                
%                 l = 30; % lenght arrow
                % extremes of the arrow
%                 x1(i,:) = [xc(i,k)-l*cosd(phi(i,k)) xc(i,k)+l*cosd(phi(i,k))];
%                 y1(i,:) = [yc(i,k)-l*sind(phi(i,k)) yc(i,k)+l*sind(phi(i,k))];
            end
            
%             xo=957.70
%             yo=518.550
%             Xm=(-xo+xc)*(.0068)
%             Ym=(yo-yc)*(.0068)
            %     save ('camdata.mat','Xm','Ym','phi')
            %
            %              xo=210.99
            %  yo=1009.6                              % 0,0 at bottom left
            %  Xm=(xc)*(.0064)
            %  Ym=(yo-yc)*(.0064)
            
            phi=phi+90 ;     % to remove -90 offset
            
            if phi<180
                phi=180+phi;        % to get angle in body frame
            else
                phi=-(180-phi);
            end
            
            if phi>180         % to have -ve psi
                phi=-(360-phi);
            else
                phi=phi;
            end
            
            
            
%             save ('camdata.mat','Xm','Ym','phi')
            
            
            
            
        end
        
    end
    %         figure(1),drawnow
    %         imshow(uint8(img));
    %         hold on,
    %         drawArrow1(x1(1,:),y1(1,:));
    %         drawArrow2(x1(2,:),y1(2,:));
    %         plot(xc(:,k),yc(:,k),'m.','MarkerSize',20)
    %         hold off
    %         legend('drone 1','drone 2','centroid')
    
    
    
% end

epsi = phi;
       
end