function optimal = Q2(varargin) %Newton's Method for Unconstrained Problems

x = randi(20,2,1); 
maximumNumberOfIteration=10;     %maximum number of iteration
tol = 1e-6;                     % termination tolerance
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
ls=[];

%calling Newton's Method
[xoptimal,ls]=newton_method(x,maximumNumberOfIteration,tol); 
optimal_Value=objectiveF(xoptimal(1),xoptimal(2));

xoptimal
optimal_Value

data{1}=ls;
hold on
xlabel('k'); % x-axis label
ylabel('f(x^(^k^)) - p* '); % y-axis label

set(gca, 'YScale', 'log');
cellfun(@(x) plot(x), data);
legend('Back Tracking');


function [xoptimalP,ls] = newton_method(x_initial,maximumNumberOfIteration,tol)

x=x_initial; ls=[];
% initialize gradient norm, iteration counter
numberOfiteration = 0; 
ls(end+1) = objectiveF(x(1),x(2));
while ( numberOfiteration <= maximumNumberOfIteration)
   
    gradient=gradienter(x(1),x(2));             %calculate gradient
    hessian=hessianer(x(1),x(2));               %calculate hessian
    
    newton_step=-inv(hessian)*gradient;     %calculate newton_step
    
    newton_decrement_sq=gradient'*inv(hessian)*gradient;
    
    if newton_decrement_sq/2 <= tol
        break
    end
    
    stepSize=BackTrackLinesearch(x,newton_step,0.7,0.1);  %B, Alpha
    x =  x + (stepSize * newton_step);     
     
    ls(end+1) = objectiveF(x(1),x(2)); 
    numberOfiteration = numberOfiteration + 1;   %update stopping criterion
end

pStar = objectiveF(x(1),x(2)); 
for k=1:length(ls)
    curw=ls(k);
    ls(k)=curw-pStar;
end
xoptimalP=x;


function t = BackTrackLinesearch(x,descentDirection,B,alpha)
t = 1;                          
fright = objectiveF(x(1),x(2));     
gradient =  gradienter(x(1),x(2));  
xx = x;
x = xx + t*descentDirection;
fleft = objectiveF(x(1),x(2));   

while fleft > fright + alpha*t*(gradient'*descentDirection)    
    t = t*B;
    x = xx + t*descentDirection;
    fleft = objectiveF(x(1),x(2));      
end
function f = objectiveF(x1,x2)
f=exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)+exp(-x1-0.1);

function g = gradienter(x1,x2)
r00=exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)-exp(-x1-0.1);
r10=3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1);
g=[r00;r10];
  
function h = hessianer(x1,x2)
r00=exp(x1+3*x2-0.1)+exp(x1-3*x2-0.1)+exp(-x1-0.1);
r01=3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1);
r10=3*exp(x1+3*x2-0.1)-3*exp(x1-3*x2-0.1);
r11=9*exp(x1+3*x2-0.1)+9*exp(x1-3*x2-0.1);

h = [r00 r01;r10 r11];



