var n,i,j,pos1,pos2:longint;
    a:array[1..105,1..105]of int64;
    bufin:array[1..65000]of byte;
    max:int64;

begin
  assign(input,'neo.in'); reset(input);
  assign(output,'neo.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);                       max := -7;
  for i := 1 to n do read(a[i,i]);

  for i := 1 to n-1 do
  begin
    for j := i+1 to n  do
    begin
      a[i,j] := a[i,j-1] * a[j,j];
      if (max = -7) or (max < a[i,j]) then
      begin
        max:= a[i,j];
        pos1 := i;
        pos2 := j;
      end;
    end;
  end;

  if max < 0 then
  begin
    writeln('0');
    writeln('0 0');
  end
  else
  begin
    writeln(max);
    writeln(pos1,' ',pos2);
  end;


  close(input);
  close(output);
end.