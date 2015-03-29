var s:ansistring;
    i,n,h,cont,nn:longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'palalila2.in'); reset(input);
  assign(output,'palalila2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(s);
  n := length(s);

  nn := 1;
  for i := 2 to n do
  begin
    if s[i] <> s[i-1] then
    begin
      inc(nn); s[nn] := s[i];
    end;
  end;
  n := nn;

  if n = 1 then
  begin
    writeln(1);
    close(input);
    close(output);
    exit;
  end;

  while not((ord(s[n]) >= $41)and(ord(s[n]) <= $7A)) do dec(n);
  h := 1;
  while (s[h] > s[h+1])and(h<n) do inc(h);

  cont := 1;
  for i := h+2 to n do
  begin
    if ((s[i-2] < s[i-1])and(s[i-1] > s[i])) or
       ((s[i-2] > s[i-1])and(s[i-1] < s[i])) then
    begin
      inc(cont);
    end;
  end;

  writeln(cont+1);

  close(input);
  close(output);
end.
