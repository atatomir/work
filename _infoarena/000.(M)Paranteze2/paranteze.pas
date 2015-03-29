var s:ansistring;
    cont,d,lung,i:longint;

begin
  assign(input,'paranteze2.in'); reset(input);
  assign(output,'paranteze2.out'); rewrite(output);

  readln(s);
  lung := length(s);

  cont := 0; d := 0;

  for i := 1 to lung do
  begin
    if s[i] = '(' then
      inc(d)
    else
    begin
      if d > 0 then
      begin
        dec(d);
        inc(cont);
      end
      else
      begin
        d := 0;
      end;
    end;

  end;

  write(cont);

  close(input);
  close(output);
end.