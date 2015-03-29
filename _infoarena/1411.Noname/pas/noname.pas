var n,i,j,x,h,t,t2,t3,t4:longint;
    a:array[1..2,0..1001]of smallint;
    r:array[0..1001,0..1001]of shortint;

procedure var1;
begin
  readln(n);
  for i := 1 to n do read(a[1,i]);
  readln();
  for i := 1 to n do read(a[2,i]);

  writeln('1');

  for i := 1 to n do
  begin
    j := 0;
    while a[1,i] > 0 do
    begin
      inc(j);
      if a[2,j] > 0 then
      begin
        write('1 ');
        dec(a[1,i]);
        dec(a[2,j]);
      end
      else
        write('0 ');
    end;
    writeln();
  end;
end;

////////////////////////////////////////////////////////
//          2 variante diferite
////////////////////////////////////////////////////////
procedure var2;
begin
  readln(n);  writeln('1');
  for i := 1 to n do
  begin
    read(x);
    a[1,x] := i;
  end;
  readln();
  for i := 1 to n do
  begin
    read(x);
    a[2,x] := i;
  end;

  for i := 1 to n do
    for j := 1 to n do r[i,j] := -1;

  h := n div 2 ;

  for i := n downto h do
  begin
    t := a[1,i]; t2 := a[1,n-i+1];
    t3:= a[2,i]; t4 := a[2,n-i+1];
    for j := 1 to n do
    begin
      if r[t,j] = -1 then r[t,j] := 1;
      if r[j,t3] = -1 then r[j,t3] := 1;
    end;
    for j := 1 to n do
    begin
      if r[t2,j] = -1 then r[t2,j] := 0;
      if r[j,t4] = -1 then r[j,t4] := 0;
    end;
  end;

  for i := 1 to n do
  begin
    for j := 1 to n do
      write(r[i,j],' ');
    writeln();
  end;


end;

begin
  assign(input,'noname.in'); reset(input);
  assign(output,'noname.out'); rewrite(output);

  var2;

  close(input);
  close(output);
end.
