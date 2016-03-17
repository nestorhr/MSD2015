clear all; close all; clc;

%% Add function to path
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\Trilateration\')
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\Trilateration\Trilateration_algorithm')
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\Detection')
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\Detection\AR_Drone_CamCalibrationSet')
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\Refereeing')
addpath('C:\Users\nhernand\Dropbox\MSD\referee_drone\matlab\Integration_Demo1\World_Model')

%% Initialize Coordinate System and Anchor System
load('Config.mat') 

%% Calibrate Camera
if 0
    AR_Drone_CamCalibration
    save('CameraParams','cameraParams')
else
    load('CameraParams.mat')
end