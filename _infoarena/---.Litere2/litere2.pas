type cuvant=record
       s:ansistring;
       id:longint;
     end;
var s,sl:ansistring;
    i,cont,nr,idl:longint;
    a:array[0..500005]of cuvant;
    bufin,bufout:array[1..65000]of byte;
    r:array[0..500005]of longint;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:longint;
begin
  i := l ; j := h; x := a[r[(i+j)div 2]].id;
  repeat
    while a[r[i]].id < x do inc(i);
    while a[r[j]].id > x do dec(j);
    if i <= j then
    begin
      y := r[i]; r[i] := r[j]; r[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

begin
  assign(input,'litere2.in'); reset(input);
  assign(output,'litere2.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(s);

  cont := 0; i := 1;
  while s[i] = ' ' do inc(i);

  while s[i] <> '.' do
  begin
    inc(cont); sl := ''; idl := 0;
    while s[i] >= 'a' do
    begin
      sl := sl + s[i];
      idl := idl or (1 shl (ord(s[i])-$60));
      inc(i);
    end;
    a[cont].s := sl; a[cont].id := idl;

    while s[i] = ' ' do inc(i);
  end;

  for i := 1 to cont do r[i] := i;
  QSort(1,cont);

  nr := 1;
  for i := 2 to cont do
    if a[r[i]].id <> a[r[i-1]].id then inc(nr);

  writeln(nr);
  a[0].id := a[r[1]].id; r[0] := 0;
  for i := 1 to cont do
  begin
    if a[r[i]].id <> a[r[i-1]].id then writeln();
    write(a[r[i]].s,' ');
  end;


  close(input);
  close(output);
end.