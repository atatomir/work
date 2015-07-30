var n,i,x,y,j,h,max:longint;
    a:array[1..14400]of smallint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'elfi.in'); reset(input);
  assign(output,'elfi.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  for i := 1 to 14400 do a[i] :=  0;

  for i := 1 to n do
  begin
    readln(x,y);
    x := 2*x+y+1;
    h := 14400 div x;
    for j := 1 to h do inc(a[j*x]);
  end;

  max := a[1];
  for i := 2 to 14400 do
    if a[i] > max then
      max := a[i];

  writeln(max);


  close(input);
  close(output);
end.
