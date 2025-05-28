% 1. 单位阶跃信号
syms x 
fplot(heaviside(x), [-2, 2]);

% 2. 采样函数
t= -10:1/500:10; 
x=sinc(t/pi); 
plot(t,x); 
title('Sa函数信号'); 
xlabel('时间(t)'); 
ylabel('幅值(f)');

% 3. 门函数
width=2; % 设置宽度 
t=-2:0.001:3; % 横坐标的取值 
ft=rectpuls(t,width); % 调用格式为rectpuls(x,y) 
plot(t,ft); 
grid on; % 显示网格 
ylim([-0.5 1.5]); % ylim(limits) 设置当前坐标区或图的y

% 4. 三角脉冲
x=-10:0.001:10
y=tripuls(x,5)
plot(x,y)
xlim([-10.7 11.3])
ylim([0.01 1.11])

% 5. 周期方波
t = linspace(0,50,1000)';
x = square(t,50);
plot(t,x,'.-')
xlabel('t')
grid on
xlim([18.4 39.7])
ylim([-1.24 1.42])

% 6. 锯齿波
T = 10*(1/50);
fs = 1000;
t = 0:1/fs:T-1/fs;
x = sawtooth(2*pi*50*t);
plot(t,x)
grid on


% 2、利用matlab编程实现如下图所示信号f(t)的变化：f(-t)、f(t+2)、f(-t+2)和f(2-2t)，画出相应图形。
clear
t0=-5:0.01:5;                         
t=t0;                                        
ft=(-t-1).*(heaviside(t+1)-heaviside(t))-(heaviside(t)-heaviside(t-1))+(heaviside(t-1)-heaviside(t-2)); 
figure(1)
subplot(1,1,1)
plot(t0,ft)
xlabel('t');
ylabel('f(t)');

t1=-t;                   
t=t1;                     
ft=(-t-1).*(heaviside(t+1)-heaviside(t))-(heaviside(t)-heaviside(t-1))+(heaviside(t-1)-heaviside(t-2));
figure(2);
subplot(2,2,1)
plot(t0,ft);
xlabel('t1');
ylabel('f(-t)');

t2=t0+2;
t=t2;
ft=(-t-1).*(heaviside(t+1)-heaviside(t))-(heaviside(t)-heaviside(t-1))+(heaviside(t-1)-heaviside(t-2));
figure(2)
subplot(2,2,2)
plot(t2,ft);
xlabel('t2');
ylabel('f(t+2)');

t3=-t0+2;
t=t3;
ft=(-t-1).*(heaviside(t+1)-heaviside(t))-(heaviside(t)-heaviside(t-1))+(heaviside(t-1)-heaviside(t-2));
figure(2)
subplot(2,2,3)
plot(t3,ft);
xlabel('t3');
ylabel('f(-t+2)');

t4=2-2*t0;
t=t4;
ft=(-t-1).*(heaviside(t+1)-heaviside(t))-(heaviside(t)-heaviside(t-1))+(heaviside(t-1)-heaviside(t-2));
figure(2)
subplot(2,2,4)
plot(t4,ft);
xlabel('t4');
ylabel('f(2-2t)');


% 3、利用matlab实现连续时间信号的卷积图解法
clear;
T=0.01;
t1=-2;
t2=3;
t3=-2;
t4=2;
t5=t1:T:t2;
t6=t3:T:t4;
f1=rectpuls(t5,0.5);
f2=0.5*rectpuls(t6,1);
y=conv(f1,f2);
y=y*T;
t=(t1+t3):T:(t2+t4);
subplot(3,1,1);
plot(t5,f1 );
subplot(3,1,2)
plot(t6,f2);
subplot(3,1,3)
plot(t,y);
