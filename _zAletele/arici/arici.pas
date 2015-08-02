var n,m:word;
    a:array[1..10000,1..10000]of byte;
    max:longword;


procedure citire;
var f:text;
    i,j:word;
begin
  assign(f,'arici.in');
  reset(f);
  readln(f,n,m);
  for i := 1 to m do
    for j := 1 to n  do read(f,a[i,j]);
end;

procedure cauta(x,y:word;mere:longword);
begin
  if x+1 <= n then cauta(x+1,y,mere+a[x,y]);
  if y+1 <= m then cauta(x,y+1,mere+a[x,y]);
  if (x=n)and(y=m) then
  begin
    mere := mere + a[x,y];
    if mere > max then max := mere;
  end;
end;


begin
  max:=0;
  citire;
  cauta(1,1,0);
  writeln(max);
  readln(max);
end.