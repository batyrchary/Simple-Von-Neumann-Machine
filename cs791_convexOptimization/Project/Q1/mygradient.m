function optimal = mygradient(varargin)

Q1= randi(2*52,10,10);

Q=Q1*Q1';

d=eig(Q);
emax=max(d);
emin=min(d);
condition_number=emax/emin;
condition_number

q=randi(2*52,10,1);

%q=[34;6;10;29;50];

x_starting_point=randi(2*52,10,1);
%x_starting_point=[76;9;9;14;12];

%maximum number of iteration
maximumNumberOfIteration=200000;    
%tol = 1e-6;                     % termination tolerance
tol=1;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%f = @(x) 0.5*x'*Q*x + q'*x      %objective function

%starting point, will also be used as current optimal point
x_sP =  x_starting_point;         
ls1=[];
ls2=[];

%calling gradient descent
%0=gradient descent
[optimalWithBackTrackLinesearch,ls1]=gradient_method(x_sP, 1, maximumNumberOfIteration,Q,q,tol,0); 
[optimalWithExactLinesearch,ls2]=gradient_method(x_sP, 0, maximumNumberOfIteration,Q,q,tol,0);    


%optimalWithBackTrackLinesearch
%optimalWith
opB=objectiveF(optimalWithBackTrackLinesearch, Q, q);
opE=objectiveF(optimalWithExactLinesearch, Q, q);
opB
opE


data{1}=ls1;
data{2}=ls2;

hold on
xlabel('k'); % x-axis label
ylabel('f(x^(^k^)) - p* '); % y-axis label
set(gca, 'YScale', 'log');
cellfun(@(x) plot(x), data);
[hleg1, hobj1]=legend('BackTrack','Exact');
textobj = findobj(hobj1, 'type', 'text');
set(textobj, 'Interpreter', 'latex', 'fontsize', 10);

%calling steepest descent
%1=steepest descent
[optimalWithBackTrackLinesearch,ls1]=gradient_method(x_sP, 1, maximumNumberOfIteration,Q,q,tol,1); 
[optimalWithExactLinesearch,ls2]=gradient_method(x_sP, 0, maximumNumberOfIteration,Q,q,tol,1);     

opB=objectiveF(optimalWithBackTrackLinesearch, Q, q);
opE=objectiveF(optimalWithExactLinesearch, Q, q);
opB
opE

function [optimal_value,ls] = gradient_method(x_initial, which_linesearch, maximumNumberOfIteration,Q,q,tol,which_method)
x_sP=x_initial;
ls=[];
P = diag(diag(Q));
% initialize gradient norm, iteration counter
gnorm = inf;  numberOfiteration = 0; 
ls(end+1) = objectiveF(x_sP,Q,q);
while and(gnorm>=tol, numberOfiteration <= maximumNumberOfIteration)
    gradient=gradienter(x_sP,Q,q);             %calculate gradient
    if which_method == 0 %gradient
        descentDirection=-gradient;            %determine descent direction
    end
    if which_method == 1 %steepest
        descentDirection=-inv(P)*gradient;
    end
    
    %stepSize=0.1;                             %determine stepsize
    if which_linesearch == 1
        stepSize=BackTrackLinesearch(Q,q,descentDirection,x_sP,0.5,0.1); %B alpha
    end
    if which_linesearch == 0
        stepSize=ExactLinesearch(Q,q,descentDirection,x_sP);
    end
    x_sP =  x_sP + (stepSize * descentDirection);  %update Current optimal point
    
    ls(end+1) = objectiveF(x_sP,Q,q);
    %update stopping criterion
    gnorm = norm(gradient);
    numberOfiteration = numberOfiteration + 1;
end
numberOfiteration
pStar = objectiveF(x_sP,Q,q);
for k=1:length(ls)
    curw=ls(k);
    ls(k)=curw-pStar;
end


optimal_value=x_sP;

function t = ExactLinesearch(Q,q,descentDirection,x)
t=1;
gradient =  gradienter(x,Q,q);  %vector direction
t=(gradient'*gradient)/(gradient'*Q*gradient);


function t = BackTrackLinesearch(Q,q,descentDirection,x,B,alpha)
t = 1;                          %stepsize
fright = objectiveF(x,Q,q);     %value
gradient =  gradienter(x,Q,q);  %vector direction
xx = x;
x = xx + t*descentDirection;    %vector -> argument for left side of while
fleft = objectiveF(x,Q,q);      %value  -> left side of while

while fleft > fright + alpha*t*(gradient'*descentDirection)
    t = t*B;
    x = xx + t*descentDirection;    %argument for left side of while
    fleft = objectiveF(x,Q,q);      %left side of while
end

function f = objectiveF(x,Q,q) %objective function
f=0.5*x'*Q*x + q'*x;            %returns value

% define the gradient of the objective
%returns vector (direction)
function g = gradienter(x,Q,q)
g = Q*x+q;


