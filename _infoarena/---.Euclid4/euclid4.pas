var a:array[0..2,0..220]of shortint;
    l:array[0..2] of longint;
    c:char;
    i,t,s,d,lm,cont:longint;
    ok:boolean;

procedure addtodest;
var rez,i:longint;
begin
  rez := 0;
  for i := 1 to lm do
  begin
    a[d,i] := a[d,i] + a[s,i] + rez;
    rez := a[d,i] div 10;
    a[d,i] := a[d,i] mod 10;
  end;

  l[d] := lm;
  if rez <> 0 then
  begin
    inc(l[d]); a[d,l[d]] := rez;
  end;

end;

function verif:longint;
var ident:boolean;
begin
  if l[0] > l[s] then verif := 0 else
  if l[0] < l[s] then verif := 2 else
  if l[0] = l[s] then
  begin
    ident := true;
    for i := l[0] downto 1 do
    begin
      if a[0,i] > a[s,i] then
      begin
        verif := 0; ident := false; break;
      end
      else
      if a[0,i] < a[s,i] then
      begin
        verif := 2; ident := false;break;
      end;
    end;
    if ident then verif := 1;
  end;

  if verif <> 2 then inc(cont);
end;

procedure back;
var i,imp:longint;
begin
  lm := l[s]; imp := 0;
  for i := 1 to lm do
  begin
    a[s,i] := a[s,i] - imp; imp := 0;
    a[s,i] := a[s,i] - a[d,i];
    if a[s,i] < 0 then
    begin
      a[s,i] := a[s,i] + 10;
      imp := 1;
    end;
  end;

  while a[s,lm] = 0 do dec(lm);
  l[s] := lm;

  t := s; s := d; d := t;
end;

begin
  assign(input,'euclid4.in'); reset(input);
  assign(output,'euclid4.out'); rewrite(output);

  l[0] := 0;

  while not eof(input) do
  begin
    read(c); if pos(c,'0123456789') = 0 then break;
    inc(l[0]);
    a[0,l[0]]:= ord(c) - $30;
  end;

  for i := 1 to l[0] div 2 do
  begin
    t := a[0,i];
    a[0,i] := a[0,l[0]-i+1];
    a[0,l[0]-i+1] := t;
  end;

  s := 1; d := 2;
  a[1,1] := 2; a[2,1] := 1; l[1] := 1; l[2] := 1;
  for i := 2 to 200 do
  begin
    a[1,i] := 0;
    a[2,i] := 0;
  end;

  ok := true; cont := 2;
  while ok do
  begin
    lm := l[s] ;

    addtodest;
    t := d; d := s; s := t;

    case verif() of
      1: ok := false;
      2: begin
           back();
           ok := false;
         end;
    end;

  end;

  writeln(cont);
  for i := l[d] downto 1 do write(a[d,i]); writeln();
  for i := l[s] downto 1 do write(a[s,i]); writeln();


  close(input);
  close(output);
end.
