program schi;
var n,k,j,i,p:longint;
    f,g:Text;
    a,b:array[1..1000]of longint;
begin
  assign(f,'schi.in'); reset(f);
  assign(g,'schi.out'); rewrite(g);
  readln(f,n);
  for i:=1 to n do
  readln(f,a[i]);
  for j:=1 to k do
  readln(f,b[j]);
  if (a[i]=b[j])and(a[i]>a[i+1]) then
                                  p:=p+1
                                else
                                  write(g,0);
   write(g,p);
   close(f); close(g);
end.
