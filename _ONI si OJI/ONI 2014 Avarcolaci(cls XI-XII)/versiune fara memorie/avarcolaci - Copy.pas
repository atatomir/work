var t,ti:longint;
    n,i,ant,cont,x:longint;
    bufin:array[1..65000]of byte;
 
begin
  assign(input,'avarcolaci.in'); reset(input);
  assign(output,'avarcolaci.out'); rewrite(output);
  settextbuf(input,bufin);
 
  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    ant := -1; cont := 0;
    for i := 1 to 2*n do
    begin
      read(x);
      if cont = 0 then ant := x;
      if x = ant then inc(cont) else dec(cont);
    end; readln();
 
    if cont = 0 then
      writeln('Mozart')
    else
    begin
      reset(input);
      for i := 1 to ti*2 do readln();
      cont := 0;
      for i := 1 to 2*n do
      begin
        read(x);
        if x = ant then inc(cont);
      end; readln();
      if cont <= n then
        writeln('Mozart')
      else
        writeln(ant);
 
    end;
 
  end;
 
 
  close(input);
  close(output);
end.