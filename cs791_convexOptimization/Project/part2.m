
cvx_begin
   variables blen(1) interval(1) length1(1) length2(1) initializationTime(1) time(1) overallTime(1)
   
   minimize(quad_over_lin(time,blen))
   subject to
        
        time == (2*interval + initializationTime)*1000 
        
        1 <= blen
        blen <= 1000
        initializationTime == 240
        5*blen-interval<=0
        length2 == 1000    
cvx_end
blen
interval




 




