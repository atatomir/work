var n,k,i,j,m,sum,bestl,bestk:longint;
    a:array[0..1000005]of longint;
    bufin:array[1..65000]of byte;

function is_good(targ:longint):boolean;
var grup,pos,s1,s2,grupe:longint;
begin
  is_good := true;
  pos := 1;

  for grup := 1 to k do
  begin
    grupe := grup;

    s1 := 0;
    while a[pos]+s1 <= targ do
    begin
      s1 := s1 + a[pos] ;
      inc(pos);

      if pos >n then break;
    end;

    s2 := 0;
    if pos <= n then
    while a[pos]+s2 <= targ do
    begin
      s2 := s2 + a[pos] ;
      inc(pos);

      if pos > n then break;
    end;

    inc(pos);

    if pos > n then break;
  end;

  if pos <=n then is_good := false else bestl := grupe;

end;

begin
  assign(input,'orase.in'); reset(input);
  assign(output,'orase.out'); rewrite(output);

  readln(n,k); a[n] := 0;
  sum := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    sum := sum + a[i];
  end;

  i := 0; j := sum;
  repeat
    m := (i+j)div 2;
    if is_good(m) then
    begin
      j := m-1;
      bestk := bestl;
    end
    else
      i := m+1;
  until i > j;

  writeln(i,' ',bestk);

  close(input);
  close(output);
end.