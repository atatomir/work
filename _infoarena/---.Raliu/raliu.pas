var t,ti,n,i,rep,cont:longint;
    a:array[0..1000005]of int64;
    bufin:array[1..65000]of byte;
    mmic:boolean;
    x:longint;
    s : int64;
  
begin
  assign(input,'raliu.in'); reset(input);
  assign(output,'raliu.out'); rewrite(output);
  settextbuf(input,bufin);
  
  readln(t);
  for ti := 1 to t do
  begin
    readln(n); a[0] := -1;s := 0;
    for i := 1 to n do read(a[i]); readln();
    for i := 1 to n do
    begin
      read(x);
      a[i] := a[i] - x;
      s := s + a[i];
      if a[i-1] > 0 then a[i] := a[i]+a[i-1];
    end;
  
    if (a[n] <= -1) or ( s<0 ) then
    begin
      writeln('NU');
      continue;
    end
    else
    begin
      rep := 0;
      for i := 1 to n-1 do
        if a[i] < 0 then inc(rep);
  
      a[0] := -1;
      cont := n; while a[cont-1] >= 0 do dec(cont);
  
      a[0] := a[n];
      for i := 1 to cont-1 do
      begin
        if a[i] < 0 then mmic := true else mmic := false;
        a[i] := a[i] + a[i-1];
        if mmic then
          if a[i] >= 0 then
            dec(rep)
          else
            break;
      end;
  
      if rep > 0 then
        writeln('NU')
      else
      begin
        writeln('DA');
        writeln(cont);
      end;
  
    end;
  
  end;
  
  
  
  close(input);
  close(output);
end.