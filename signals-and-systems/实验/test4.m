% 1、1 利用Matlab符号运算fourier函数和ifourier函数，以符号形式画出门函数的傅里叶正反变换。
syms t
y=heaviside(t+1)-heaviside(t-1);
ezplot(y,[-2,2]);
F=fourier(y);
figure;
ezplot(abs(F),[-10,10]);
figure;
iF=ifourier(y);
ezplot(abs(iF));

% 1、2 利用matlab的fft和ifft函数求冲激函数的傅里叶正反变换
t=-10:0.1:10;
f=dirac(t);
f=sign(f);
plot(f)
figure;
F=fft(f);
plot(t,abs(F))
figure;
iF=ifft(f);
plot(t,abs(iF))


% 2、利用Matlab的quad函数用数值分析的方法近似计算三角波信号 x(t)=1-|t| t<=1 的频谱；
clear
w=linspace(-6*pi,6*pi,512); % 均分指令linspace(x1,x2,N) x1为起始值，x2为终点值，N为元素个数
figure(1)
plot(w)

N=length(w);                          %返回到该行数中的最大的值
X=zeros(1,N);                         %生成一个1行N列的零矩阵

for k=1:N
    X(k)=quad(@sf,-1,1,[],[],w(k));
end
figure(2)
subplot(121);
plot(w,real(X));
xlabel('\omega');
ylabel('X(j\omega)');
title('Spectrum of Triangle wave');


% 3、1 分别画出其傅里叶级数展开式前三项之和、前十项之和的图形，
% 分别计算其和原信号之间的均方误差，分析图形和误差变化的原因；（E=1）
clear;
T=20;
w=2*pi/T;
t=0:0.01:20;
f1=1/2+2/pi*sin(w*t)+2/pi*1/3*sin(3*w*t);    %傅里叶级数展开式前三项的和
figure
plot(f1)
xlabel('t')
ylabel('f1(t)')

f10=f1;
for n=5:2:17
    f10=f10+2/pi*1/n*sin(n*w*t);
end
figure;
plot(f10)
xlabel('t')
ylabel('f10(t)')

%计算均方误差
clear;

for i=1:60
    a(i)=cumpt(i);
    if i==3
        a(3)
    end
    if i==10
        a(10)
    end
end


% 3、2 编程画出傅里叶级数的项数（<100）和与均方误差之间的关系曲线，
% 并在图中标出均方误差小于等于0.01时所需要的项数。
x=1:1:60;
p=find(a<=0.01)
p(1)
plot(x,a);
xlabel('n');
ylabel('均方误差');
text(p(1),a(p(1)),'o','color','g')

