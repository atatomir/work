program munte;
var x:array[1..100] of longint;
    fin,fout:text;
    n,c,i,k,m,l:longint;
    b:boolean;
begin
assign(fin,'munte.in');
assign(fout,'munte.out');
reset(fin);
rewrite(fout);
readln(fin,n);
for i:=1 to n do
 read(fin,x[i]);
if n mod 2=1 then
              n:=n+1;
c:=n div 2;
if c>=3 then
        begin
        writeln(fout,2);
        k:=1;
        repeat
         b:=false;
         for i:=c to n do
          x[i]:=x[i+1];
         n:=n-1;
         m:=n;
         if n mod 2=1 then
                      m:=m+1;
         c:=m div 2;
         if c>=3 then
                b:=true;
         k:=k+1;
        until b=false ;
        l:=(k-1)*2;
        writeln(fout,l);
        writeln(fout,k-1);
        end
        else
        writeln(fout,0);


close(fin);
close(fout);
end.

