var n,m,i,j:longint;
    a,b:array[1..251,1..251]of smallint;
    bufin:array[1..65000]of byte;
    min1,min2,pos:longint;
    minl1,minl2,lpos:longint;

procedure calc_min(x:smallint);
begin
  //writeln(x,' ',minl1,' ',minl2,' ',pos);

  if minl1 > x then
  begin
    minl2 := minl1;
    minl1 := x;
    lpos := j;
  end
  else
    if minl2 > x then
    begin
      minl2 := x;
    end;

end;

begin
  assign(input,'lacusta.in'); reset(input);
  assign(output,'lacusta.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to n do
  begin
    for j := 1 to m do
      read(a[i,j]);
    readln();
  end;


  if (n = 1) and (m = 1) then
    write(a[1,1])
  else
  begin
    if n =1 then
      write(a[1,1] + a[1,m])
    else
    begin                             //rezolvare
      b[1,1] := a[1,1];   for i := 2 to m do b[1,i] := b[1,1] + 1;
      minl1 := 999999; minl2 := 999999; lpos := 9999999;

      pos := 1; min1 := a[1,1]; min2 := 999;
      for i := 2  to n do
      begin

        //writeln('!',min1,' ',min2,' ',pos);

        for j := 1 to m do
        begin

          if pos <> j then
            b[i,j] := min1 + a[i,j] + a[i-1,j]
          else
            b[i,j] := min2 + a[i,j] + a[i-1,j];

          calc_min(b[i,j]);

        end;

        min1 := minl1; min2 := minl2; pos := lpos;
        minl1 := 999999; minl2 := 999999; lpos := 9999999;
      end;


    end;                           // sf rezolvare
  end;

 { for i := 1 to n do
  begin
    for j := 1 to m do
      write(b[i,j],' ');
    writeln();
  end;                              }

  //writeln(a[n,m],' ',min1,' ',min2);


  if pos <> m then write(a[n,m] + min1) else write(a[n,m]+min2);

  close(input);
  close(output);
end.
