data = fopen("LOG00000.TXT",'r');
formatSpec = "%d";
sizeData = [1 Inf];
Data = fscanf(data, formatSpec, sizeData);

plot(linspace(1,1500,1500),Data);
grid;