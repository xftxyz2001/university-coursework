% 1、利用Matlab的Butterworth方法设计一个低通滤波器，
% 通带截止频率为100Hz，通带衰减为1dB，
% 阻带截止频率为200Hz，阻带衰减为15dB，采样频率为500HZ。
wp=100*2*pi;
ws=200*2*pi;
ap=1;
as=15;
Fs=500;
[N,Wc]=buttord(wp,ws,ap,as,'s');
[Z,P,K]=buttap(N);
[a,b,c,d]=zp2ss(Z,P,K);
[AT,BT,CT,DT]=lp2lp(a,b,c,d,Wc);
[n1,d1]=ss2tf(AT,BT,CT,DT);
[n2,d2]=bilinear(n1,d1,500);
[H,W]=freqz(n2,d2);
plot(W*Fs/(2*pi),abs(H));grid;
xlabel('频率/Hz');
ylabel('幅值');

% 2、利用Matlab设计一个3dB带宽为10kHz，过度带小于等于1kHz的Butterworth高通滤波器。
clear
fs=20;
f1=10;
Fh=11;
wp1=(f1*2*pi)/fs;
ws1=(Fh*2*pi)/fs;
[n,Wn]=buttord(wp1,ws1,1,25,'s');
[b,a]=butter(n,Wn,'s');
[H,W]=freqz(b,a,256);
plot(W*fs/(2*pi),abs(H));
grid;
xlabel('频率/kHz');ylabel('幅度');
