var s:ansistring;
    i,n,cont:longint;
    lc:char;

begin
  assign(input,'compress.in'); reset(input);
  assign(output,'compress.out'); rewrite(output);

  readln(s);
  n := length(s);  lc := '@';  cont := 1;

  for i := 1 to n do
  begin
    if pos(s[i],'abcdefghijklmnopqrstuvwxyz') > 0 then
    begin
      if lc = s[i] then
        inc(cont)
      else
      begin
        if i > 1 then
        begin
          write(lc,cont);
          lc := s[i];
          cont := 1;
        end;
      end;
      lc := s[i];
    end;
  end;

  write(lc,cont);

  close(input);
  close(Output);
end.