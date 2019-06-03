

cvx_begin

n=10;
k=5;
%we will have kxn matrix  
%sth like 1 2 3 4 5 6 7 8 9 10
%         2 2 3 4 5 6 7 8 9 10
%         3 2 3 4 5 6 7 8 9 10
%         4 2 3 4 5 6 7 8 9 10
%         5 2 3 4 5 6 7 8 9 10
    
S=9; %S nonzeroelements out of n
x = [zeros(1,n-S), ones(1,S)];  
x = x(randperm(n1));
%x  sth like=>     1     0     0     0     0     0     0     0     1     1

freq=S/n;

nvec = 0:1:n-1; % row vector for n
kvec = 0:1:k-1; % row vecor for k
F = kvec'*nvec; % creates a k by n matrix
F

for r = 1:k;
   for c=1:n;
      WN =(1/(sqrt(N))) * exp(-1i*2*pi*c*freq/N);  
      F(r,c) = WN;
   end;
end;

F


y = (F*x');




cvx_end


