
var k,cant:smallint;
    n,i,j,g :longint;
    greu:int64;
    a :array[1..1000000] of smallint;

    bufin:array[1..65000]of byte;


begin
  assign(input,'placute.in'); reset(input);
  assign(output,'placute.out'); rewrite(output);
  settextbuf(input,bufin);
  //for i:=1 to 1000000 do a[i] := 0;

  readln(n,k);
if k > 1 then
begin
  greu := 0;
  for i := 1 to n do
  begin
    read(g);
    readln(a[g ]);
    greu := greu + a[g];
  end;
  if n <> k then
  begin
  greu := 0;cant := 0;i := 1000000;
  repeat
    if a[i] > 0 then
    begin
     if a[i] <> cant then
     begin
      greu := greu + i;
      cant := a[i];
      a[i] := 0;
      i := i-1;
     end
     else
     begin
       j := i;
       while (j >= 1) and ((a[j] = cant) or (a[j] = 0)) do
       begin
         j := j - 1;
       end;

       if j > 0 then
       begin
        greu := greu + j;
        cant := a[j];
        a[j] := 0;
       end
       else
       begin
         i := 0;
       end;
     end;
    end
    else
    begin
      while (i>=1) and (a[i]=0) do i := i -1;

    end;


  until (i <= 0);
  end
  else
  begin
  end;
end
else
begin
  greu :=0;
  for i := 1 to n do
  begin
    readln(a[1],j);
    if a[1] > greu then greu := a[1];
  end;
end;



  write(greu);

  close(input);
  close(output);
end.
