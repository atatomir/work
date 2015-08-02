program imprimanta;
var n:qword;
    x:longint;
    k,i,min,max:byte;
    c:array[1..15] of byte;
    a:array[0..9] of byte;
    f,g:text;
begin
  assign(f,'imprimanta.in'); reset(f);
  assign(g,'imprimanta.out'); rewrite(g);
  a[0]:=12;
  a[1]:=5;
  a[2]:=11;
  a[3]:=11;
  a[4]:=9;
  a[5]:=11;
  a[6]:=12;
  a[7]:=7;
  a[8]:=13;
  a[9]:=12;
  readln(f,n,x);
  k:=0;
  while n<> 0 do
    begin
      k:=k+1;
      c[k]:=n mod 10;
      n:=n div 10;
    end;
  min:=a[c[1]];
  for i:=2 to k do
    if a[c[i]]<min then min:=a[c[i]];
  max:=0;
  for i:=1 to k do if a[c[i]]=min then if c[i]>max then max:=c[i];
  writeln(g,max);
  if x mod 5=0 then for i:=1 to x div 5 do write(g,1);
  close(f);
  close(g);
end.
