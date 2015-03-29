var n,n2,i,a,b:longint;
    max,t:longint;

begin
  assign(input,'serviciu.in'); reset(input);
  assign(output,'serviciu.out'); rewrite(output);

  max := -1;

  readln(n); n2 := n * 2;

  for i := 1 to n do
  begin
    readln(a,b);

    if a < b then
    begin
      t := a;
      a := b;
      b := t;
    end;

    t := a - b;
    b := b + n2;
    if t > b-a then t := b-a ;

    if t > max then max := t;

  end;

  write(max);

  close(input);
  close(output);
end.
