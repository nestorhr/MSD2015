function frame = getFramePi()
    persistent cam rpi
    
    if isempty(cam)
        rpi = raspi();
        cam = cameraboard(rpi, 'Resolution', '640x480', 'FrameRate', 20);
    end
    
    frame = snapshot(cam);
end