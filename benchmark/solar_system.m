% Solar system simulation for benchmarking

% Simulation parameters
nSteps = 250;
G = 1e-5;
nParticles = 9;
dTime = 0.0001;

% Physical property arrays
pos = NaN(nParticles, 3);
vel = NaN(nParticles, 3);
acc = NaN(nParticles, 3);
radii = NaN([nParticles 1]);
masses = NaN([nParticles 1]);

% Center particle attributes
radii(1) = 10;
masses(1) = 1e15;
pos(1,:) = [0 0 0];
vel(1,:) = [0 0 0];

% Other particle attributes
for i = 2:nParticles
    radii(i) = 1;
    masses(i) = 1;
    pos(i,:) = [ (5*i+10) 0 0 ];
    GM_r = G*masses(1) / norm(pos(i,1) - pos(1,1));
    vel(i,:) = [ 0 sqrt(GM_r) 0 ];
end

% Create position and velocity arrays
allPos = NaN(nParticles, 3, nSteps+1);
allVel = NaN(nParticles, 3, nSteps+1);

% Simulation time step
for t = 1:nSteps
    allPos(:,:,t) = pos(:,:);
    allVel(:,:,t) = vel(:,:);
    for k = 1:nParticles
        acc(k,:) = gravity(G, masses, pos, k);
    end
    vel = vel + dTime * acc;
    pos = pos + dTime * vel;
end
allPos(:,:,end) = pos(:,:);
allVel(:,:,end) = vel(:,:);

pos2D = reshape(permute(allPos, [2 1 3]), [nParticles*3 nSteps+1]);
%vel2D = reshape(permute(allVel, [2 1 3]), [nParticles*3 nSteps]);
%posVel2D = [pos2D; vel2D];

% Load in the c++ simulation files
cSimData = NaN(nParticles, 3, nSteps+1);
for n = 0:nSteps
    data = csvread(['./c_sim/exmd.csv.' num2str(0)], 1, 0);
    cSimData(:,:,n+1) = data(:,1:3);
end
cSimData2D = reshape(permute(cSimData, [2 1 3]), [nParticles*3 nSteps+1]);

Diff = (pos2D-cSimData2D);
%Eliminate zeros in Diff
Diff(3:3:27,:) = [];
Diff(1:2,:) = [];
%Eliminate zeros 
pos2D(3:3:27,:) = [];
pos2D(1:2,:) = [];

fracDiff = Diff ./ pos2D;
imagesc(fracDiff); colorbar; caxis([-2 2]);
