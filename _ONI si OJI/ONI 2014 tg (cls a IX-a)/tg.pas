var n,i,j:longint;
    ok:array[0..4000005]of boolean;
    rez:int64;


begin
  assign(input,'tg.in'); reset(input);
  assign(output,'tg.out'); rewrite(output);

  readln(n);
  for i := 1 to n do ok[i] := false;
  for i := 1 to n do
    if not ok[i] then
    begin
      j := 1;
      while i*j*j <= n do
      begin
        rez := rez + j-1;
        ok[i*j*j] := true;
        inc(j);
      end;
    end;

  writeln(rez);

  close(input);
  close(output);
end.
