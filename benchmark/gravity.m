function acceleration = gravity(G, masses, positions, ind)
%GRAVITY Calculate the gravitational a on a particle
%   
%   Usage:
%       force = gravity(masses, positions, index);
%
%   Input:
%       G: the gravitational constant
%       masses: nParticles-dim column vector of masses 
%       positions: nParticles-by-3 matrix of positions
%       ind: particle force should be calculated for
%
%   Output:
%       force: the force on the particle
%
% Hugh Wilson - hswilson@princeton.edu

% Separation vectors - pointing towards the particle
nParticles = size(positions, 1);
sep = repmat(positions(ind,:), [ nParticles 1 ]) - positions;

% Force due to each of the other particles
sep_norm = sqrt(sum(sep.^2 , 2));
accelerations = G * repmat(masses, [ 1 3 ]) .* sep ./ ...
    (repmat(sep_norm, [1 3]).^3);
accelerations(ind,:) = [];
acceleration = -sum(accelerations, 1);
end

