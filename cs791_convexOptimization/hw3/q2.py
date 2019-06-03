import sys

sys.path.append('/usr/local/lib/python2.7/site-packages')

import cvxpy 
import numpy

A=np.matrix('1 2 0 1;\ 0 0 3 1;\ 0 3 1 1;\ 2 1 2 5;\ 1 0 3 2')

cmax=np.matrix('100; 100; 100; 100; 100')

p=np.matrix('3; 2; 7; 6')

pdisc=np.matrix('2; 1; 4; 2')

q=np.matrix('4; 10; 5; 10')

x=cvx.Variable(4)

t1=cvx.mul_elemwise(p, x)
t2=cvx.mul_elemwise(p, q) + cvx.mul_elemwise(pdisc, x-q)
obj=cvx.Maximize(cvx.sum_entries(cvx.min_elemwise(t1, t2)))

cons=[x >= 0, A*x <= cmax]

prob = cvx.Problem(obj, cons)
prob.solve()

r=cvx.min_elemwise(t1, t2).value
totr=sum(r)

avgPrice=r/x.value
print x.value
print r
print totr
print avgPrice  
