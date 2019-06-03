MAXITERS = 100; %maximum iteration
ALPHA = 0.01;
BETA = 0.5;
RESTOL = 1e-7;  %tolerance
p=30; %30
n=100; %100
x1=rand(1,n,1);
x1=x1';
x2=randi(1,n,1);


A=randi(100,p,n); %p by n matrix

while (rank(A,1e-16) ~= p)
A=randi(100,p,n);
end
 
res1=Computation(A,x1,MAXITERS,ALPHA,BETA,RESTOL,p,n);
res2=Computation(A,x2,MAXITERS,ALPHA,BETA,RESTOL,p,n);

data{1}=res1;
data{2}=res2;
hold on
set(gca, 'YScale', 'log');
xlabel('k'); % x-axis label
ylabel('norm of residual'); % y-axis label
cellfun(@(x) plot(x), data);

[hleg1, hobj1]=legend('x0=random','x0=1');
textobj = findobj(hobj1, 'type', 'text');
set(textobj, 'Interpreter', 'latex', 'fontsize', 10);
function res = Computation(A,x,MAXITERS,ALPHA,BETA,RESTOL,p,n)
    v=zeros(p,1);
    b=A*x; %
    res=[];
    for i=1:MAXITERS
       gradient=1+log(x);
       r = [gradient+A'*v;  A*x-b];  
       res = [res, norm(r)]; %add elements to end
       sol = -[diag(1./x) A';  A zeros(p,p)] \ r;
       Dx = sol(1:n); 
       Dnu = sol(n+[1:p]);
       if (norm(r) < RESTOL)
           break; 
       end;
       t=1;
       while (min(x+t*Dx) <= 0)
           t = BETA*t;  
       end;
       while norm([1+log(x+t*Dx)+A'*(v+Dnu);  A*(x+Dx)-b]) > (1-ALPHA*t)*norm(r)
           t=BETA*t; 
       end; 
       x=x+t*Dx;
       v=v+t*Dnu;
    end;
end
    
