var n,i,v,cont:longint;
    c:char;
    s:ansistring;

begin
  assign(input,'par.in'); reset(input);
  assign(output,'par.out'); rewrite(output);

  readln(n);
  readln(s);
  v := 0; cont := 0;

  if n mod 2 = 1 then begin writeln(-1); close(input); close(output); exit; end;

  for i := 1 to n do
  begin
    if s[i] = '(' then
      inc(v)
    else
    begin
      dec(v);
      if v < 0 then
      begin
        inc(cont);
        v := 1;
      end;
    end;
  end;
  cont := cont + v div 2;
  writeln(cont);

  close(input);
  close(output);
end.