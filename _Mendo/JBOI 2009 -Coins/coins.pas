var c:array[1..3,1..2,1..12]of boolean;
    sign:array[1..3]of char;
    s:string;
    i,pos,j,x:longint;
    err,dif,gasit,gi:longint;
    gs:char;

procedure readd(var x:longint); inline;
begin
  while (ord(s[pos])<$30)or(ord(s[pos])>$39) do inc(pos);
  x := ord(s[pos])-$30;inc(pos);
  if not ((ord(s[pos])<$30)or(ord(s[pos])>$39)) then
  begin
    x := 10*x +  ord(s[pos])-$30;
    inc(pos);
  end;
end;

procedure verif();inline;
var ok:boolean;
    v1,v2:longint;
begin
  ok := true;
  for i := 1 to 3 do
  begin
    v1 := 1; v2 := 1;
    if c[i,1,err] then v1 := v1 + dif;
    if c[i,2,err] then v2 := v2 + dif;

    case sign[i] of
      '=': if v1 <> v2 then ok := false;
      '<': if v1 >= v2 then ok := false;
      '>': if v1 <= v2 then ok := false;
    end;
  end;
  if ok then
  begin
    inc(gasit);
    gi := err;
    if dif = -1 then gs := '-' else gs := '+';
  end;
end;

begin
  for i := 1 to 3 do
    for j := 1 to 12 do
    begin
      c[i,1,j] := false;
      c[i,2,j] := false;
    end;

  for i := 1 to 3 do
  begin
    readln(s);
    while s = '' do readln(s);

    s := s + '///';

    for j := 1 to length(s) do
      if (s[j]='=')or(s[j]='<')or(s[j]='>') then sign[i] := s[j];
    pos := 1;
    for j := 1 to 4 do
    begin
      readd(x);
      c[i,1,x] := true;
    end;
    for j := 1 to 4 do
    begin
      readd(x);
      c[i,2,x] := true;
    end;
  end;

  gasit := 0; gi := 0; gs := '/';
  for err := 1 to 12 do
  begin
    dif := +1;
    verif();
    dif := -1;
    verif();
  end;

  if gasit = 0 then
    writeln('impossible')
  else
  if gasit > 1 then
    writeln('indefinite')
  else
    writeln(gi,gs);
end.