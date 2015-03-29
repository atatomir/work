var n,m,i,j,cont:longint;
    a:array[0..505,0..505]of longint;
    bufout:array[1..65000]of byte;

function getmin(x:longint):longint;
begin
  getmin := 1;
  while 2*getmin <= x do getmin := getmin*2;
end;

procedure Divide(x1,y1,x2,y2:longint);
var i,j,min,d1,d2,c1,c2,l,s:longint;
begin
  if (x1 > x2)or(y1 > y2) then exit;

  d1 := x2-x1+1; d2 := y2-y1+1;
  min := d1; if min > d2 then min := d2;

  min := getmin(min);

  c1 := d1 div min; c2 := d2 div min;

  for l := 0 to c1-1 do
  begin
    for s := 0 to c2-1 do
    begin
      for i := 1 to min do
        for j := 1 to min do
          a[x1+l*min+i-1,y1+s*min+j-1] := cont;
      inc(cont);
    end;
  end;


  Divide(x1,y1+min*c2,x1+min*c1-1,y2);
  Divide(x1+min*c1,y1,x2,y1+min*c2-1);
  Divide(x1+min*c1,y1+min*c2,x2,y2);

end;

begin
  assign(input,'piese.in'); reset(input);
  assign(output,'piese.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n,m); cont := 1;

  Divide(1,1,n,m);


  writeln(cont-1);
  for i := 1 to n do
  begin
    for j := 1 to m do write(a[i,j],' ');
    writeln();
  end;

  close(input);
  close(output);
end.
