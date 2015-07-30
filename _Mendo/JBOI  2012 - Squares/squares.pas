type line=record
       pos,d1,d2:longint;
     end;
var n,i,j,x,y,lat,cont:longint;
    a:array[1..2,0..205]of line;
    l,c:array[0..205]of longint;
    d,p1,p2:longint;
    sum:int64;

procedure QSort(v,l,h:longint);
var i,j,x,x2:longint;
    y:line;
begin
  i := l; j := h ; x := a[v,(i+j)div 2].pos;  x2 := a[v,(i+j)div 2].d1;
  repeat
    while (a[v,i].pos < x)or((a[v,i].pos = x)and(a[v,i].d1 < x2)) do inc(i);
    while (a[v,j].pos > x)or((a[v,j].pos = x)and(a[v,j].d1 > x2)) do dec(j);
    if i<= j then
    begin
      y := a[v,i]; a[v,i] := a[v,j]; a[v,j] := y;
      inc(i); dec(j);
    end;
  until i > j;
  if l < j then QSort(v,l,j);
  if i < h then QSort(v,i,h);
end;

function verif(v,pos,d1,d2:longint):boolean;
var i:longint;
begin
  for i := 1 to cont do
    if a[v,i].pos = pos then
      if a[v,i].d1 <= d1 then
        if a[v,i].d2 > d1 then d1 := a[v,i].d2;
  if d1 >= d2 then verif := true else verif := false;
end;

begin
  {assign(input,'squares.in'); reset(input);
  assign(output,'squares.out'); rewrite(output);}

  readln(n); cont := 0;

  for i := 1 to n do
  begin
    readln(x,y,lat);
    inc(cont);
    a[1,cont].pos := x; a[1,cont].d1 := y; a[1,cont].d2 := y+lat;
    a[2,cont].pos := y; a[2,cont].d1 := x; a[2,cont].d2 := x+lat;

    inc(cont);
    a[1,cont].pos := x+lat; a[1,cont].d1 := y; a[1,cont].d2 := y+lat;
    a[2,cont].pos := y+lat; a[2,cont].d1 := x; a[2,cont].d2 := x+lat;
  end;

  QSort(1,1,cont);
  QSort(2,1,cont);

  l[0] := 1; l[1] := a[1,1].pos;
  c[0] := 1; c[1] := a[2,1].pos;
  sum := 0;

  for i := 2 to cont do
  begin
    if a[1,i].pos <> a[1,i-1].pos then begin inc(l[0]); l[l[0]] := a[1,i].pos; end;
    if a[2,i].pos <> a[2,i-1].pos then begin inc(c[0]); c[c[0]] := a[2,i].pos; end;
  end;

  for i := 1 to l[0]-1 do
    for j := i+1 to l[0] do
    begin
      d := l[j] - l[i];
      p2 := 0;
      for p1 := 1 to c[0]-1 do
      begin
        if p2 <= p1 then p2 := p1+1;
        while (c[p2]-c[p1] < d)and(p2 < c[0]) do inc(p2);
        if c[p2]-c[p1] = d then
        begin
          if verif(1,l[i],c[p1],c[p2]) then
            if verif(1,l[j],c[p1],c[p2]) then
              if verif(2,c[p1],l[i],l[j]) then
                if verif(2,c[p2],l[i],l[j]) then inc(sum);
          //writeln(sum,' ! ',l[i],' ',c[p1],' ',l[j],' ',c[p2]);
        end;
      end;
    end;

   writeln(sum);

   {close(input);
   close(output); }
end.
