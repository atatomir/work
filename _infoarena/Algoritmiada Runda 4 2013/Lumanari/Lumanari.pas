var m,n,i,grup,nant,cont,h,h2:longint;
    a:array[1..200001]of longint;
    bufin:array[1..65000]of byte;

procedure Sort(l, r: longint);
var
  i, j, x, y: longint;
begin
  i := l; j := r; x := a[(l+r) DIV 2];
  repeat
    while a[i] < x do i := i + 1;
    while x < a[j] do j := j - 1;
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;


begin
  assign(input,'lumanari.in'); reset(input);
  assign(output,'lumanari.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(m);
  for i := 1 to m do read(a[i]);

  n := 0;  grup := 0;

  repeat

    nant := n;

    h := m - grup;
    sort(1,m);


    cont := 0;
    for i := 1 to h do
      if a[i] >= cont+1 then inc(cont);

    n := n + cont;
    for i := m downto h+1 do a[i] := a[i]-cont;
    h2 := h - cont+1;
    for i := h2 to h do a[i] := a[i] - (i-h2+1);
    grup := n;


  until n = nant;

  writeln(n);

  close(input);
  close(output);
end.
