
alpha=2;
beta=3;

fileID=fopen('/Users/batyrchary/Desktop/my_text.txt','w');
for t = 0:100:1000
    result=(alpha/beta)*exp(-alpha*t);
    fprintf(fileID,'t=%6.0f, result=%6.0f\n',t,result);
    t
    result
end

fclose(fileID)