function frame = getFramePi()
    persistent cam rpi
    
    if isempty(cam)
        rpi = raspi();
        cam = cameraboard(rpi, 'Resolution', '320x240', 'FrameRate', 5);
    end
    
    frame = snapshot(cam);
end