var n,t:longint;
    s:string;
    a:array[0..1001]of byte;
    i,mmic,s1,s2:longint;
    op:char;

function getterm:longint;
var x:longint;
begin
  x := 0;
  while pos(s[i],'0123456789') > 0 do
  begin
    x := x*10+ ord(s[i])- $30;
    inc(i);
  end;
  case s[i] of
    'm': x := x * 1000;
    's': x := x * 100;
    'z': x := x * 10;
  end;
  inc(i);
  getterm := x;
end;

begin
  assign(input,'comp.in'); reset(input);
  assign(output,'comp.out'); rewrite(output);

  readln(n);  mmic := 0;

  for t := 1 to n do
  begin
    readln(s);  s := s + '<';
    i := 1; s1 := 0; s2 := 0;
    while (s[i] <> '<') and (s[i] <> '>') do
    begin
      if s[i] = '+' then
        inc(i)
      else
      begin
        s1 := s1 + getterm;
      end;
    end;
    op := s[i]; inc(i);
    while (s[i] <> '<') and (s[i] <> '>') do
    begin
      if s[i] = '+' then
        inc(i)
      else
      begin
        s2 := s2 + getterm;
      end;
    end;

    if op = '<' then inc(mmic);
    case op of
      '<': if s1 < s2 then a[t] := 1 else a[t] := 0;
      '>': if s1 > s2 then a[t] := 1 else a[t] := 0;
    end;
  end;

  writeln(mmic);
  for i := 1 to n do writeln(a[i]);


  close(input);
  close(output);
end.