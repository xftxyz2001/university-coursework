% 1、绘制波形图
% t=-10:0:01:10;
% f='sin(t)/t';
% % ezplot(f,t);
% fplot(@(t)sin(t)./t);
% grid on;
syms t
f=sinc(t)
fplot(f)

% 2、选择奈奎斯特采样频率对其离散化，画出离散化后的波形图；
t1=-15:0.5:15;
f1=sinc(t1/pi);
stem(t1,f1)

% 3、选取合适的理想低通滤波器由的采样值恢复，并画出恢复后的波形图；
n=-100:100;
ws=5;
wc=ws/2;
wm=wc;
ts=pi/wm;
nts=n*ts; 
f=sinc(nts/pi);
dt=0.005;
t=-15:dt:15;
fa=f*ts*wc/pi*sinc((wc/pi)*(ones(length(nts),1)*t-nts'*ones(1,length(t))));
plot(t,fa)

% 4、选择低于奈奎斯特采样频率的采样率对其离散化，画出采样信号的频谱图；
% 选择合适的理想低通滤波器恢复原信号，画出其波形，计算其和原信号之间的均方误差；
t=-15:0.5:15
%f1='sin(t)/t'
f=sinc(t/(1.5*pi))
subplot(2,1,1)
stem(t,f)

wm=0.5
Ts=pi*1*5
wc=wm
n=-100:100
nts=n*ts

f=sinc(nts/pi);
dt=0.005;
t=-15:dt:15;
fa=f*ts*wc/pi*sinc((wc/pi)*(ones(length(nts),1)*t-nts'*ones(1,length(t))));
subplot(2,1,2)
plot(t,fa)
grid on

error=abs(fa-sinc(t/pi))
x=sum(error.^2)/length(error)
%plot(t,error)

