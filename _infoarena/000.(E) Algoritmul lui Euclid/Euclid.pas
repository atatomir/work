var x,y,t:int64;
    ta:longint;
    i:longint;
    bufin,bufout:array[1..65000]of byte;


begin


assign(input,'euclid2.in');reset(input);
assign(output,'euclid2.out');
rewrite(output);

settextbuf(input,bufin);
settextbuf(output,bufout);

readln(t);

for i := 1 to t do
begin
readln(x,y);

//if (x=0)or (y=0) then writeln(fo,'0')
//else
begin

{if x <> y then
repeat
  if x<y then
    y := y -x
  else
    x := x - y;
until x=y ;
writeln(fo,x);}
  x :=x mod y;

  while x <> 0  do
  begin

    ta := y mod x;
    y := x;
    x := ta;
  end;

  writeln(y);
end;
end;



close(output);close(input);


end.
