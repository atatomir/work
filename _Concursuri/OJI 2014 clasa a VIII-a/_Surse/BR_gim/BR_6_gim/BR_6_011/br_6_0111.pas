program imprimanta;
var a,r,c:array[1..11] of integer;
    fin,fout:text;
    n,k,i,j,min,max,l:longint;
begin
assign(fin,'imprimanta.in');
assign(fout,'imprimanta.out');
reset(fin);
rewrite(fout);
readln(fin,n,k);
a[1]:=12;
a[2]:=5;
a[3]:=11;
a[4]:=11;
a[5]:=9;
a[6]:=11;
a[7]:=12;
a[8]:=7;
a[9]:=13;
a[10]:=12;
i:=0;
while n<>0 do
 begin
 i:=i+1;
 r[i]:=n mod 10;
 n:=n div 10;
 end;
 min:=13;
l:=1;
for j:=1 to i do
 if min>=a[r[j]+1] then
                  begin
                  if min=a[r[j]+1] then
                                   l:=l+1;
                  min:=a[r[j]+1];
                  c[l]:=r[j];
                  end;
max:=0;
for j:=1 to l do
 if max<c[j] then
             max:=c[j];
writeln(fout,max);
close(fin);
close(fout);
end.









