function x = smallexample()
% These specify the quadratic objective function.
%rr = randi([1 10],1,5)

%H = diag(rr);

H = diag([ 2 2 4 2 1 ]);
%q=randi([1 10],1,5);
%q=q';
q = [ -5 -5 -21 7 1 ]';

% These specify the quadratic inequality constraints.
%temp=randi([1 10],1,5);
%P{1} = diag(temp);
%temp=randi([1 10],1,5);
%P{2} = diag(temp);
%temp=randi([1 10],1,5);

%P{3} = diag(temp);

P{1} = diag([ 4 2 2 0 1]);
P{2} = diag([ 2 2 2 2 1]);
P{3} = diag([ 2 4 2 4 1]);

%temp=randi([-2 2],1,5);
%temp
%r{1} = temp';

%temp=randi([-2 2],1,5);

%r{2} = temp';

%temp=randi([-2 2],1,5);

%r{3} = temp';

r{1} = [  2 -1  0 -1 1]';
r{2} = [  1 -1  1 -1 1]';
r{3} = [ -1  0  0 -1 1]';

b = [ 5 8 10 ]';

% Set the starting point.
x0 = [ 0 0 0 0 1]';

%temp=randi([0 1],1,5);

%x0 = temp';


%fprintf('Running exact interior point method to obtain solution.\n');
data = { H q P r b };   % All the information about the quadratic program.
z    = zeros(size(b));  % A dummy variable; does nothing.

x = ipsolver(x0,H, q, P, r, b,@(x)gradient(x,H,q),@(x)constraints(x,H, q, P, r, b),@(x,z)jacobian(x,z,H, q, P, r, b),'bfgs',1e-6,100,true);

%disp(x);


end

function f=objective(x,H,q)
    f = x'*H*x/2 + q'*x;
end

function f=gradient(x,H,q)
    f =  H*x + q;  
end

function f=constraints(x,H, q, P, r, b)
     m=length(b);
     f = zeros(m,1);
    for i = 1:m
      f(i) = x'*P{i}*x/2 + r{i}'*x - b(i);
    end
end

function  [J, W]=jacobian(x,z,H, q, P, r, b)

    n = length(x);
    m = length(b);
    J = zeros(m,n);
    W = zeros(n);
    for i = 1:m
      J(i,:) = (P{i}*x + r{i})';
      W      = W + z(i)*P{i};
    end
    
end



function x = ipsolver (x,H, q, P, r, b, gradient, constraints, jacobian, descentdir, tolerance, maxiter, verbose)

  % Some algorithm parameters.
  eps       = 1e-8;   % A number close to zero.
  sigmamax  = 0.5;    % The maximum centering parameter.
  etamax    = 0.25;   % The maximum forcing number.
  mumin     = 1e-9;   % Minimum barrier parameter.
  alphamax  = 0.995;  % Maximum step size.
  alphamin  = 1e-6;   % Minimum step size.
  beta      = 0.75;   % Granularity of backtracking search.
  tau       = 0.01;   % Amount of actual decrease we will accept in 
                      % line search.

  c  = constraints(x);
  n  = length(x);
  m  = length(c);
  nv = n + m;
  z  = ones(m,1);
  B  = eye(n);
  
  if verbose
    fprintf('  i f(x)       lg(mu) sigma   ||rx||  ||rc||  alpha   #ls\n');
  end
  

  alpha = 0;
  ls    = 0;
  for iter = 1:maxiter
      
    f     = objective(x,H,q);
    c     = constraints(x);
    [J W] = jacobian(x,z);
    if strcmp(descentdir,'newton')
      [g B] = gradient(x);
    else
      g = gradient(x);
    end
    
   
    rx = g + J'*z;  % Dual residual.
    rc = c.*z;      % Complementarity.
    r0 = [rx; rc]; 
    
    eta        = min(etamax,norm(r0)/nv);
    sigma      = min(sigmamax,sqrt(norm(r0)/nv));
    dualitygap = -c'*z;
    mu         = max(mumin,sigma*dualitygap/m);
    
    if verbose
      fprintf('%3d %+0.3e  %+5.2f %0.1e %0.1e %0.1e %0.1e %3d\n',...
	      iter,f,log10(mu),sigma,norm(rx),norm(rc),alpha,ls);
    end
 
    if norm(r0)/nv < tolerance
      break
    end
   
    if strcmp(descentdir,'bfgs') & iter > 1
      B = bfgsupdate(B,alpha*px,g-gprev);
    end

    S  = diag(sparse(z./(c-eps)));
    gb = g - mu*J'*(1./(c-eps));
    px = (B + W - J'*S*J) \ (-gb);
    pz = -(z + mu./(c-eps) + S*J*px);
    

    alpha = alphamax;
    is    = find(z + pz < 0);
    if length(is)
      alpha = alphamax * min(1,min(z(is) ./ -pz(is)));
    end
    
    psi  = merit(x,z,f,c,mu,eps);
    dpsi = gradmerit(x,z,px,pz,g,c,J,mu,eps);
    ls   = 0;
    while true

      ls     = ls + 1;
      xnew   = x + alpha * px;
      znew   = z + alpha * pz;
      f      = objective(xnew,H,q);
      c      = constraints(xnew);
      psinew = merit(xnew,znew,f,c,mu,eps);

      if sum(c > 0) == 0 & psinew < psi + tau*eta*alpha*dpsi
    	x     = xnew;
        z     = znew;
        gprev = g;
        break
      end
      
      % The candidate point does not meet our criteria, so decrease the step
      % size for 0 < beta < 1.
      alpha = alpha * beta;
      if alpha < alphamin
	error('Step size too small');
      end
    end
  end
end  

function psi = merit (x, z, f, c, mu, eps)
  psi = f - c'*z - mu*sum(log(c.^2.*z+eps));

  
end

function dpsi = gradmerit (x, z, px, pz, g, c, J, mu, eps)
  dpsi = px'*(g - J'*z - 2*mu*J'*(1./(c-eps))) - pz'*(c + mu./(z+eps));

end

function B = bfgsupdate (B, s, y)  
  if y'*s < 0
    error('dot(y,s) > 0 is not satisfied');
  end
  x = B*s;
  B = B - x*x'/(x'*s) + y*y'/(y'*s);
  
end









//////

x=[1.3];
for iter = 1:100
    if mod(iter,15) == 1
        x(iter)=0.3;
    elseif mod(iter, 16) == 1
        x(iter)=0.2;
    elseif mod(iter, 17) == 1
        x(iter)=-0.1;
    elseif mod(iter, 18) == 1
        x(iter)=1.1;
    elseif mod(iter, 14) == 1
        x(iter)=0.7;
    elseif mod(iter, 12) == 1
        x(iter)=-0.2;
    elseif mod(iter, 11) == 1
        x(iter)=0.8;
    elseif mod(iter, 10) == 1
        x(iter)=-0.7;
    elseif mod(iter, 9) == 1
        x(iter)=0.5;
    elseif mod(iter, 8) == 1
        x(iter)=0.1;
    elseif mod(iter, 7) == 1
        x(iter)=0.0;
    elseif mod(iter, 6) == 1
        x(iter)=-0.4;
    elseif mod(iter, 5) == 1
        x(iter)=0.9; 
    elseif mod(iter, 4) == 1
        x(iter)=1; 
    else
        x(iter)=-0.5;
    end
    
    end


