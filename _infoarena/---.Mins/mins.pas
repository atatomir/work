const def=-1000000;
var i,j:longint;
    a:array[0..1000005]of longint;
    h,sum,val,n,m,min:int64;

begin
  assign(input,'mins.in'); reset(input);
  assign(output,'mins.out'); rewrite(output);

  readln(n,m); dec(n); dec(m);

  if n < m then min := n else min := m;

  //for i := 1 to min do a[i] := 0;
  for i := 2 to min do
  begin
    if a[i] = 0 then
    begin
      a[i] := 1;
      h := min div i;
      for j := 2 to h do inc(a[i*j]);

      h := i; h := h*h;
      h := min div h;
      for j := 1 to h do a[i*i*j] := def;

      val := (n div i)*(m div i);
      if a[i] and 1 = 0 then val := -val;
      sum := sum + val;
    end
    else
    if a[i] > 0 then
    begin
      val := (n div i)*(m div i);
      if a[i] and 1 = 0 then val := -val;
      sum := sum + val;
    end;

  end;

  sum := n*m - sum;
  writeln(sum);


  close(input);
  close(output);
end.