var s:ansistring;
    n,i:longint;
    cuvi,act:ansistring;

begin
  assign(input,'beep.in'); reset(input);
  assign(output,'beep.out'); rewrite(output);

  readln(cuvi);
  readln(s); n := length(s);
  if s[n] <> ' ' then
  begin
    inc(n);
    s := s + ' ';
  end;

  act := '';

  for i := 1 to n do
  begin
    if ($41 <= ord(s[i]))and(ord(s[i]) <= $7A) then
    begin
      act := act + s[i];
    end
    else
    begin
      if act = cuvi then
        write('beep ')
      else
        write(act,' ');
      act := '';
    end;

  end;


  close(input);
  close(output);
end.