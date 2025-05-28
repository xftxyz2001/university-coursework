% 1. funtool命令
funtool

% 2. syms函数 & solve函数
syms x
eqn = sin(x) == 1;
sol = solve(eqn, x); % 解：pi/2
disp(sol);

% 方程组求解
syms x y
eqns = [x + y == 3, x - y == 1];
vars = [x y];
[sol_x, sol_y] = solve(eqns, vars); % 解：x=2, y=1
disp([sol_x, sol_y]);

% 3. dsolve函数
% 解微分方程
syms y(x)
ode = diff(y,x) == 1 + y^2;
cond = y(0) == 1;
ySol(x) = dsolve(ode, cond);
disp('微分方程 dy = (1 + y^2)dx, y(0) = 1 的解为:');
disp(ySol);

% 4. 求 sin(t) 在 [0, 2π] 的近似导数
t = linspace(0, 2*pi, 1000);
x = sin(t);
dxdt = diff(x)./diff(t);  % 近似导数
t_diff = t(1:end-1);      % 对应的 t 值（少一个点）
% 绘制结果
figure;
subplot(2,1,1);
plot(t, x);
title('原函数 x = sin(t)');
xlabel('t');
ylabel('x');
subplot(2,1,2);
plot(t_diff, dxdt);
title('近似导数 dx/dt');
xlabel('t');
ylabel('dx/dt');

% 5. 求 ∫(0.2 + sin(t))dt 从 0 到 π/2
t = linspace(0, pi/2, 1000);
y = 0.2 + sin(t);
s = trapz(t, y);  % 梯形法数值积分
disp(['近似数值积分结果为: ', num2str(s)]);

% 6. 求 1 + 1/2^2 + 1/3^2 + ... + 1/k^2 的前十项和
syms k
sum_expr = symsum(1/k^2, k, 1, 10);
disp('前十项和为: ');
disp(vpa(sum_expr, 6));  % 显示6位有效数字

% 7. 求 exp(x) 的泰勒展开
syms x
taylor(exp(x));
