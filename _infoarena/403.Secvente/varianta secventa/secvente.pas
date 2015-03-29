var n,i,j:longint;
    bufin:array[1..65000]of byte;
    x,suma,max:longint;
    a0,a1,a2,b0,b1,b2:longint;


begin
  assign(input,'secvente.in'); reset(input);
  assign(output,'secvente.out'); rewrite(output);
  settextbuf(input,bufin);

  for i := 1 to 3 do
  begin
    readln(n); suma := 0; a0 := -1; a1 := -1; a2 := -1;
                          b0 := -1; b1 := -1; b2 := -1; max := -1;
    for j := 1 to n do
    begin
      readln(x);
      suma := (suma + x) mod 3; //writeln('!',suma);
      case suma of
        0: a0 := j;
        1: if a1 = -1 then a1 := j else b1 := j;
        2: if a2 = -1 then a2 := j else b2 := j;
      end;
    end;


    if (a0 <> -1)  then
      if max < a0 then max := a0;
    if (a1 <> -1) and (b1 <> -1) then
      if max < b1 - a1 then max := b1-a1;
    if (a2 <> -1) and (b2 <> -1) then
      if max < b2 - a2 then max := b2-a2;

    if (max = -1) and (a0 <> -1) then max := 1;

    if max = -1 then max := 0;
    writeln(max);

  end;


  close(input);
  close(output);
end.