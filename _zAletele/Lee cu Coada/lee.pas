const nr = 5000001;
type coada=record
       x,y,pos:longint;
     end;
var n,m,u,v,ei,ej,epos:longint;
    a:array[1..1000,1..1000]of longint;
    c:array[1..2000000]of coada;
    fo:text;

begin
  assign(input,'Lee.in'); reset(input);
  assign(fo,'Lee.out'); rewrite(fo);

  readln(n,m,c[1].x,c[1].y); c[1].pos := 1;

  for u := 1 to n do
    for v := 1 to m do
      a[u,v] := nr;

  u := 1; v := 1;


  repeat
    ei := c[u].x; ej := c[u].y; epos := c[u].pos;
    inc(u);
    if a[ei,ej] = nr then
      a[ei,ej] := epos;

    //writeln(u,' ',v);



    if (ei > 1) and (a[ei-1,ej] = nr) then
    begin
      inc(v);
      c[v].x := ei-1; c[v].y := ej; c[v].pos := epos+1;
    end;

    if (ej > 1) and (a[ei,ej-1] = nr) then
    begin
      inc(v);
      c[v].x := ei; c[v].y := ej-1; c[v].pos := epos+1;
    end;

    if (ei < n) and (a[ei+1,ej] = nr) then
    begin
      inc(v);
      c[v].x := ei+1; c[v].y := ej; c[v].pos := epos+1;
    end;

    if (ej < m) and (a[ei,ej+1] = nr) then
    begin
      inc(v);
      c[v].x := ei; c[v].y := ej+1; c[v].pos := epos+1;
    end;


    if (ei > 1) and (ej > 1) and (a[ei-1,ej-1] = nr) then
    begin
      inc(v);
      c[v].x := ei-1; c[v].y := ej-1; c[v].pos := epos+1;
    end;

    if (ei < n) and (ej < m) and (a[ei+1,ej+1] = nr) then
    begin
      inc(v);
      c[v].x := ei+1; c[v].y := ej+1; c[v].pos := epos+1;
    end;

    if (ei > 1) and (ej < m) and (a[ei-1,ej+1] = nr) then
    begin
      inc(v);
      c[v].x := ei-1; c[v].y := ej+1; c[v].pos := epos+1;
    end;

    if (ei < n) and (ej > 1) and (a[ei+1,ej-1] = nr) then
    begin
      inc(v);
      c[v].x := ei+1; c[v].y := ej-1; c[v].pos := epos+1;
    end;


  until u > v;               //writeln('test');

  for u := 1 to n do
  begin
    for v := 1 to m do
    begin
      write(fo,a[u,v],' ');
    end;
    writeln(fo);
  end;

  close(Input);
  close(fo);
end.
