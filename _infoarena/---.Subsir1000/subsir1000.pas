type prim = record
       v,l:longint;
     end;
var n,i,s,x,j,max,maxx:longint;
    c:array[1..100000]of boolean;
    a:array[0..35000]of prim;
    best:array[0..100000]of longint;

procedure ciur();
var i,j,h:longint;
begin
  s := 0;

  for i := 2 to n do c[i] := true;
  c[1] := false;

  for i := 2 to n do
  begin
    if c[i] = false then continue;

    inc(s); a[s].v := i; a[s].l := 0;

    h := n div i;
    for j := i to h do c[i*j] := false;

  end;
end;

begin
  assign(input,'subsir1000.in'); reset(input);
  assign(output,'subsir1000.out'); rewrite(output);

  readln(n);
  ciur(); maxx := -1;  best[0] := 0;

  for i := 1 to n do
  begin
    read(x); max := -1;
    for j := 1 to s do
    begin
      if x mod a[j].v = 0 then
      begin
        if max < best[a[j].l]+1 then max := best[a[j].l]+1;
        a[j].l := i;
      end;

      if a[j].v >= x then break;
    end;
    if maxx < max then maxx := max;
    best[i] := max;
  end;

  writeln(maxx);

  close(input);
  close(output);
end.