clear all; close all; clc;

cam = gigecam;
set(cam,'PixelFormat','RGB8Packed','Timeout',20)

backim = snapshot(cam);
save('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Top_View_Camera\background.mat','backim');

imshow(backim);

