clear all
close all
clc

%% sampling time controller
dt = 1/250;%1e-3;

Renu2ned = [0, 1, 0;
            1, 0, 0;
            0, 0, -1];
RtoNed = [1 0 0;
          0 -1 0;
          0 0 -1];
%% Drone Parameters
g = 9.81;
mass = 3.294; %Kg
J = diag([0.1, 0.1, 0.01]); %inertia matrix

kf = 0.858;
km = 0.176;
L = 0.3;

%% Thresholds
roll_max = deg2rad(30);
pitch_max = deg2rad(30);
yaw_rate = 0.3;
thrust_max = 2*g*mass;

%% RC offsets
roll_offset = 0.028;
pitch_offset = 0.028;
yaw_offset = 0.028;
thrust_offset = 0.075;

%% Gains
Kp_pos = diag([1.0, 1.0, 1.0]);
Kd_pos = diag([0.001, 0.001, 0.001]);

Kp_orien = diag([15.0, 15.0, 15.0]);
Kd_orien = diag([1.0, 1.0, 1.0]);

% sat = 3.5;
ei = [0,0,0]';
eir = [0,0,0]';

%% Allocation Matrix
%Terna NED
% M1_sign = -1;
% M1_ang = deg2rad(45);
% M2_sign = -1;
% M2_ang = deg2rad(215);
% M3_sign = 1;
% M3_ang = deg2rad(325);
% M4_sign = 1;
% M4_ang = deg2rad(135);
M1_sign = -1;
M1_ang = deg2rad(45);
M2_sign = -1;
M2_ang = deg2rad(225);
M3_sign = 1;
M3_ang = deg2rad(315);
M4_sign = 1;
M4_ang = deg2rad(135);

angles = [M1_ang, M2_ang, M3_ang, M4_ang];
P = [M1_sign, M2_sign, M3_sign, M4_sign];

zita1 = [cos(angles(1)); sin(angles(1)); 0] * L;
zita2 = [cos(angles(2)); sin(angles(2)); 0] * L;
zita3 = [cos(angles(3)); sin(angles(3)); 0] * L;
zita4 = [cos(angles(4)); sin(angles(4)); 0] * L;

nR = [0;0;-1];

tau1 = cross(kf * zita1, nR) + P(1) * km * nR;
tau2 = cross(kf * zita2, nR) + P(2) * km * nR;
tau3 = cross(kf * zita3, nR) + P(3) * km * nR;
tau4 = cross(kf * zita4, nR) + P(4) * km * nR;

A = [-kf, -kf, -kf, -kf;
     tau1, tau2, tau3, tau4];

A_inv = inv(A);