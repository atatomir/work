type interval=record
       max:smallint;
       pos:smallint;
     end;
var n,m,i,j,cont:longint;
    f,b,r:array[0..2005]of smallint;
    a:array[0..2005]of interval;

function maxim(a,b:smallint):smallint;
begin
  if a > b then maxim := a else maxim := b;
end;

procedure QSortInt(l,h:smallint);
var i,j,x:smallint;
    y:interval;
begin
  i := l ; j := h; x := a[(i+j)div 2].max;
  repeat
    while a[i].max < x do inc(i);
    while a[j].max > x do dec(j);
    if i<=j then
    begin
      y := a[i] ; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i>j;
  if i < h then QSortInt(i,h);
  if j > l then QSortInt(l,j);
end;

procedure QSortB(l,h:smallint);
var i,j,x,y:smallint;
begin
  i := l ; j := h; x := b[(i+j)div 2];
  repeat
    while b[i] < x do inc(i);
    while b[j] > x do dec(j);
    if i <=j then
    begin
      y := b[i]; b[i] := b[j]; b[j] := y;
      inc(i); dec(j);
    end;
  until i >j;
  if i < h then QSortB(i,h);
  if l < j then QSortB(l,j);
end;

begin
  assign(input,'volei.in'); reset(input);
  assign(output,'volei.out'); rewrite(output);

  readln(n);
  for i := 1 to n do read(f[i]); f[n+1] := f[1];
  for i := 2 to n+1 do
  begin
    a[i-1].max := maxim(f[i-1],f[i]);
    a[i-1].pos := i-1;
  end;

  readln(m);
  for i := 1 to m do read(b[i]);

  QSortInt(1,n);
  QSortB(1,m);

  for i := 1 to n do r[i] := 0;

  j := n;  a[0].max := -5; cont := 0;

  for i := m downto 1 do
  begin
    while a[j].max >= b[i] do dec(j);
    if j >= 1 then
    begin
      inc(cont);
      r[a[j].pos] := b[i];
      dec(j);
    end
    else
      break;
  end;


  writeln(cont);
  {for i :=  1 to n do
  begin
    write(f[i],' ');
    if r[i] <> 0 then write('(',r[i],') ');
  end;                       }
  //evaluatorul nu cere decat prima valoare , de aceea este comentat ^^
  //in cazul rasp complet scoate comentariul



  close(input);
  close(output);
end.
