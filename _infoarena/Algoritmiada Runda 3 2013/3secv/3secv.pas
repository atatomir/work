var n,i,p1,p2:longint;
    a:array[1..1000003]of int64;
    bufin:array[1..65000]of byte;
    stotal,a1,a2,cauta,stotal2:int64;

begin
  assign(input,'3secv.in'); reset(input);
  assign(output,'3secv.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);  stotal := 0;
  for i := 1 to n do
  begin
    read(a[i]);
    stotal := stotal + a[i];
  end;
  cauta := stotal div 3;
  a1 := 0; a2 := 0;
  i := 1;

  a1 := a1 + a[i];

  while (a1 + a[i+1] <= cauta)and(i+1 <= n-2) do     // gasire p1
  begin
    inc(i);
    a1 := a1 + a[i];
  end;
  p1 := i; inc(i);

  a2 := a2 + a[i];       stotal2 := stotal - a1;
                      cauta := stotal2 div 2;

  while (a2 + a[i+1] <= cauta)and(i+1 <= n-1) do      // gasire p2
  begin
    inc(i);
    a2 := a2 + a[i];
  end;
  p2 := i;

  while ( a1 > a2 )and( p1 > 1) do             // verificare si regasire p1
  begin
    a1 := a1 - a[p1];
    a2 := a2 + a[p1];
    dec(p1);
  end;


  write(p1,' ',p2);

  close(input);
  close(output);
end.
