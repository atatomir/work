type elem=record
       a,b:longint;
     end;
var op,n,m,k,i,j,max,x,y,x2,y2,cont:longint;
    a:array[0..1505,0..1505]of longint;
    bufin,bufout:array[1..65000]of byte;
    v:array[0..1005]of elem;
    l,c:array[0..1505]of shortint;

begin
  assign(input,'harta5.in'); reset(input);
  assign(output,'harta5.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(op);
  readln(n,m,k);

  if op = 1 then
  begin
    max := 0;
    for i :=1 to k do
    begin
      readln(x,y,x2,y2);
      v[i].a := x2-x; v[i].b := y2-y;

      if (x2-x=y2-y) then
        if x2-x > max then max := x2 - x;
    end;
    reset(input);
    readln(op); readln(op); cont := 0; inc(max);
    for i := 1 to k do
    begin
      if v[i].b > v[i].a then v[i].a := v[i].b;
      if v[i].a+1 <= max-2 then inc(cont);
    end;
    write(max*max,' ');
    writeln(cont);
  end
  else
  begin
    for i := 0 to n do
      for j := 0 to m do a[i,j] := 0;
    for i := 1 to k do
    begin
      readln(x,y,x2,y2);
      inc(a[x,y]); inc(a[x2+1,y2+1]);
      dec(a[x,y2+1]); dec(a[x2+1,y]);
      if (x2-x >= 2)and(y2-y >= 2) then
      begin
        dec(a[x+1,y+1]); dec(a[x2,y2]);
        inc(a[x+1,y2]); inc(a[x2,y+1]);
      end;
    end;


    for i := 1 to n do l[i] := 0;
    for j := 1 to m do c[j] := 0;

    for i := 1 to n do
      for j := 1 to m do
      begin
        a[i,j] := a[i,j] + a[i-1,j] + a[i,j-1] - a[i-1,j-1];
        if a[i,j] > 0 then
        begin
          l[i] := 1; c[j] := 1;
        end;
      end;

    for i := 2 to n do
      if (l[i-1] <= 0)and(l[i] = 0) then l[i] := -1;
    for i := 2 to m do
      if (c[i-1] <= 0)and(c[i] = 0) then c[i] := -1;

    for i := 1 to n do
    begin
      if l[i] >= 0 then
      begin
        for j := 1 to m do
          if c[j] >= 0 then write(a[i,j],' ');
        writeln();
      end;
    end;
  end;


  close(input);
  close(output);
end.
