type numar = record
       v:smallint;
       i:longint;
     end;
var n,k,i,j,t,x:longint;
    bufin:array[1..65000]of byte;
    max,maxi:longint;
    v:array[1..500000]of numar;

begin
  assign(input,'secventa.in'); reset(input);
  assign(output,'secventa.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);
  i := 1; j := 0;
  max := -30005;

  for t := 1 to n  do
  begin
    read(x);
    while (i <= j) and (v[j].v > x) do dec(j);
    inc(j); v[j].i := t; v[j].v := x;
    if v[i].i <= t -k then inc(i);
    if (v[i].v > max)and(t >= k ) then
    begin
      max := v[i].v;
      maxi := t;
    end;
  end;

  writeln(maxi-k+1,' ',maxi,' ',max);


  close(input);
  close(output);
end.
