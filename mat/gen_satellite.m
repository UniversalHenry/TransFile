% generate satellite
% Henry Lu 19.04.12

%% process
close all;clear;clc;
num = 2000 + int16(1000 * rand());
sat = gen_sat(num);    % num = needed point number
scatter3(sat{1}(:,1),sat{1}(:,2),sat{1}(:,3),'filled','g');
hold on;
scatter3(sat{2}(:,1),sat{2}(:,2),sat{2}(:,3),'filled','r');
scatter3(sat{3}(:,1),sat{3}(:,2),sat{3}(:,3),'filled','b');
axis([-1,1,-1,1,-1,1]);
points = [ones(size(sat{1},1),1),sat{1};
        ones(size(sat{2},1),1)*2,sat{2};
        ones(size(sat{3},1),1)*3,sat{3}];
fid1 = fopen('points.txt','w');
r = size(points,1);
for i = 1:r
    fprintf(fid1,'%f\t',points(i,:));
    fprintf(fid1,'\n');
end
fclose(fid1);
%% generate hub

% cylindricity
function shape = gen_cyl_shape(last_point)
start_y = last_point(2);
if rand() > 0.5     % continuous
    start_x = last_point(1);
else    % not continuous
    start_x = rand() * 0.2 + 0.05;
end
if rand() > 0.5   % ordinary line
    end_x = rand() * 0.2 + 0.05;
    end_y = start_y + rand() * 0.15 + 0.1;
else    % straight line
    end_x = start_x;
    end_y = start_y + rand() * 0.15 + 0.1;
end
shape = {1,[start_x,start_y;end_x,end_y]};
end

% cuboid
function shape = gen_cub_shape(last_point)
start_y = last_point(2);
if rand() > 0.2     % square
    end_x = rand() * 0.2 + 0.05;
    end_z = end_x;
else    % rectangle
    end_x = rand() * 0.2 + 0.05;
    end_z = rand() * 0.2 + 0.05;
end
end_y = start_y + rand() * 0.15 + 0.1;
shape = {2,[end_z,start_y;end_x,end_y]};
end

% generate hub points
function points = gen_hub(num,body)
hub = {};
x_max = 0;
y_max = 0;
for i = 1:body
    if rand() > 0.2
        if i == 1
            hub{i} = gen_cyl_shape([0,0]);
        else
            hub{i} = gen_cyl_shape(hub{i-1}{2}(2,:));
        end
    else
        if i == 1
            hub{i} = gen_cub_shape([0,0]);
        else
            hub{i} = gen_cub_shape(hub{i-1}{2}(2,:));
        end
    end
    x_max = max(hub{i}{2}(2,1),x_max);
    y_max = max(hub{i}{2}(2,2),y_max);
end
t = 0;
points_rec = zeros(num,3);
while true
    y = rand() * y_max;
    x = (1 - rand()^2) * x_max;
    z = 0;
    b = 0;
    for i = 1:body
        if hub{i}{2}(2,2) > y && hub{i}{2}(1,2) <= y && x <= hub{i}{2}(2,1)
            b = i;
            if hub{i}{1} == 1
                x_ = (hub{i}{2}(2,1) - hub{i}{2}(1,1)) * (y - hub{i}{2}(1,2)) / (hub{i}{2}(2,2) - hub{i}{2}(1,2)) + hub{i}{2}(1,1);
                if x_ < x
                    b = 0;
                end
            end
            break;
        end
    end
    if b == 0
        continue
    end
    y = y_max - y;
    if hub{i}{1} == 1
        theta = 2*pi*rand();
        z = sin(theta)*x;
        x = cos(theta)*x;
    else
        z = (-1) ^ (rand()>0.5) * hub{i}{2}(1,1) * rand();
        x = x * (-1) ^ (rand()>0.5);
    end
    t = t + 1;
    points_rec(t,1) = x;
    points_rec(t,2) = y;
    points_rec(t,3) = z;
    if t == num
        break
    end
end
fprintf('hub %d\n',num);
points = {points_rec,[x_max,y_max],hub};
end

%% generate board
function shape = gen_board_shape(hub_sz)
r = rand();
if r > 0.5  % rectangle
    x1 = rand() * 1 + 0.5;
    y1 = rand() * 0.1 + 0.05;
    shape = {1,[x1,y1]};
elseif r > 0.8  % 2 lines
    x1 = rand() * 0.2 + 0.05;
    y1 = rand() * 0.1 + 0.05;
    x2 = rand() * 1 + 0.5;
    y2 = y1;
    shape = {2,[x1,y1,x2,y2]};
else    % 3 lines
    x1 = rand() * 0.2 + 0.05;
    y1 = rand() * 0.1 + 0.05;
    x2 = rand() * 1 + 0.5;
    y2 = y1;
    x3 = rand() * 0.2 + 0.05;
    y3 = (rand() > 0.5) * rand() * y2;
    shape = {3,[x1,y1,x2,y2,x3,y3]};
end
shape{2} = shape{2}* 10 * max(hub_sz(1),0.3);
end

function points = gen_board(num,hub_sz,hub)
while true
    y0 = rand() * hub_sz(2);
    x0 = 0;
    theta1 = 2*pi*rand(); % x axis
    body = max(size(hub));
    for i = 1:body
        if hub{i}{2}(2,2) > y0 && hub{i}{2}(1,2) <= y0 && hub{i}{1} == 1
             x0 = (hub{i}{2}(2,1) - hub{i}{2}(1,1)) * (y0 - hub{i}{2}(1,2)) / (hub{i}{2}(2,2) - hub{i}{2}(1,2)) + hub{i}{2}(1,1);
             break;
        end
        if hub{i}{2}(2,2) > y0 && hub{i}{2}(1,2) <= y0 && hub{i}{1} == 2
             x0 = hub{i}{2}(2,1);
             break;
        end
    end
    if x0 < 0.8 * hub_sz(1)
        continue;
    end
    y0 = hub_sz(2) - y0;
    board = gen_board_shape(hub_sz);
    t = 0;
    polar = 0;
    points_rec = zeros(num,3);
    if board{1} == 1
        polar = rand() * 0.2 + 0.1;
    else
        if rand() > 0.7
            polar = rand() * 0.2 + 0.1;
        end
    end
    if polar > 0
        p_num = int16(num * 0.02 * rand() + num * 0.03);
        while true
            x = polar * rand();
            y = 0.005 * rand() - 0.0025;
            z = 0.005 * rand() - 0.0025;
            p = [1,0,0;0,cos(theta1),sin(theta1);0,-sin(theta1),cos(theta1)]*[x,y,z]';
            x = (-1)^(rand()>0.5)*(x0 + p(1));
            y = y0 + p(2);
            z = p(3);
            t = t + 1;
            points_rec(t,1) = x;
            points_rec(t,2) = y;
            points_rec(t,3) = z;
            if t == p_num
                break
            end
        end
    end
    x_max = board{2}(board{1}*2 - 1);
    y_max = board{2}(2);
    while true
        x = x_max * rand();
        y = y_max * rand();
        if (board{1} == 2 || board{1} == 3) && x < board{2}(1)
            y_ = board{2}(1) / board{2}(2) * x;
            if y_ < y
                continue
            end
        end
        if board{1} == 3 && x > board{2}(3)
            y_ =  (x - board{2}(5)) /(board{2}(3) - board{2}(5)) * (board{2}(4) - board{2}(6)) + board{2}(6);
            if y_ < y
                continue
            end
        end
        x = x + polar;
        y = (-1)^(rand()>0.5)*y;
        z = 0.005 * rand() - 0.0025;
        p = [1,0,0;0,cos(theta1),sin(theta1);0,-sin(theta1),cos(theta1)]*[x,y,z]';
        x = (-1)^(rand()>0.5)*(x0 + p(1));
        y = y0 + p(2);
        z = p(3);
        t = t + 1;
        points_rec(t,1) = x;
        points_rec(t,2) = y;
        points_rec(t,3) = z;
        if t == num
            break
        end
    end
    x_max = x_max + x0 + polar;
    fprintf('board %d\n',num);
    points = {points_rec,[x_max,y_max],board};
    break;
end
end

%% generate nozzle
function shape = gen_nozzle_shape()
    x1 = 0.025 * rand() + 0.025;
    y1 = 0;
    x2 = 0.02 * rand() + x1;
    y2 = (rand() * 2 + 1) * x2;
    shape = [x1,y1,x2,y2] * 2;
end

function points = gen_nozzle(num)
    s = gen_nozzle_shape();
    points_rec = zeros(num,3);
    t=0;
    while true
        x = rand() * s(3);
        y = rand() * s(4);
        x_ = y / s(4) * (s(3) - s(2));
        if x_ < x
            continue
        end
        theta = 2*pi*rand();
        z = sin(theta)*x;
        x = cos(theta)*x;
        y = -y;
        t = t + 1;
        points_rec(t,1) = x;
        points_rec(t,2) = y;
        points_rec(t,3) = z;
        if t == num
            break
        end
    end
fprintf('nozzle %d\n',num);
points = {points_rec,[s(3),s(4)],s};
end

%% generate satellite
function sat = gen_sat(num)
num_b = int16((0.9 + 0.2 * rand())*0.2*num);
num_n = int16((0.9 + 0.2 * rand())*0.05*num);
num_h = num - num_b - num_n;
hub = gen_hub(num_h,5);
nozzle = gen_nozzle(num_n);
board = gen_board(num_b,hub{2},hub{3});
y_m = (hub{2}(2) - nozzle{2}(2)) / 2;
hub{1}(:,2) = hub{1}(:,2) - y_m;
nozzle{1}(:,2) = nozzle{1}(:,2) - y_m;
board{1}(:,2) = board{1}(:,2) - y_m;
h = hub{1};
n = nozzle{1};
b = board{1};
x = board{2}(1) * 2;
y = hub{2}(2) + nozzle{2}(2);
shrink = 1 / max(x,y) * (0.8 + 0.2 * rand());
h = h * shrink;
n = n * shrink;
b = b * shrink;
fprintf('satellite %d',num);
sat = {h,n,b};
end