A=[1 2 0 1; 0 0 3 1; 0 3 1 1; 2 1 2 5; 1 0 3 2];
cmax=[100; 100; 100; 100; 100];
pbase=[3;2;7;6];
pdiscount=[2;1;4;2];
q=[4;10;5;10];
cvx_begin
    variable x(4)
    revenue=min(pbase.*x,pbase.*q+pdiscount.*(x-q))
    totalrevenue=sum(revenue)
    maximize(totalrevenue)
    subject to
        A*x<=cmax    
        x>=0
cvx_end
x
averagePrice=revenue./x
revenue
totalrevenue


