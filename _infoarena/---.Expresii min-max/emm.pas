var s:ansistring;
    i:longint;

function mm(c:char;a,b:longint):longint;
begin
  case c of
    'm': if a < b then mm := a else mm := b;
    'M': if a > b then mm := a else mm := b;
  end;
end;

function getterm:longint;
var x:longint;
begin
  x := 0;
  while pos(s[i+1],'0123456789') > 0 do
  begin
    inc(i);
    x := x*10 + ord(s[i])-48;

    if i = length(s) then break;
  end;
  getterm := x;
end;

function eval:longint;
var x:longint;
    op:char;
begin
  op := 'M'; x := -5;

  while (i+1<= length(s)) do
  begin
    inc(i);
    if s[i] = '(' then
      x := mm(op,x,eval())
    else
    begin
      if (s[i] = 'm') or (s[i]='M') then
        op := s[i]
      else
      if pos(s[i],'0123456789') > 0 then
      begin
        dec(i);
        x := mm(op,x,getterm);
      end
      else
        break;
    end;

  end;

  eval := x;
end;

begin
  assign(input,'emm.in'); reset(input);
  assign(output,'emm.out'); rewrite(output);

  readln(s);  i := 0;
  writeln(eval);

  close(input);
  close(output);
end.
