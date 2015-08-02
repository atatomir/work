var f,g:text;
    s,k,n,l,kb,c,cat,m,nrcifre,i,j,z,ce:longint;
begin
assign(f,'galbeni.in');
reset(f);
assign(g,'galbeni.out');
rewrite(g);
read(f,s,k,n);
l:=s;
kb:=1;
for i:=1 to k do
    kb:=kb*10;
for i:=1 to n-1 do
    begin
    l:=s;
    while l>0 do
        begin
        c:=l mod 10;
        l:=l div 10;
        if c<>0 then
           s:=s*c;
        end;
    s:=s*8;
    cat:=s div 9;
    if (cat div kb=cat)or(cat>kb) then
        s:=cat mod kb
        else
        begin
         m:=cat;
         while m>0 do
               begin
               ce:=m mod 10;
               m:=m div 10;
               nrcifre:=nrcifre+1;
               end;
        z:=k-nrcifre;
        s:=cat;
        for j:=1 to z do
            s:=s*10+9;
        end;
    end;
writeln(g,s);
close(f);
close(g);
end.
