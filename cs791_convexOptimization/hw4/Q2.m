Q = [1 -1/2; -1/2 2];
    f = [-1 0]';
    
    A = [1 2; 1 -4; 5 76];
    u = [-2 -3 1]';
    
    
    cvx_begin
        variable x(2)
        dual variable l
        minimize(quad_form(x,Q)+f'*x)
        subject to
            l: A*x <= u
    cvx_end
    
    p_op = cvx_optval