type boat=record
       pos,lung:longint;
     end;
     finish=record
       pos,boats:longint;
     end;
var n,i,j,h,cont,max,imax:longint;
    a:array[0..10005]of boat;
    v:array[0..10005]of finish;

procedure QSort(l,h:longint);
var i,j,x:longint;
    y:boat;
begin
  i := l; j := h; x := a[(i+j)div 2].pos ;
  repeat
    while a[i].pos < x do inc(i);
    while a[j].pos > x do dec(j);
    if i <= j then
    begin
      y := a[i]; a[i] := a[j]; a[j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(l,j);
  if i < h then QSort(i,h);
end;

function cbmax(x:longint):int64;
var i,j,m:longint;
begin
  if cont = 0 then cbmax := 0
  else
  begin
    i := 1 ; j := cont;
    repeat
      m := (i+j)div 2;
      if x < v[m].pos then
        j := m-1
      else
        i := m+1;
    until i > j;

    cbmax := j;
  end;
end;

function cbmin(x:longint):int64;
var i,j,m:longint;
begin
  if cont = 0 then cbmin := 1
  else
  begin
    i := 1 ; j := cont;
    repeat
      m := (i+j)div 2;
      if x <= v[m].pos then
        j := m-1
      else
        i := m+1;
    until i > j;

    cbmin := i;
  end;
end;

begin
  {assign(input,'boat.in'); reset(input);
  assign(output,'boat.out'); rewrite(output); }

  readln(n);
  for i := 1 to n do readln(a[i].lung,a[i].pos);
  QSort(1,n);

  cont := 0; v[0].pos := -100005; v[0].boats := 0;
  for i := 1 to n do
  begin
    h := cbmax(a[i].pos);
    max := v[h].boats; imax := h;
    for j := h-1 downto 1 do
    begin
      if v[j].boats = max then
      begin
        imax := j;
      end
      else
        break;
    end;
    imax := v[imax].pos;
    //!!!!  if imax < 0 then imax := 0;
    if imax < a[i].pos-a[i].lung then imax := a[i].pos-a[i].lung;
    inc(max); imax := imax + a[i].lung;
    //am descoperit cat putem adauga si unde
    h := cbmin(imax);
    if max > v[h-1].boats then
    begin
      inc(cont);
      for j := cont downto h do
      begin
        v[j] := v[j-1];
        if max > v[j].boats then v[j].boats := max;
      end;
      v[h].pos := imax; v[h].boats := max; //writeln('!',max,' ',imax);

    end;

  end;

  writeln(v[cont].boats);

  {close(input);
  close(output);}
end.