var a:array[1..9]of longint;
    k,i,ti:longint;

begin
  assign(input,'calcgame.in'); reset(input);
  assign(output,'calcgame.out'); rewrite(output);

  readln(k);
  for i := 1 to 9 do a[i] := 0;

  for ti := 1 to 1000 do
  begin
    for i := 1 to 9 do
    begin
      a[i] := (a[i]*10+i)mod k;
      if a[i] = 0 then
      begin
        writeln(i,' ',ti);
        close(input);
        close(output);
        exit;
      end;
    end;
  end;

  writeln('Impossible');

  close(input);
  close(output);
end.