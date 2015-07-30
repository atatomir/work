var s:ansistring;
    bg,en,hand,time,ruri,wait:int64;
    i:longint;

begin
  {assign(input,'hand.in'); reset(input);
  assign(output,'hand.out'); rewrite(output);}

  readln(s);
  bg := 1; en := length(s);

  while (s[bg] = 'L')and(bg <= en) do inc(bg);
  while (s[en] = 'R')and(bg <= en) do dec(en);

  if bg > en then begin writeln('0 0'); exit; end;

  hand := 0; time := 0; wait := 0;
  for i := bg to en do
  begin
    if s[i] = 'R' then
    begin
      inc(ruri);
      dec(wait); if wait < 0 then wait := 0;
    end
    else
    begin
      hand := hand + ruri;
      time := ruri + wait;
      inc(wait);
    end;
  end;

  writeln(time,' ',hand);

  {close(input);
  close(output);}
end.
