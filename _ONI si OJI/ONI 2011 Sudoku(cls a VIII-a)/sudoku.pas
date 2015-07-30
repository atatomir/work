var i,j,ant:longint;
    n,nr,k,l,h:QWord;
    a:array[1..32,1..32]of byte;


procedure rezolva(i,j:longint;var l,h:QWord);
var p:longint;
    m:int64;
begin
  m := (l+h) div 2;
  if k <= m then p := 1 else p := 2;
  case ant of
    1: a[i,j] := p+1;
    2: if p = 1 then a[i,j] := 1 else a[i,j] := 3;
    3: a[i,j] := p;
  end;
  ant := a[i,j];
  if p = 1 then h := m else l := m+1;

end;


begin

  assign(input,'sudoku1.in'); reset(input);
  assign(output,'sudoku1.out'); rewrite(output);


  readln(n,k);
  nr := 1;
  for i := 1 to n-1 do nr := nr*4;
  writeln(nr*3);

  if k <= nr then
  begin
    a[1,1] := 1;
    l := 1; h := nr;
  end
  else
  if k <= 2*nr then
  begin
    a[1,1] := 2;
    l := nr+1; h := 2*nr;
  end
  else
  begin
    a[1,1] := 3;
    l := 2*nr+1; h := 3*nr;
  end;

  ant := a[1,1];
  for i := 2 to n do rezolva(1,i,l,h);
  ant := a[1,1];
  for i := 2 to n do rezolva(i,1,l,h);

  for i := 2 to n do
    for j := 2 to n do
    begin
      if a[i-1,j] = a[i,j-1] then
        a[i,j] := 6 - a[i-1,j] - a[i-1,j-1]
      else
        a[i,j] := 6 - a[i-1,j] - a[i,j-1];
    end;


  for i := 1 to n do
  begin

    for j := 1 to n do
      write(a[i,j],' ');
    writeln();
  end;

  close(input);
  close(output);
end.
