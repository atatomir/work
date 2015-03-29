var n,i,l,act,max:longint;
    s:ansistring;
    bufin:array[1..65000]of byte;
    st:array[0..1000005]of char;
    lg:array[0..1000005]of longint;
    r:array[1..1000000]of boolean;

function invert(c:char):char;
begin
  case c of
    '(': invert := ')';
    '[': invert := ']';
    '{': invert := '}';
  end;
end;

begin
  assign(input,'paranteze.in'); reset(input);
  assign(output,'paranteze.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(s);

  l := 0; max := 0; st[0] := '!';

  for i :=1  to n do r[i] := false;

  for i := 1 to n do
  begin
    if pos(s[i],'([{') > 0 then
    begin
      inc(l);
      st[l] := s[i];
      lg[l] := i;
    end
    else
    begin
      if invert(st[l]) <> s[i] then
      begin
        l := 0;
      end
      else
      begin
        r[lg[l]] := true;
        r[i] := true;

        dec(l);
      end;
    end;
  end;

  max := 0; act := 0;

  for i := 1 to n do
  begin
    if r[i] then
    begin
      inc(act);
    end
    else
    begin
      if act > max then max := act;
      act := 0;
    end;

  end;

  if act > max then max := act;

  writeln(max);



  close(input);
  close(output);
end.
