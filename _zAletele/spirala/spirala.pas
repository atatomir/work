var bufout:array[1..65000]of byte;
    n,m:byte;
    x1,x2,y1,y2:byte;
    a:array[1..10,1..10]of byte;
    add,i,j:byte;

procedure umple(x1,x2,y1,y2:byte);
var i:byte;
begin
  for i := y1 to y2 do
  begin
    inc(add);
    a[x1,i] := add ;
  end;
  for i := x1+1 to x2-1 do
  begin
    inc(add);
    a[i,y2] := add;
  end;
  if x1 <> x2 then
  begin
    for i := y2 downto y1 do
    begin
      inc(add);
      a[x2,i] := add;
    end;
  end;
  for i := x2-1 downto x1+1 do
  begin
    inc(add);
    a[i,y1] := add;
  end;
  inc(x1); x2 := x2-1;
  inc(y1); y2 := y2-1;

  if (x1 <= x2) and (y1<=y2) then
    umple(x1,x2,y1,y2);

end;


begin
  assign(input,'spirala.in'); reset(input);
  assign(output,'spirala.out'); rewrite(output);
  settextbuf(output,bufout);

  add := 0;  read(n,m);

  umple(1,n,1,m);


  for i := 1 to n do
  begin
    for j := 1 to m do
      write(a[i,j]:4);
    writeln();
  end;

  close(input); close(output);
end.