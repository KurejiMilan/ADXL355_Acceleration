clc;
clear;

freq = [0.1, 0.2, 0.3, 0.4 , 0.5, 0.6, 0.7, 0.8, 0.9, 1 ,1.5, 2, 2.5 ,3, 3.5, 4, 4.5, 5, 6, 7, 8 , 9, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100];
Vpp = [7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.1, 7.0,  6.9, 6.9, 6.8, 6.8, 6.7, 6.5, 6.3, 6.0, 5.55, 5.15, 4.82, 3.14, 2.05, 1.40, 1.01, 0.76, 0.59, 0.48, 0.38, 0.273, 0.205, 0.159, 0.127, 0.105];
Amp = zeros(size(Vpp));
Vpeak = max(Vpp);
is_equal = false;

%check for correct length of samples
if isequal(size(freq), size(Vpp))
    disp('equal number of samples in freq and amplitude');
    is_equal = true;
else
    disp('not equal number of samples in freq and amplitude.');
end

if is_equal
    % just nominal voltage
    semilogx(freq, Vpp);
    yline(Vpeak/sqrt(2), "--");
    grid on;
    title("frequency response");
    xlabel("frequency in logrithmic scale");
    ylabel("Vpp");
    figure;
    % this section handles conversion to dB
    for i = 1:length(Vpp)
        Amp(i) = 20*log10(Vpp(i));
    end
    semilogx(freq, Amp);
    yline((20*log10(Vpeak))-3.01,"--");
    title("frequency response");
    xlabel("frequency in logrithmic scale");
    ylabel("dB");
    grid on;
end
