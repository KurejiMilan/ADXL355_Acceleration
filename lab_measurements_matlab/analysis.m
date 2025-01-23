clear;
data = fopen("LOG00000.TXT",'r');
formatSpec = "%d";
sizeData = [1 Inf];
Data = fscanf(data, formatSpec, sizeData);

plot(linspace(1,1500,1500),Data);
legend("measured data from experiment");
grid;
%%
%chop of bad section;
adc_reading = Data(250:end);
x_axis = linspace(1, length(adc_reading),length(adc_reading));
figure;
plot(x_axis, adc_reading); 
xline(247,"r");
xline(297,"r");

xline(317);
xline(347);

xline(692,"r");
xline(729,"r");

xline(743);
xline(799);

xline(1142,"r");
xline(1173,"r");
%%
% get average value for 0 g and 1 g
g = 9.8;
v0g = adc_reading(247:297);
v1g = adc_reading(317:347);

avgV0g = sum(v0g)/length(v0g);
avgV1g = sum(v1g)/length(v1g);

k1 = g/(avgV1g-avgV0g);
k0 = -k1*avgV0g; 
%%
%accelaration
accel = k1.*adc_reading+k0;
%%accel = accel-g;
figure;
plot(x_axis, accel);
grid;
legend("acceleration");
%%
%summation
sel_accel = accel(101:177);
%sel_accel = accel(355:431); 3.6085
%sel_accel = accel(554:633); -3.6267
%sel_accel = accel(806:874); 3.6085
%sel_accel = accel(1014:1085);

sel_accel = sel_accel-g;
figure;
accel_x = linspace(1, length(sel_accel),length(sel_accel));
plot(accel_x, sel_accel);
grid;
legend("acceleration");
velsum = 0;
vel_profile = zeros(1,length(sel_accel));
for i=1:length(sel_accel)
    velsum = (sel_accel(i)*0.1)+velsum;
    vel_profile(i) = velsum;
end
compen = zeros(1,length(sel_accel));
slope = (vel_profile(end)-vel_profile(1))/length(sel_accel);

for i=1:length(sel_accel)
    compen(i) = slope*i+vel_profile(1);
end
figure;
plot(accel_x, vel_profile);
hold;
plot(accel_x, compen);

%compensating
for i=1:length(sel_accel)
    vel_profile(i) = vel_profile(i)-compen(i);
end
%print after compensation
plot(accel_x, vel_profile);
grid;
legend("velocity", "velocity drift slope", "compensated velocity");
distance = 0;
distance_profile = zeros(1,length(sel_accel));
for i=1:length(sel_accel)
    distance = (vel_profile(i)*0.1)+distance;
    distance_profile(i) = distance;
end

figure;
plot(accel_x, distance_profile);
legend("travelled distance");
grid;
%velsum