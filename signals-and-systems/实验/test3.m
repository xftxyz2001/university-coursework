% 1、利用matlab绘制单位冲激响应（impulse函数）和单位阶跃响应（step函数）
% 2y'' + 7y' + 3y = f(t)
sys = tf([1],[2,7,3]);
t = 0:0.1:10;
y=impulse(sys,t);
plot(t,y)
title('冲激响应1')

sys = tf([1],[2,7,3]);
t = 0:0.1:10;
y=step(sys,t);
plot(t,y)
title('阶跃响应1')

% y'' + 3y' + 2y = f'(t) + f(t)
sys = tf([1,1],[1,3,2]);
t = 0:0.1:10;
y=impulse(sys,t);
plot(t,y)
title('冲激响应2')

sys = tf([1,1],[1,3,2]);
t = 0:0.1:10;
y=step(sys,t);
plot(t,y)
title('阶跃响应2')


% 例1: y'' + 2y' + 4y = f'(t) + f(t)
num = [1 1];   % 传递函数分子多项式系数，对应 s + 1
den = [1 2 4]; % 传递函数分母多项式系数，对应 s^2 + 2s + 4
sys = tf(num, den); 
t = 0:0.01:10; % 时间向量：从0开始，步长0.01，到10结束，确定计算响应的时间范围

% 绘制单位冲激响应
y_impulse = impulse(sys, t); % 计算单位冲激响应
figure; % 创建新的绘图窗口
plot(t, y_impulse);
title('单位冲激响应');
xlabel('时间t');
ylabel('h(t)');

% 绘制单位阶跃响应
y_step = step(sys, t); % 计算单位阶跃响应
figure; % 再创建一个新的绘图窗口
plot(t, y_step);
title('单位阶跃响应');
xlabel('时间t');
ylabel('g(t)');


% 例2: h(t) = (e^(-2t) + e^(-3t)) * u(t) ; f(t) = e^(-t) * u(t)
t = 0:0.1:5;
h = exp(-2*t)+exp(-3*t);
f = exp(-t).* (t >= 0); % 修正输入激励，确保符合u(t)特性
yf = conv(h,f);
dt = 0.1; % 时间步长
t_new = (0:length(yf)-1)*dt; % 重新生成时间轴
figure(1);
plot(t_new,yf);
title('conv系统零状态响应');
xlabel('t');
ylabel('零状态响应值');


% 3、原微分方程: y''(t) + 3y'(t) + 2y(t) = f'(t) + f(t)
% 拉普拉斯变换后: H(s) = (s + 1)/(s^2 + 3s + 2)
num = [1 1];    % 分子多项式系数: s + 1
den = [1 3 2];  % 分母多项式系数: s^2 + 3s + 2
sys = tf(num, den);
%% 计算极点
poles = roots(den);  % 求分母多项式的根
%% 判断稳定性
is_stable = true;
for pole = poles'
    if real(pole) >= 0
        is_stable = false;
        break;
    end
end
%% 输出结果
fprintf('系统函数: H(s) = ');
disp(sys);
fprintf('极点: s = %.1f, s = %.1f\n', poles(1), poles(2));
if is_stable
    disp('系统稳定性: 稳定（所有极点位于左半平面）');
else
    disp('系统稳定性: 不稳定');
end
%% 绘制零极点图验证
figure('Color','white');
pzmap(sys);  % 绘制零极点分布
title('系统零极点分布');
grid on;


% 4、y''(t) + 3y'(t) + 2y(t) = f'(t) + f(t)的系统搭建及响应分析
model = 'system_response';
new_system(model);
open_system(model);

% 添加正弦输入模块
add_block('simulink/Sources/Sine Wave', [model '/Sine Input']);
set_param([model '/Sine Input'], 'Amplitude', '1', 'Frequency', '2', 'Phase', '0');

% 添加传递函数模块
add_block('simulink/Continuous/Transfer Fcn', [model '/System']);
set_param([model '/System'], 'Numerator', '[1 1]', 'Denominator', '[1 3 2]');

% 添加输出模块
add_block('simulink/Sinks/Scope', [model '/Output Scope']);
add_block('simulink/Sinks/To Workspace', [model '/To Workspace']);
set_param([model '/To Workspace'], 'VariableName', 'y_out', 'SaveFormat', 'Structure');

% 连接模块
add_line(model, 'Sine Input/1', 'System/1');
add_line(model, 'System/1', 'Output Scope/1');
add_line(model, 'System/1', 'To Workspace/1');
% 设置仿真参数
set_param(model, 'Solver', 'ode45', 'StopTime', '10', 'FixedStep', '0.01');
% 保存并运行仿真
save_system(model);
simOut = sim(model, 'ReturnWorkspaceOutputs', 'on');
sys = tf([1 1], [1 3 2]);  % 定义传递函数
step(sys);                  % 绘制阶跃响应曲线
S = stepinfo(sys);          % 提取阶跃响应参数
% 输出参数
peak_time = S.PeakTime;         % 峰值时间（一阶系统无峰值，返回NaN）
overshoot = S.Overshoot;        % 超调量（0%）
rise_time = S.RiseTime;         % 上升时间（10%到90%）
settling_time = S.SettlingTime; % 调节时间（2%误差带）
disp(['峰值时间: ', num2str(peak_time)]);
disp(['超调量: ', num2str(overshoot), '%']);
disp(['上升时间: ', num2str(rise_time)]);
disp(['调节时间: ', num2str(settling_time)]);
