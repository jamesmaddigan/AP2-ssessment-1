clc;
close all;
clear all;

f = 500;
Fs = 48000;
T = 1/Fs;
s = 3;
N = s*Fs;
t_samples = linspace(1,s*Fs, s*Fs)';
t_seconds = (0:3*Fs-1)'*T;

input = linspace(N,1);
%[input,Fs] = audioread(piano.wav);
arctan = linspace(N,1);
parallel_arcTan = linspace(N,1);
parallel_cubic = linspace(N,1);
parallel_soft_combined = linspace(N,1);
hardClip = linspace(N,1);
cubic = linspace(N,1);
arc_cubic_parallel = linspace(N,1);
bitcrush = linspace(N,1);

%==========================================================================
%Paramaters

arc_alpha = 12;
cubic_alpha = 2.2;
arcTan_ratio = 0.5;
cubic_ratio = 1 - arcTan_ratio;
threshold = 0.6;

for n = 1:N
input(n) = sin(2*pi*f*T*n);
end

figure(1);
plot(t_samples, input);
title("Input Sine Wave");
xlim([0 3*(Fs/f)]);
ylim([-1 1]);

%==========================================================================


for n = 1:N
    
arcTan(n) = atan(1*(arc_alpha * input(n)))/atan(arc_alpha);
end
figure(2);
plot(t_samples, arcTan);
title("arcTan distortion");
hold on;
xlim([0 3*(Fs/f)]);
ylim([-1 1]);
plot(t_samples, input);
hold off;




%==========================================================================

for n = 1:N 
    cubic(n) = cubic_alpha * (input(n) - (cubic_alpha * (1/3) * input(n).^3));
end

figure(3);
plot(t_samples, cubic);
title("Cubic Distortion");
hold on;
xlim([0 3*(Fs/f)]);
ylim([-1 1]);
plot(t_samples, input);
hold off;


%==========================================================================

for n = 1:N
    parallel_arcTan(n) = arcTan_ratio * atan(1*(arc_alpha * input(n)))/atan(arc_alpha);
    parallel_cubic(n) = cubic_ratio * cubic_alpha * (input(n) - (cubic_alpha * (1/3) *input(n).^3));
    parallel_soft_combined(n) = (parallel_arcTan(n) + parallel_cubic(n));
end

figure(4);
plot(t_samples, parallel_soft_combined);
title("ArcTan and cubic distrotion in Parallel");
hold on;
xlim([0 3*(Fs/f)]);
ylim([-1 1]);
plot(t_samples, input);
hold off;

%==========================================================================


for n = 1:N
    
    hardClip(n) = parallel_soft_combined(n);
    if (hardClip(n) > threshold)
        hardClip(n) = threshold;
    end
    if (hardClip(n) < - threshold)
        hardClip(n) = -threshold;
    end
end
figure(5);
plot(t_samples, hardClip);
title("Hard Clipping Distortion");
hold on;
xlim([0 3*(Fs/f)]);
ylim([-1 1]);
plot(t_samples, input);
hold off;

%=========================================================================

for n = 1:N
    nBits = 4;
    ampValues = 2^(nBits - 1);
    bitcrush(n) = ceil(ampValues * input(n)) * (1/ampValues);
    
    
end

figure(6);
plot(t_samples, bitcrush);
title("Bit reduction Distortion");
hold on;
xlim([0 3*(Fs/f)]);
ylim([-1 1]);
plot(t_samples, input);
hold off;








