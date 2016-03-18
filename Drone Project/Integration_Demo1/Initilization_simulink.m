clear all; close all; clc;

%% Add function to path
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Trilateration\')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Trilateration\Trilateration_algorithm')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Detection')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Detection\AR_Drone_CamCalibrationSet')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Refereeing')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\World_Model')
addpath('E:\GitHub\MSD2015\Drone Project\Integration_Demo1\Top_View_Camera')

%% Initialize Coordinate System and Anchor System
load('Config.mat') 

%% Load Top View Cam Files
load('background.mat')
load('template_drones1.mat')

%% Initialize Variables
thetaCamX = 58*pi/180;
thetaCamY = 45*pi/180;

%% Initialize Reference Image Cascade Detector
% cam=webcam(3);cl
% preview(cam);
% prompt = 'Press any key to take reference image of the ball to track';
% inputkey = input(prompt);
% ReferenceFrame = snapshot(cam);
% ReferenceImage = imresize (ReferenceFrame,[320 240]);
% prompt = 'Press any key to continue execution';
% inputkey2 = input(prompt);
% closePreview(cam);
% clear cam;
referenceImage = imread('field.png');