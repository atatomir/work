var a:array[0..160000]of real;
    v:array[1..400,1..2]of longint;
    t,ti,n,i,j,pos,h:longint;
    ant:real;
    bufin:array[1..65000]of byte;
    corect:boolean;

function hash(x,y,xx,yy:longint):real;
var a,b,p,l:real;
begin
  hash := 0;
  if x = xx then
    hash := 722563929.4422
  else
  begin
    a := xx - x;
    b := yy - y;
    p := b/a; l := sqrt(sqr(a)+sqr(b));
    hash := p+l;
  end;
end;

procedure QSort(l,h:longint);
var i,j:longint;
    y,x:real;
begin
  i := l; j := h; x := a[(i+j)div 2];
  repeat
    while a[i] < x do inc(i);
    while a[j] > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if i < h then QSort(i,h);
  if l < j then QSort(l,j);
end;

begin
  assign(input,'plagiat.in'); reset(input);
  assign(output,'plagiat.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    for i := 1 to n do readln(v[i,1],v[i,2]);

    h := 0;
    for i := 1 to n-1 do
      for j := i+1 to n do
      begin
        inc(h);
        a[h] := hash(v[i,1],v[i,2],v[j,1],v[j,2]);
      end;

    Qsort(1,h);

    corect := false;
    ant := a[1]; pos := 1;
    for i := 2 to h do
      if a[i] = ant then
      begin
        inc(pos);
        if pos >= 3 then
        begin
          corect := true;
          break;
        end;
      end
      else
      begin
        pos := 1;
        ant := a[i];
      end;

    if corect then writeln('DA') else writeln('NU');

  end;

  close(input);
  close(output);
end.