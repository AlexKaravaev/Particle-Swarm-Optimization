[x]=read("~/Innopolis/Introduction_To_AI/week6/res1.txt",2000,1)
x = [x]
[y]=read("~/Innopolis/Introduction_To_AI/week6/res2.txt",2000,1)
y = [y]
for n=0:5:2000
    for k=1:5
        if k==1 then
            plot(x(n+k),y(n+k),".r");
        elseif k==2 then
            plot(x(n+k),y(n+k),".g");
        elseif k==3 then
            plot(x(n+k),y(n+k),".o");
        elseif k==4 then
            plot(x(n+k),y(n+k),".b");
        elseif k==5 then
            plot(x(n+k),y(n+k),".y");
        end,
        
    end
    sleep(0.01)
    
end
