var n,m,i,y,j:longint;
    bufin,bufout:array[1..65000]of byte;
    a:array[1..3,0..15001]of longint;
    c:array[0..1001]of longint;
    v:array[0..1001]of boolean;
    h:longint;

procedure Sort(l, r: longint);
var
  i, j, x, y: longint;
begin
  i := l; j := r; x := a[2,(l+r) DIV 2];
  repeat
    while a[2,i] < x do i := i + 1;
    while x < a[2,j] do j := j - 1;
    if i <= j then
    begin
      y := a[2,i] ; a[2,i] := a[2,j]; a[2,j] := y;
      y := a[1,i] ; a[1,i] := a[1,j]; a[1,j] := y;
      i := i + 1; j := j - 1;
    end;
  until i > j;
  if l < j then Sort(l, j);
  if i < r then Sort(i, r);
end;
	
	
	
begin
  assign(input,'3color.in'); reset(input);
  assign(output,'3color.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n,m);
  for i := 1 to m do readln(a[1,i],a[2,i]);

  Sort(1,m);

  c[0] := 0;  j := 0; a[2,m+1] := -5;

  for i := 1 to n-1 do
  begin
    for h := 0 to 999 do v[h] := false;
    while a[2,j+1] = i do
    begin
      inc(j);
      v[c[a[1,j]]] := true;
    end;

    for h := 0 to 999 do
      if v[h] = false then
      begin
        c[i] := h;
        break;
      end;
  end;

  for i := 0 to n-1 do write(c[i],' ');

  close(input);
  close(output);
end.
